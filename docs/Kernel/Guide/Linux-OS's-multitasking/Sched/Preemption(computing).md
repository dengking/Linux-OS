# [Preemption (computing)](https://en.wikipedia.org/wiki/Preemption_(computing))

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



Today, nearly all operating systems support **preemptive multitasking**, including the current versions of [Windows](https://en.wikipedia.org/wiki/Windows), [macOS](https://en.wikipedia.org/wiki/MacOS), [Linux](https://en.wikipedia.org/wiki/Linux) (including [Android](https://en.wikipedia.org/wiki/Android_(operating_system))) and [iOS](https://en.wikipedia.org/wiki/IOS_(Apple)).

Some of the earliest operating systems available to home users featuring preemptive multitasking were [Sinclair QDOS](https://en.wikipedia.org/wiki/Sinclair_QDOS) (1984[[2\]](https://en.wikipedia.org/wiki/Preemption_(computing)#cite_note-2)) and [Amiga OS](https://en.wikipedia.org/wiki/Amiga_OS) (1985). These both ran on [Motorola 68000](https://en.wikipedia.org/wiki/Motorola_68000)-family [microprocessors](https://en.wikipedia.org/wiki/Microprocessors) without memory management. Amiga OS used [dynamic loading](https://en.wikipedia.org/wiki/Dynamic_loading) of relocatable code blocks ("[hunks](https://en.wikipedia.org/wiki/Amiga_Hunk)" in Amiga jargon) to multitask preemptively all processes in the same flat address space.

Early [PC](https://en.wikipedia.org/wiki/Personal_Computer#The_IBM_PC) operating systems such as [MS-DOS](https://en.wikipedia.org/wiki/MS-DOS) and [PC DOS](https://en.wikipedia.org/wiki/PC_DOS), did not support multitasking at all, however alternative operating systems such as [MP/M-86](https://en.wikipedia.org/wiki/MP/M-86) (1981) and [Concurrent CP/M-86](https://en.wikipedia.org/wiki/Concurrent_CP/M-86) did support preemptive multitasking. Other [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems including [MINIX](https://en.wikipedia.org/wiki/MINIX) and [Coherent](https://en.wikipedia.org/wiki/Coherent_(operating_system)) provided preemptive multitasking on 1980s-era personal computers.

Later [DOS](https://en.wikipedia.org/wiki/DOS) versions natively supporting preemptive multitasking/multithreading include [Concurrent DOS](https://en.wikipedia.org/wiki/Concurrent_DOS), [Multiuser DOS](https://en.wikipedia.org/wiki/Multiuser_DOS), [Novell DOS](https://en.wikipedia.org/wiki/Novell_DOS) (later called [Caldera OpenDOS](https://en.wikipedia.org/wiki/Caldera_OpenDOS) and [DR-DOS](https://en.wikipedia.org/wiki/DR-DOS) 7.02 and higher). Since [Concurrent DOS 386](https://en.wikipedia.org/wiki/Concurrent_DOS_386), they could also run multiple DOS programs concurrently in [virtual DOS machines](https://en.wikipedia.org/wiki/Virtual_DOS_machine).

The earliest version of Windows to support a limited form of preemptive multitasking was [Windows 2.1x](https://en.wikipedia.org/wiki/Windows_2.1x), which used the [Intel 80386](https://en.wikipedia.org/wiki/Intel_80386)'s [Virtual 8086 mode](https://en.wikipedia.org/wiki/Virtual_8086_mode) to run DOS applications in [virtual 8086 machines](https://en.wikipedia.org/wiki/Virtual_machine), commonly known as "DOS boxes", which could be preempted. In [Windows 95, 98 and Me](https://en.wikipedia.org/wiki/Windows_9x), 32-bit applications were made preemptive by running each one in a separate address space, but 16-bit applications remained cooperative for backward compatibility.[[3\]](https://en.wikipedia.org/wiki/Preemption_(computing)#cite_note-how_win95-3) In Windows 3.1x (protected mode), the kernel and virtual device drivers ran preemptively, but all 16-bit applications were non-preemptive and shared the same address space.

Preemptive multitasking has always been supported by [Windows NT](https://en.wikipedia.org/wiki/Windows_NT) (all versions), [OS/2](https://en.wikipedia.org/wiki/OS/2) (native applications), [Unix](https://en.wikipedia.org/wiki/Unix) and [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems (such as [Linux](https://en.wikipedia.org/wiki/Linux), [BSD](https://en.wikipedia.org/wiki/BSD) and [macOS](https://en.wikipedia.org/wiki/MacOS)), [VMS](https://en.wikipedia.org/wiki/OpenVMS), [OS/360](https://en.wikipedia.org/wiki/OS/360), and many other operating systems designed for use in the academic and medium-to-large business markets.

Although there were plans to upgrade the cooperative multitasking found in the [classic Mac OS](https://en.wikipedia.org/wiki/Classic_Mac_OS) to a preemptive model (and a preemptive API did exist in [Mac OS 9](https://en.wikipedia.org/wiki/Mac_OS_9), although in a limited sense[[4\]](https://en.wikipedia.org/wiki/Preemption_(computing)#cite_note-Pre-emptive_Multitasking-4)), these were abandoned in favor of [Mac OS X (now called macOS)](https://en.wikipedia.org/wiki/MacOS) that, as a hybrid of the old Mac System style and [NeXTSTEP](https://en.wikipedia.org/wiki/NeXTSTEP), is an operating system based on the [Mach](https://en.wikipedia.org/wiki/Mach_(kernel)) kernel and derived in part from [BSD](https://en.wikipedia.org/wiki/BSD), which had always provided Unix-like preemptive multitasking.



