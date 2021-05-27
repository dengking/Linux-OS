# 2.3. Segmentation in Linux

**Segmentation** has been included in 80 x 86 microprocessors to encourage programmers to split their
applications into logically related entities, such as subroutines or global and local data areas.
However, Linux uses segmentation in a very limited way. In fact, segmentation and paging are
somewhat redundant, because both can be used to separate the physical address spaces of
processes: segmentation can assign a different linear address space to each process, while paging
can map the same linear address space into different physical address spaces. Linux prefers paging
to segmentation for the following reasons:

- Memory management is simpler when all processes use the same segment register values that
  is, when they share the same set of **linear addresses**.
- One of the design objectives of Linux is portability to a wide range of architectures; RISC
  architectures in particular have limited support for segmentation.

The 2.6 version of Linux uses segmentation only when required by the 80 x 86 architecture.

All Linux processes running in User Mode use the same pair of segments to address instructions and
data. These segments are called ***user code segment*** and ***user data segment*** , respectively. Similarly,
all Linux processes running in Kernel Mode use the same pair of segments to address instructions
and data: they are called ***kernel code segment*** and ***kernel data segment*** , respectively. Table 2-3
shows the values of the Segment Descriptor fields for these four crucial segments.

Notice that the linear addresses associated with such segments all start at 0 and reach the
addressing limit of $2^{32} -1$. This means that all processes, either in User Mode or in Kernel Mode, may use the same logical addresses.

> NOTE: : 上述断言非常具有价值

Another important consequence of having all segments start at  `0x00000000` is that in Linux, logical
addresses coincide with linear addresses; that is, the value of the Offset field of a **logical address**
always coincides with the value of the corresponding **linear address**.



As stated earlier, the **Current Privilege Level** of the CPU indicates whether the processor is in User or
Kernel Mode and is specified by the  `RPL` field of the **Segment Selector** stored in the  `cs` register.
Whenever the **CPL** is changed, some **segmentation registers** must be correspondingly updated. For instance, when the  **CPL** is equal to 3 (User Mode), the  `ds` register must contain the **Segment Selector** of the user data segment, but when the CPL is equal to 0, the  `ds` register must contain the Segment
Selector of the kernel data segment.

A similar situation occurs for the  `ss` register. It must refer to a **User Mode stack** inside the **user data
segment** when the **CPL** is 3, and it must refer to a **Kernel Mode stack** inside the **kernel data segment**
when the CPL is 0. When switching from User Mode to Kernel Mode, Linux always makes sure that
the  `ss` register contains the **Segment Selector of the kernel data segment**.

> NOTE: : stack是inside data segment的，并且它们共用同一个descriptor；

When saving a pointer to an instruction or to a data structure, the kernel does not need to store the
**Segment Selector** component of the **logical address**, because the  `ss` register contains the **current**
**Segment Selector**. As an example, when the kernel invokes a function, it executes a  call assembly
language instruction specifying just the Offset component of its logical address; the Segment
Selector is implicitly selected as the one referred to by the  `cs` register. Because there is just one
segment of type "executable in Kernel Mode," namely the code segment identified by  `__KERNEL_CS` , it
is sufficient to load  __`KERNEL_CS` into  `cs` whenever the CPU switches to Kernel Mode. The same
argument goes for pointers to kernel data structures (implicitly using the  `ds` register), as well as for
pointers to user data structures (the kernel explicitly uses the  `es` register).

> NOTE: : 没有读懂

Besides the four segments just described, Linux makes use of a few other specialized segments.
We'll introduce them in the next section while describing the Linux `GDT`.



## 2.3.1. The Linux `GDT`

In uniprocessor systems there is only one `GDT`, while in multiprocessor systems there is one `GDT` for
every CPU in the system. All `GDT`s are stored in the  `cpu_gdt_table` array, while the addresses and
sizes of the `GDT`s (used when initializing the  `gdtr` registers) are stored in the  `cpu_gdt_descr` array. If
you look in the Source Code Index, you can see that these symbols are defined in the file
`arch/i386/kernel/head.S` . Every macro, function, and other symbol in this book is listed in the
Source Code Index, so you can quickly find it in the source code.



---



## 补充内容

### stackoverflow [Segmentation in Linux : Segmentation & Paging are redundant?](https://stackoverflow.com/questions/3029064/segmentation-in-linux-segmentation-paging-are-redundant)

I'm reading "Understanding Linux Kernel". This is the snippet that explains how Linux uses Segmentation which I didn't understand.

