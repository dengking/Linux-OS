

# 1.6.1. The Process/Kernel Model

When a program is executed in **User Mode**, it cannot directly access the **kernel data structures** or the
**kernel programs**. When an application executes in **Kernel Mode**, however, these restrictions no
longer apply. Each CPU model provides special **instructions** to switch from **User Mode** to **Kernel Mode**
and vice versa. A program usually executes in User Mode and switches to Kernel Mode only when
requesting a service provided by the kernel. When the kernel has satisfied the program's request, it
puts the program back in **User Mode**.

> NOTE: See also
>
> - [User space](https://en.wikipedia.org/wiki/User_space)
> - [CPU modes](https://en.wikipedia.org/wiki/CPU_modes)
> - [Protection ring](https://en.wikipedia.org/wiki/Protection_ring)

Processes are dynamic entities that usually have a limited life span within the system. The task of
creating, eliminating, and synchronizing the existing processes is delegated to a group of routines in
the kernel.

**The kernel itself is not a process but a process manager**. The process/kernel model assumes that
processes that require a **kernel service** use specific programming constructs called **system calls** .
Each **system call** sets up the group of parameters that identifies the **process request** and then
executes the hardware-dependent CPU **instruction** to switch from **User Mode** to **Kernel Mode**.

> NOTE: See also
>
> - [System call](https://en.wikipedia.org/wiki/System_call)

Besides user processes, Unix systems include a few **privileged processes** called **kernel threads** with
the following characteristics:

- They run in Kernel Mode in the kernel address space.
- They do not interact with users, and thus do not require terminal devices.
- They are usually created during system startup and remain alive until the system is shut down.

> NOTE : 
>
> - [What is a Kernel thread?](https://stackoverflow.com/questions/9481055/what-is-a-kernel-thread)
> - [Understanding Kernel Threads](https://www.ibm.com/support/knowledgecenter/en/ssw_aix_72/kernelextension/kern_threads.html)

On a uniprocessor system, only one process is running at a time, and it may run either in User or in Kernel Mode. If it runs in **Kernel Mode**, the processor is executing some **kernel routine**. Figure 1-2 illustrates examples of transitions between User and Kernel Mode. Process 1 in **User Mode** issues a **system call**, after which the process switches to **Kernel Mode**, and the **system call** is serviced. Process 1 then resumes execution in **User Mode** until a **timer interrupt** occurs, and the **scheduler** is activated in **Kernel Mode**. A **process switch** takes place, and Process 2 starts its execution in **User Mode** until a hardware device raises an interrupt. As a consequence of the interrupt, Process 2 switches to **Kernel Mode** and services the interrupt.

![](../Figure1-2Transitions-between-User-and-Kernel-Mode.jpg)



**Unix kernels** do much more than handle **system calls**; in fact, **kernel routines** can be activated in
several ways:

1、A process invokes a **system call**.

2、The CPU executing the process signals an **exception**, which is an unusual condition such as an
invalid instruction. The kernel handles the exception on behalf of the process that caused it.

3、A peripheral device issues an **interrupt signal** to the CPU to notify it of an event such as a
request for attention, a status change, or the completion of an I/O operation. Each **interrupt
signal** is dealt by a kernel program called an **interrupt handler**. Because peripheral devices
operate asynchronously with respect to the CPU, interrupts occur at unpredictable times.

4、A **kernel thread** is executed. Because it runs in Kernel Mode, the corresponding program must
be considered part of the kernel.

