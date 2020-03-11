# [Kernel preemption](https://en.wikipedia.org/wiki/Kernel_preemption)

**Kernel preemption** is a method used mainly in [monolithic](https://en.wikipedia.org/wiki/Monolithic_kernel) and [hybrid](https://en.wikipedia.org/wiki/Hybrid_kernel) [kernels](https://en.wikipedia.org/wiki/Kernel_(computing)) where all or most [device drivers](https://en.wikipedia.org/wiki/Device_drivers) are run in [kernel space](https://en.wikipedia.org/wiki/Kernel_space), whereby the [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)) is permitted to forcibly perform a [context switch](https://en.wikipedia.org/wiki/Context_switch) (i.e. preemptively schedule; on behalf of a runnable and higher priority process) on a driver or other part of the kernel during its execution, rather than [co-operatively](https://en.wikipedia.org/wiki/Computer_multitasking#Cooperative_multitasking.2Ftime-sharing) waiting for the driver or kernel function (such as a [system call](https://en.wikipedia.org/wiki/System_call)) to complete its execution and return control of the processor to the scheduler.[[1\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-kernelnewbies-1)[[2\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-lwn-2)[[3\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-3)[[4\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-4)

There are two main benefits to this method in monolithic and hybrid kernels, and answer one of the main criticisms of monolithic kernels from [microkernel](https://en.wikipedia.org/wiki/Microkernel) advocates, which is that:

- A device driver can enter an infinite loop or other unrecoverable state, crashing the whole system.[[1\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-kernelnewbies-1)
- Some drivers and system calls on monolithic kernels are slow to execute, and cannot return control of the processor to the scheduler or other program until they complete execution.[[2\]](https://en.wikipedia.org/wiki/Kernel_preemption#cite_note-lwn-2)

## See also

- [Linux kernel preemption](https://en.wikipedia.org/wiki/Linux_kernel_preemption)