> Segmentation has been included in 80 x 86 microprocessors to encourage programmers to split their applications into logically related entities, such as subroutines or global and local data areas. However, Linux uses segmentation in a very limited way. *In fact, segmentation and paging are somewhat redundant*, because both can be used to separate the physical address spaces of processes: segmentation can assign a different linear address space to each process, while paging can map the same linear address space into different physical address spaces. Linux prefers paging to segmentation for the following reasons:
>
> Memory management is simpler when all processes use the same segment register values that is, when they share the same set of linear addresses.
>
> One of the design objectives of Linux is portability to a wide range of architectures; RISC architectures in particular have limited support for segmentation.
>
> All Linux processes running in User Mode use the same pair of segments to address instructions and data. These segments are called user code segment and user data segment , respectively. Similarly, all Linux processes running in Kernel Mode use the same pair of segments to address instructions and data: they are called kernel code segment and kernel data segment , respectively. Table 2-3 shows the values of the Segment Descriptor fields for these four crucial segments.

I'm unable to understand 1st and last paragraph.



[A](https://stackoverflow.com/a/3029086)

The `80x86` family of CPUs generate a real address by adding the contents of a CPU register called a segment register to that of the program counter. Thus by changing the segment register contents you can change the physical addresses that the program accesses. Paging does something similar by mapping the same **virtual address** to different **real addresses**. Linux using uses the latter - the **segment registers** for Linux processes will always have the same unchanging contents.





### stackexchange [Does Linux not use segmentation but only paging?](https://unix.stackexchange.com/questions/469253/does-linux-not-use-segmentation-but-only-paging)

*The Linux Programming Interface* shows the layout of a virtual address space of a process. Is each region in the diagram a segment?

[![enter image description here](https://i.stack.imgur.com/dvK8G.png)](https://i.stack.imgur.com/dvK8G.png)

From *Understanding The Linux Kernel*,

is it correct that the following means that the segmentation unit in MMU maps the segments and offsets within segments into the virtual memory address, and the paging unit then maps the virtual memory address to the physical memory address?

> The Memory Management Unit (MMU) transforms a logical address into a linear address by means of a hardware circuit called a segmentation unit; subsequently, a second hardware circuit called a paging unit transforms the linear address into a physical address (see Figure 2-1).

[![enter image description here](https://i.stack.imgur.com/916KY.png)](https://i.stack.imgur.com/916KY.png)

Then why does it say that Linux doesn't use segmentation but only paging?

> Segmentation has been included in 80x86 microprocessors to encourage programmers to split their applications into logically related entities, such as subroutines or global and local data areas. However, **Linux uses segmentation in a very limited way.** In fact, segmentation and paging are somewhat redundant, because both can be used to separate the physical address spaces of processes: segmentation can assign a different linear address space to each process, while paging can map the same linear address space into different physical address spaces. Linux prefers paging to segmentation for the following reasons:
>
> • Memory management is simpler when all processes use the same segment register values—that is, when they share the same set of linear addresses.
>
> • One of the design objectives of Linux is portability to a wide range of architectures; RISC architectures, in particular, have limited support for segmentation.
>
> The 2.6 version of Linux uses segmentation only when required by the 80x86 architecture.



[A](https://unix.stackexchange.com/a/469254)

*The x86-64 architecture does not use segmentation in long mode (64-bit mode).*

*Four of the segment registers: CS, SS, DS, and ES are forced to 0, and the limit to 2^64.*

https://en.wikipedia.org/wiki/X86_memory_segmentation#Later_developments

It is no longer possible for the OS to limit which ranges of the "linear addresses" are available. Therefore it cannot use segmentation for memory protection; it must rely entirely on paging.

Do not worry about the details of x86 CPUs which would only apply when running in the legacy 32-bit modes. Linux for the 32-bit modes is not used as much. It may even be considered "in a state of benign neglect for several years". See [32-Bit x86 support in Fedora](https://lwn.net/Articles/728207/) [LWN.net, 2017].

(It happens that 32-bit Linux does not use segmentation either. But you don't need to trust me on that, you can just ignore it :-).



[A](https://unix.stackexchange.com/a/469256)

As the `x86` has segments, it is not possible to not use them. But both `cs` (code segment) and `ds`(data segment) base addresses are set to zero, so the segmentation is not really used. An exception is thread local data, one of the normally unused segment registers points to **thread local data**. But that is mainly to avoid reserving one of the general purpose registers for this task.

It doesn't say that Linux doesn't use segmentation on the x86, as that would not be possible. You already highlighted one part, **Linux uses segmentation in a very limited way**. The second part is **Linux uses segmentation only when required by the 80x86 architecture**

You already quoted the reasons, paging is easier and more portable.


### wikipedia [x86 memory segmentation](https://en.wikipedia.org/wiki/X86_memory_segmentation) Later developments

