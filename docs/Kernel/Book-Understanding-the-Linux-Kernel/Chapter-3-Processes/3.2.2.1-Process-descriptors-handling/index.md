# 3.2.2.1. Process descriptors handling

Processes are dynamic entities whose lifetimes range from a few milliseconds to months. Thus, the kernel must be able to handle many processes at the same time, and **process descriptors** are stored in **dynamic memory** rather than in the memory area permanently assigned to the kernel. For each process, Linux **packs** two different data structures in a single per-process **memory area**: 

1、a small data structure linked to the **process descriptor**, namely the  `thread_info` structure

2、the **Kernel Mode process stack**. 

The length of this **memory area** is usually 8,192 bytes (two page frames). For reasons of efficiency the kernel stores the 8-KB memory area in two consecutive page frames with the first page frame aligned to a multiple of $2^{13}$ ; this may turn out to be a problem when little dynamic memory is available, because the free memory may become highly fragmented (see the section "The Buddy System Algorithm" in Chapter 8). Therefore, in the 80x86 architecture the kernel can be configured at **compilation time** so that **the memory area** including **stack** and  `thread_info` structure spans a single **page frame** (4,096 bytes).

> NOTE: 上面这段中的 **dynamic memory** 在Chapter 8. Memory Management中定义。

> NOTE: 1.6.3. Reentrant Kernels中**Kernel Mode process stack**是为**kernel control path**而准备的，kernel control path的执行是Reentrant的。

In the section "Segmentation in Linux" in Chapter 2, we learned that a process in **Kernel Mode** accesses a **stack** contained in the **kernel data segment**, which is different from the **stack** used by the process in **User Mode**. Because kernel control paths make little use of the stack, only a few thousand bytes of **kernel stack** are required. Therefore, 8 KB is ample space for the stack and the  `thread_info` structure. However, when stack and  `thread_info` structure are contained in a single page frame, the kernel uses a few additional stacks to avoid the overflows caused by deeply nested interrupts and exceptions (see Chapter 4).

> NOTE: 一个process有两个stack：
>
> - Kernel Mode process stack，由**kernel control path**使用
> - User Mode process stack



Figure 3-2 shows how the two data structures are stored in the 2-page (8 KB) memory area. The
`thread_info` structure resides at the beginning of the memory area, and the stack grows downward
from the end. The figure also shows that the  `thread_info` structure and the  `task_struct` structure
are mutually linked by means of the fields  `task` and  `thread_info` , respectively.

Figure 3-2. Storing the `thread_info` structure and the process kernel stack in two page frames

![](./Figure-3-2-Storing-the-thread_info-structure-and-the-process-kernel-stack-in-two-page-frames.jpg)

The  `esp` register is the **CPU stack pointer**, which is used to address the stack's top location. On 80x86
systems, the stack starts at the end and grows toward the beginning of the **memory area**（即从低地址向高地址）. Right after switching from **User Mode** to **Kernel Mode**, the kernel stack of a process is always empty, and therefore the  `esp` register points to the byte immediately following the stack.

The value of the  `esp` is decreased as soon as data is written into the stack. Because the  `thread_info`
structure is 52 bytes long, the **kernel stack** can expand up to 8,140 bytes.

The C language allows the  `thread_info` structure and the **kernel stack** of a process to be conveniently represented by means of the following union construct:

```c
union thread_union {
struct thread_info thread_info;
unsigned long stack[2048]; /* 1024 for 4KB stacks */
};
```

> NOTE: `thread_union`就是上述的memory area的实现。
>
> `thread_union`源码：https://elixir.bootlin.com/linux/latest/ident/thread_union

The  `thread_info` structure shown in Figure 3-2 is stored starting at address  `0x015fa000` , and the stack is stored starting at address  `0x015fc000` . The value of the  `esp` register points to the current **top** of the stack at  `0x015fa878` .

The kernel uses the  `alloc_thread_info` and  `free_thread_info` macros to allocate and release the **memory area** storing a  `thread_info` structure and a **kernel stack**.



## 注解

> The figure also shows that the  `thread_info` structure and the  `task_struct` structure are mutually linked by means of the fields  task and  `tHRead_info` , respectively.

要理解上面这段话，需要搞清楚`struct thread_info`的定义，以下是[i386的`struct thread_info`](https://elixir.bootlin.com/linux/v2.6.11/source/include/asm-i386/thread_info.h#L28)

```c
struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	unsigned long		flags;		/* low level flags */
	unsigned long		status;		/* thread-synchronous flags */
	__u32			cpu;		/* current CPU */
	__s32			preempt_count; /* 0 => preemptable, <0 => BUG */


	mm_segment_t		addr_limit;	/* thread address space:
					 	   0-0xBFFFFFFF for user-thead
						   0-0xFFFFFFFF for kernel-thread
						*/
	struct restart_block    restart_block;

	unsigned long           previous_esp;   /* ESP of the previous stack in case
						   of nested (IRQ) stacks
						*/
	__u8			supervisor_stack[0];
};
```

可以看到`struct thread_info`有成员变量`struct task_struct	*task`，而在`struct task_struct`中，有成员变量`struct thread_info *thread_info;`，这就是上面这段话的最后一句所描述的：



`thread_union`是保存在per-process memory area，这也就意味着： **Kernel Mode process stack**也保存在per-process memory area中；而这一段中又提及：a process in **Kernel Mode**  accesses a **stack** contained in the **kernel data segment**；那kernel data segment是存放在何处呢？

一个关键点是要知道本书的基于`i386`架构来进行描述的，在`i386`中，使用了segmentation，但是在后来这种方式被取代了；所以很多架构中压根可能就没有 **Kernel Mode stack** contained in the **kernel data segment**的这种结构，在[How are the segment registers (fs, gs, cs, ss, ds, es) used in Linux?](https://reverseengineering.stackexchange.com/questions/2006/how-are-the-segment-registers-fs-gs-cs-ss-ds-es-used-in-linux)中对此进行了说明。



基于这个问题，我进行了Google：`is kernel data segment in process address space`；目前所有的和这个问题相关的内容都在《`virtual-memory-address-space-thinking.md`》中；在阅读这一段的时候，
