# Understanding.The.Linux.kernel.3rd.Edition



在1.6.3. Reentrant Kernels中给出了它的定义：

> A **kernel control path** denotes the sequence of instructions executed by the kernel to handle a system call, an exception, or an interrupt.

1.6.4. Process Address Space中指出kernel control path执行在它自己的kernel stack：

> kernel control path refers to its own private kernel stack.

1.6.5. Synchronization and Critical Regions中指出kernel control path的Synchronization

4.1. The Role of Interrupt Signals中指出kernel control path的执行：

> There are some things in this chapter that will remind you of the context switch described in the previous chapter, carried out when a kernel substitutes one process for another. But there is a key
> difference between interrupt handling and process switching: the code executed by an interrupt or
> by an exception handler is not a process. Rather, it is a kernel control path that runs at the expense
> of the same process that was running when the interrupt occurred (see the later section "Nested
> Execution of Exception and Interrupt Handlers"). As a kernel control path, the interrupt handler is
> lighter than a process (it has less context and requires less time to set up or tear down).



# [Kernel Control Path Definition](http://www.linfo.org/kernel_control_path.html)