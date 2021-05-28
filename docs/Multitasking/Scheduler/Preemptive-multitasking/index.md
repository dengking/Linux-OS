# wikipedia [Preemption (computing)](https://en.wikipedia.org/wiki/Preemption_(computing))

In [computing](https://en.wikipedia.org/wiki/Computing), **preemption** is the act of temporarily interrupting a [task](https://en.wikipedia.org/wiki/Task_(computing)) being carried out by a [computer system](https://en.wikipedia.org/wiki/Computer), without requiring its cooperation, and with the intention of resuming the task at a later time. Such changes of the executed task are known as [context switches](https://en.wikipedia.org/wiki/Context_switch). It is normally carried out by a [privileged](https://en.wikipedia.org/wiki/Protection_ring) task or part of the system known as a preemptive [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)), which has the power to **preempt**, or interrupt, and later resume, other tasks in the system.



## User mode and kernel mode

see also: [Kernel preemption](https://en.wikipedia.org/wiki/Kernel_preemption)

In any given system design, some **operations** performed by the system may not be preemptible（可抢占的）. This usually applies to [kernel](https://en.wikipedia.org/wiki/Kernel_(operating_system)) functions and service [interrupts](https://en.wikipedia.org/wiki/Interrupt) which, if not permitted to [run to completion](https://en.wikipedia.org/wiki/Run_to_completion) （运行完成）, would tend to produce [race conditions](https://en.wikipedia.org/wiki/Race_condition) resulting in [deadlock](https://en.wikipedia.org/wiki/Deadlock). Barring（禁止） the scheduler from **preempting tasks** while they are processing kernel functions simplifies the kernel design at the expense of system responsiveness（ 禁止调度程序在处理内核函数时抢占任务，从而以系统响应为代价简化内核设计）. The distinction between [user mode](https://en.wikipedia.org/wiki/User_space) and [kernel mode](https://en.wikipedia.org/wiki/Ring_(computer_security)#Supervisor_mode), which determines privilege level within the system, may also be used to distinguish whether a task is currently preemptible.

Most modern systems have **preemptive kernels**, designed to permit tasks to be preempted even when in kernel mode. Examples of such systems are [Solaris](https://en.wikipedia.org/wiki/Solaris_(operating_system)) 2.0/SunOS 5.0,[[1\]](https://en.wikipedia.org/wiki/Preemption_(computing)#cite_note-1) [Windows NT](https://en.wikipedia.org/wiki/Windows_NT), [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel) (2.6.x and newer), [AIX](https://en.wikipedia.org/wiki/IBM_AIX) and some [BSD](https://en.wikipedia.org/wiki/BSD) systems ([NetBSD](https://en.wikipedia.org/wiki/NetBSD), since version 5).



## Preemptive multitasking



The term **preemptive multitasking** is used to distinguish a [multitasking operating system](https://en.wikipedia.org/wiki/Multitasking_operating_system), which permits preemption of tasks（允许抢占任务）, from a [cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking) system wherein processes or tasks must be explicitly programmed to [yield](https://en.wikipedia.org/wiki/Yield_(multithreading))（放弃执行，让渡） when they do not need system resources.

In simple terms: Preemptive multitasking involves the use of an [interrupt mechanism](https://en.wikipedia.org/wiki/Interrupt_mechanism) which suspends the currently executing process and invokes a [scheduler](https://en.wikipedia.org/wiki/Scheduler_(computing)) to determine which process should execute next. Therefore, all processes will get some amount of CPU time at any given time.

In preemptive multitasking, the operating system [kernel](https://en.wikipedia.org/wiki/Kernel_(computer_science)) can also initiate a [context switch](https://en.wikipedia.org/wiki/Context_switch) to satisfy the [scheduling policy](https://en.wikipedia.org/wiki/Scheduling_policy)'s priority constraint, thus preempting（抢占） the active task. In general, preemption means "prior seizure of". When the high priority task at that instance seizes（夺取） the currently running task, it is known as **preemptive scheduling**(抢占式调度）.

The term "preemptive multitasking" is sometimes mistakenly used when the intended meaning is more specific, referring instead to the class of scheduling policies known as *time-shared scheduling*, or *time-sharing*.

**Preemptive multitasking** allows the computer system to more reliably guarantee each process a regular "slice" of operating time. It also allows the system to rapidly deal with important external events like incoming data, which might require the immediate attention of one or another process.

At any specific time, processes can be grouped into two categories: those that are waiting for input or output (called "[I/O bound](https://en.wikipedia.org/wiki/IO_bound)"), and those that are fully utilizing the CPU ("[CPU bound](https://en.wikipedia.org/wiki/CPU_bound)"). In early systems, processes would often "poll", or "[busywait](https://en.wikipedia.org/wiki/Busy_waiting)" while waiting for requested input (such as disk, keyboard or network input). During this time, the process was not performing useful work, but still maintained complete control of the CPU. With the advent of **interrupts** and **preemptive multitasking**, these **I/O bound processes** could be "blocked", or put on hold, pending the arrival of the necessary data, allowing other processes to utilize the CPU. As the arrival of the requested data would generate an interrupt, blocked processes could be guaranteed a timely return to execution.

Although multitasking techniques were originally developed to allow multiple users to share a single machine, it soon became apparent that multitasking was useful regardless of the number of users. Many operating systems, from mainframes down to single-user personal computers and no-user [control systems](https://en.wikipedia.org/wiki/Control_systems) (like those in [robotic spacecraft](https://en.wikipedia.org/wiki/Robotic_spacecraft)), have recognized the usefulness of multitasking support for a variety of reasons. Multitasking makes it possible for a single user to run multiple applications at the same time, or to run "background" processes while retaining control of the computer.



### Time slice

The period of time for which a process is allowed to run in a preemptive multitasking system is generally called the *time slice* or *quantum*. The scheduler is run once every time slice to choose the next process to run. The length of each time slice can be critical to balancing **system performance** vs **process responsiveness** - if the time slice is too short then the scheduler will consume too much processing time, but if the time slice is too long, processes will take longer to respond to input.

An [interrupt](https://en.wikipedia.org/wiki/Interrupt) is scheduled to allow the [operating system](https://en.wikipedia.org/wiki/Operating_system) [kernel](https://en.wikipedia.org/wiki/Kernel_(computer_science)) to switch between processes when their time slices expire, effectively allowing the processor’s time to be shared between a number of tasks, giving the illusion that it is dealing with these tasks in parallel (simultaneously). The operating system which controls such a design is called a multi-tasking system.



### System support

> NOTE: 
>
> 目前主流OS默认都是preemptive multitasking



