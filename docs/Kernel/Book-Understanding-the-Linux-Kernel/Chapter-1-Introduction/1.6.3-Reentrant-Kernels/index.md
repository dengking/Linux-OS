# 1.6.3. Reentrant Kernels

> NOTE: 从一个内核设计者的角度来思考本节的内容，将更加容易掌握作者所要传达的思想。内核的设计者会追求系统能够快速地响应用户的请求，系统能够高效地运行，系统需要尽可能的压缩CPU的空闲时间，让CPU更多地进行运转。所以，它就需要在某个请求暂时无法完成的情况下，将它挂起并转向另外一个请求；当该请求的执行条件满足的时候再将它重启；另外，kernel还需要处理无法预测何时会出现的各种interrupt和exception，挂起当前的请求转去执行相应的handler。这种能力就是本节所述的*reentrant*。显然这种设计能够最大程度地保证系统的高效。这种设计也不可避免地导致系统的复杂，正如在本节后面所述的， 系统是在多个*kernel control path*中交错运行的，这种设计会派生出一系列的问题，比如将在1.6.5. Synchronization and Critical Regions中介绍的race condition，所以它kernel的实现提出了更高的要求。当然可以预期的是，系统是在这样的交错中不断向前进的。
>
> 如何来实现reentrant kernel呢？这是一个需要系统地进行设计才能够解决的问题，下面总结了和这个问题相关的一些章节：
>
> - 1.6.4. Process Address Space
>
>   Kernel control path refers to its own private kernel stack.
>
> - 1.6.5. Synchronization and Critical Regions
>
>   描述了kernel control path的Synchronization
>
> 为了便于描述reentrant kernel的实现，本段中作者提出了*kernel control path*的概念，这个概念表示了kernel所有的可能的活动，主要包括如下两种情况：
>
> - system call
> - interrupt and exception
>
> 也就是说：
>
> 当process向kernel请求一个system call，此时kernel中就执行此system call，使用*kernel control path*概念来进行理解的话，则是kernel创建了一个执行这个system call的kernel control path；
>
> 当产生interrupt或exception，此时kernel转去执行它们对应的handler，使用*kernel control path*概念来进行理解的话，可以认为kernel创建了一个执行这个handler的kernel control path；
>
> 为什么要使用*kernel control path*概念来进行描述呢？因为我们知道，operating system的kernel的执行情况是非常复杂的，它需要同时处理非常多的事情，比如process请求的system call，在此过程中是会伴随中随时可能发生的interrupt和exception的。前面我们已经铺垫了，kernel为了保持高效，可能需要挂起正在执行的流程转去执行另外一个流程，而后在重启之前挂起的流程。此处所谓的流程，我们使用更加专业的术语就是kernel control path。显然与function相比，kernel control path蕴含着更加丰富的，更加符合kernel调度情况的内涵，比如它能够表示kernel的suspend，resume，能够表示多个control path的interleave。这种通过创造新的概念来说表述更加便利的做法是在各种学科非常普遍的。
>
> 关于在这些情况下，kernel control path的一些执行细节，比如kernel control path和process之间的关联是本书中会一直强调的内容，需要进行一下总结，其中最最典型的就是kernel control path runs on behalf of process。为了今后便于快速地检索到这些内容，现将本书中所有的与此相关内容的位置全部都整理到这里：
>
> - chapter 1.6.3. Reentrant Kernels
>
>   本节的后半部分对kernel control path的一些可能情况进行了枚举，并描述了这些情况下，kernel control path和process之间的关系
>
> - Chapter 4. Interrupts and Exceptions
>
>   主要描述了Interrupts and Exceptions触发的kernel control path的执行情况。并且其中还对比了interrupt 触发的kernel control path和system call触发的kernel control path之间的差异等内容。
>
> 下面是一些补充内容：
>
> linfo [Kernel Control Path Definition](http://www.linfo.org/kernel_control_path.html)



All Unix kernels are *reentrant*. This means that several processes（指的是lightweight process） may be executing in **Kernel Mode** at the same time. Of course, on uniprocessor systems, only one process can progress, but **many** can be blocked in **Kernel Mode** when waiting for the CPU or the completion of some I/O operation. For instance, after issuing a read to a disk on behalf of a process, the kernel lets the **disk controller** handle it and resumes executing other processes. An **interrupt** notifies the kernel when the device has satisfied the read, so the former process can resume the execution.

One way to provide **reentrancy** is to write functions so that they modify only **local variables** and do not alter **global data structures**. Such functions are called *reentrant functions* . But a **reentrant kernel** is not limited only to such **reentrant functions** (although that is how some **real-time kernels** are implemented). Instead, the kernel can include **nonreentrant functions** and use **locking mechanisms** to ensure that only one process can execute a **nonreentrant function** at a time.

If a **hardware interrupt** occurs, a **reentrant kernel** is able to suspend the current running process even if that process is in **Kernel Mode**. This capability is very important, because it improves the  throughput of the **device controllers** that issue interrupts. Once a device has issued an interrupt, it waits until the **CPU acknowledges** it. If the kernel is able to answer quickly, the **device controller** will be able to perform other tasks while the CPU handles the interrupt.

Now let's look at **kernel reentrancy** and its impact on the organization of the kernel. A *kernel control path* denotes the sequence of instructions executed by the kernel to handle a **system call**, an **exception**, or an **interrupt**.

In the simplest case, the CPU executes a **kernel control path** sequentially from the first instruction to
the last. When one of the following events occurs, however, the CPU interleaves the **kernel control paths** :

1、A process executing in User Mode invokes a **system call**, and the corresponding **kernel control path** verifies that the request cannot be satisfied immediately; it then invokes the **scheduler** to select a new process to run. As a result, a **process switch** occurs. The first **kernel control path** is left unfinished, and the CPU resumes the execution of some other **kernel control path**. In this case, the two **control paths** are executed on behalf of two different processes.

2、The CPU detects an exception for example, access to a page not present in RAM while running a **kernel control path**. The first control path is suspended, and the CPU starts the execution of a suitable procedure. In our example, this type of procedure can allocate a new page for the process and read its contents from disk. When the procedure terminates, the first control path can be resumed. In this case, the two control paths are executed on behalf of the same process.

3、A hardware interrupt occurs while the CPU is running a kernel control path with the interrupts enabled. The first kernel control path is left unfinished, and the CPU starts processing another kernel control path to handle the interrupt. The first kernel control path resumes when the interrupt handler terminates. In this case, the two kernel control paths run in the execution context of the same process, and the total system CPU time is accounted to it. However, the interrupt handler doesn't necessarily operate on behalf of the process.

4、An interrupt occurs while the CPU is running with kernel preemption enabled, and a higher priority process is runnable. In this case, the first kernel control path is left unfinished, and the CPU resumes executing another kernel control path on behalf of the higher priority process. This occurs only if the kernel has been compiled with kernel preemption support.

Figure 1-3 illustrates a few examples of noninterleaved and interleaved kernel control paths. Three different CPU states are considered:

1、Running a process in User Mode (`User`)

2、Running an exception or a system call handler (`Excp`)

3、Running an interrupt handler (`Intr`)

![](../Figure-1-3-Interleaving-of-kernel-control-paths.jpg)

