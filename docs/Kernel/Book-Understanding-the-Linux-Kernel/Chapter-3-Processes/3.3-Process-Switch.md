# 3.3. Process Switch

> NOTE: 本节所描述的process switch的内容是加载next process，至于如何保存previous process，本节没有进行深入的描述。

To control the execution of processes, the kernel must be able to **suspend** the execution of the
process running on the CPU and **resume** the execution of some other process previously suspended.
This activity goes variously by the names ***process switch***, ***task switch***, or ***context switch***. The next
sections describe the elements of process switching in Linux.

## 3.3.1. Hardware Context

While each process can have its own **address space**, all processes have to share the **CPU registers**.
So before resuming the execution of a process, the kernel must ensure that each such register is
loaded with the value it had when the process was suspended.

The set of data that must be loaded into the registers before the process resumes its execution on
the CPU is called the ***hardware context*** . The hardware context is a subset of the ***process execution***
***context***, which includes all information needed for the process execution. In Linux, a part of the
**hardware context** of a process is stored in the **process descriptor**, while the remaining part is saved
in the **Kernel Mode stack**.

> NOTE : 上面这段话非常重要

In the description that follows, we will assume the  `prev` local variable refers to the **process descriptor**
of the process being switched out and  `next` refers to the one being switched in to replace it. We can thus define a **process switch** as the activity consisting of saving the **hardware context** of  `prev` and replacing it with the **hardware context** of  `next` . Because **process switches** occur quite often, it is important to minimize the time spent in saving and loading hardware contexts.

Old versions of Linux took advantage of the hardware support offered by the 80x86 architecture and performed a **process switch** through a  `far jmp` instruction [`*`] to the selector of the **Task State Segment Descriptor** of the  next process. While executing the instruction, the CPU performs a **hardware context switch** by automatically saving the old **hardware context** and loading a new one. But Linux 2.6 uses software to perform a **process switch** for the following reasons:

> [`*`] `far jmp` instructions modify both the  `cs` and  `eip` registers, while simple  `jmp` instructions modify only  `eip` 

- Step-by-step switching performed through a sequence of  `mov` instructions allows better control over the validity of the data being loaded. In particular, it is possible to check the values of the `ds` and  `es` **segmentation registers**, which might have been forged by a malicious user. This type of checking is not possible when using a single  `far jmp` instruction.
- The amount of time required by the old approach and the new approach is about the same. However, it is not possible to optimize a **hardware context switch**, while there might be room for improving the current switching code.

**Process switching** occurs only in **Kernel Mode**. The contents of all registers used by a process in **User Mode** have already been saved on the **Kernel Mode stack** before performing **process switching** (see Chapter 4). This includes the contents of the  `ss` and  `esp` pair that specifies the **User Mode stack pointer address**.

## 3.3.2. Task State Segment

The 80x86 architecture includes a specific segment type called the *Task State Segment* (TSS), to store hardware contexts. Although Linux doesn't use **hardware context switches**, it is nonetheless
forced to set up a TSS for each distinct CPU in the system. This is done for two main reasons:

- When an 80x86 CPU switches from **User Mode** to **Kernel Mode**, it fetches the address of the **Kernel Mode stack** from the TSS (see the sections "Hardware Handling of Interrupts and Exceptions" in Chapter 4 and "Issuing a System Call via the sysenter Instruction" in Chapter 10).
- When a User Mode process attempts to access an I/O port by means of an  `in` or  `out` instruction, the CPU may need to access an I/O Permission Bitmap stored in the TSS to verify whether the process is allowed to address the port.



### 3.3.2.1. The thread field

At every process switch, the **hardware context** of the process being replaced must be saved somewhere. It cannot be saved on the TSS, as in the original Intel design, because Linux uses a single TSS for each processor, instead of one for every process.

Thus, each **process descriptor** includes a field called  `thread` of type  `thread_struct` , in which the kernel saves the **hardware context** whenever the process is being switched out. As we'll see later, this data structure includes fields for most of the CPU registers, except the **general-purpose registers** such as  `eax` ,  `ebx` , etc., which are stored in the **Kernel Mode stack**.



## 3.3.3. Performing the Process Switch

A process switch may occur at just one well-defined point: the  schedule( ) function, which is discussed at length in Chapter 7. Here, we are only concerned with how the kernel performs a process switch.

Essentially, every process switch consists of two steps:

- Switching the Page Global Directory to install a new address space; we'll describe this step in
  Chapter 9.
- Switching the Kernel Mode stack and the hardware context, which provides all the information
  needed by the kernel to execute the new process, including the CPU registers.