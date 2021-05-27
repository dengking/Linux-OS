# 1.4. Basic Operating System Concepts

Each computer system includes a basic set of programs called the *operating system*. The most important program in the set is called the *kernel*. It is loaded into RAM when the system boots and contains many critical procedures that are needed for the system to operate. The other programs are less crucial utilities; they can provide a wide variety of interactive experiences for the user as well as doing all the jobs the user bought the computer for but the essential shape and capabilities of the system are determined by the **kernel**. The kernel provides key facilities to everything else on the system and determines many of the characteristics of higher software. Hence, we often use the term "operating system" as a synonym for "kernel."

> NOTE: See also
>
> - wikipedia [Operating system](https://en.wikipedia.org/wiki/Operating_system)
> - wikipedia [Kernel (operating system)](https://en.wikipedia.org/wiki/Kernel_(operating_system))

The operating system must fulfill two main objectives:

1、Interact with the hardware components, servicing all low-level programmable elements included in the hardware platform.

2、Provide an execution environment to the applications that run on the computer system (the so-called user programs).

> NOTE: 
>
> OS的两大作用

Some operating systems allow all user programs to directly play with the hardware components (a typical example is MS-DOS ). In contrast, a Unix-like operating system hides all low-level details concerning the physical organization of the computer from applications run by the user. When a program wants to use a hardware resource, it must issue a request to the operating system. The kernel evaluates the request and, if it chooses to grant the resource, interacts with the proper hardware components on behalf of the user program.

> NOTE: 
>
> 一、上面这一段讲的是Linux kernel的设计原则: "Linux kernel design-monolithic集成kernel-system call as request to hardware."
>
> 二、下面这一段讲的是Linux kernel是如何实现上述设计理念的

To enforce this mechanism, modern operating systems rely on the availability of specific hardware features that forbid(禁止) user programs to directly interact with low-level hardware components or to access arbitrary memory locations. In particular, the hardware introduces at least two different **execution modes** for the CPU: a nonprivileged mode for user programs and a privileged mode for the kernel. Unix calls these **User Mode** and **Kernel Mode** , respectively.

> NOTE: 
>
> See also
>
> - [User space](https://en.wikipedia.org/wiki/User_space)
> - [CPU modes](https://en.wikipedia.org/wiki/CPU_modes)
> - [Protection ring](https://en.wikipedia.org/wiki/Protection_ring)

In the rest of this chapter, we introduce the basic concepts that have motivated the design of Unix over the past two decades, as well as Linux and other operating systems. While the concepts are probably familiar to you as a Linux user, these sections try to delve into them a bit more deeply than usual to explain the requirements they place on an operating system kernel. These broad considerations refer to virtually all Unix-like systems. The other chapters of this book will hopefully help you understand the Linux kernel internals.

## 1.4.1. Multiuser Systems

A *multiuser system* is a computer that is able to *concurrently* and *independently* execute several applications belonging to two or more **users**. *Concurrently* means that applications can be active at the same time and contend for the various resources such as CPU, memory, hard disks, and so on. *Independently* means that each application can perform its task with no concern for what the applications of the other users are doing. Switching from one application to another, of course, slows down each of them and affects the response time seen by the users. Many of the complexities of modern operating system kernels, which we will examine in this book, are present to minimize the delays enforced on each program and to provide the user with responses that are as fast as possible.

**Multiuser operating systems** must include several features:

- An **authentication mechanism** for verifying the user's identity
- A **protection mechanism** against buggy user programs that could block other applications running in the system
- A **protection mechanism** against malicious user programs that could interfere with or spy on the activity of other users
- An **accounting mechanism** that limits the amount of resource units assigned to each user

To ensure **safe protection mechanisms**, operating systems must use the hardware protection associated with the **CPU privileged mode**. Otherwise, a user program would be able to directly access the system circuitry and overcome the imposed bounds. Unix is a multiuser system that enforces the **hardware protection** of **system resources**.

## 1.4.2. Users and Groups

In a **multiuser system**, each user has a private space on the machine; typically, he owns some quota of the disk space to store files, receives private mail messages, and so on. The operating system must ensure that the private portion of a user space is visible only to its owner. In particular, it must ensure that no user can exploit a system application for the purpose of violating the private space of another user.

All users are identified by a unique number called the *User ID*, or *UID*. Usually only a restricted number of persons are allowed to make use of a computer system. When one of these users starts a working session, the system asks for a login name and a password. If the user does not input a valid pair, the system denies access. Because the password is assumed to be secret, the user's privacy is ensured.

To selectively share material with other users, each user is a member of one or more *user groups* , which are identified by a unique number called a *user group ID* . Each file is associated with exactly one group. For example, access can be set so the user owning the file has read and write privileges, the group has read-only privileges, and other users on the system are denied access to the file.

Any Unix-like operating system has a special user called *root* or *superuser* . The system administrator must log in as root to handle user accounts, perform maintenance tasks such as system backups and program upgrades, and so on. The root user can do almost everything, because the operating system does not apply the usual protection mechanisms to her. In particular, the root user can access every file on the system and can manipulate every running user program.



## 1.4.3. Processes

> NOTE: 本节中的process指的是标准[Process](https://en.wikipedia.org/wiki/Process_(computing)) 

All operating systems use one fundamental abstraction: the *process*. A process can be defined either as "an instance of a program in execution" or as the "execution context" of a running program. In traditional operating systems, a process executes a single sequence of instructions in an *address space*; the *address space* is the set of memory addresses that the process is allowed to reference. Modern operating systems allow processes with multiple **execution flows** that is, multiple sequences of instructions executed in the same **address space**.

> NOTE: 每个execution flow对应的是一个thread

Multiuser systems must enforce an execution environment in which several processes can be active concurrently and contend for system resources, mainly the CPU. Systems that allow concurrent active processes are said to be *multiprogramming* or *multiprocessing* . `[*]` It is important to distinguish programs from processes; several processes can execute the same program concurrently, while the same process can execute several programs sequentially.

> `[*]` Some multiprocessing operating systems are not multiuser; an example is Microsoft Windows 98.

On uniprocessor systems, just one process can hold the CPU, and hence just one **execution flow** can
progress at a time. In general, the number of CPUs is always restricted, and therefore only a few processes can progress at once. An operating system component called the *scheduler* chooses the process that can progress. Some operating systems allow only nonpreemptable processes, which means that the scheduler is invoked only when a process voluntarily relinquishes the CPU. But processes of a multiuser system must be preemptable; the operating system tracks how long each process holds the CPU and periodically activates the scheduler.

> NOTE: See also
>
> - [Single-tasking and multi-tasking](https://en.wikipedia.org/wiki/Operating_system#Single-tasking_and_multi-tasking)
> - [Preemption (computing)](https://en.wikipedia.org/wiki/Preemption_(computing))

Unix is a multiprocessing operating system with preemptable processes . 

Unix-like operating systems adopt a *process/kernel model* . Each process has the illusion that it's the only process on the machine, and it has **exclusive access** to the operating system services. Whenever a process makes a **system call** (i.e., a request to the kernel, see Chapter 10), the hardware changes the **privilege mode** from **User Mode** to **Kernel Mode**, and the process starts the execution of a kernel procedure with a strictly limited purpose. In this way, the operating system acts within the execution context of the process in order to satisfy its request. Whenever the request is fully satisfied, the kernel procedure forces the  hardware to return to User Mode and the process continues its execution from the instruction following the system call.

> NOTE: *process/kernel model*会在1.6.1. The Process/Kernel Model节进行详细介绍。

## 1.4.4. Kernel Architecture

As stated before, most Unix kernels are monolithic: each **kernel layer** is integrated into the whole kernel program and runs in **Kernel Mode** on behalf of the **current process**. In contrast, microkernel operating systems demand a very small set of functions from the kernel, generally including a few **synchronization primitives**, a simple **scheduler**, and an **interprocess communication mechanism**. Several system processes that run on top of the **microkernel** implement other **operating system-layer functions**, like **memory allocators**, **device drivers**, and **system call handlers**.

Although academic research on operating systems is oriented toward **microkernels** , such operating systems are generally slower than monolithic ones, because the explicit message passing between the different layers of the operating system has a cost. However, **microkernel** operating systems might have some theoretical advantages over **monolithic** ones. **Microkernels** force the system programmers to adopt a **modularized** approach, because each operating system layer is a relatively independent program that must interact with the other layers through well-defined and clean software interfaces. Moreover, an existing microkernel operating system can be easily ported to other architectures fairly easily, because all hardware-dependent components are generally encapsulated in the microkernel code. Finally, microkernel operating systems tend to make better use of random access memory (RAM) than monolithic ones,  because system processes that aren't implementing needed functionalities might be swapped out or destroyed. To achieve many of the theoretical advantages of microkernels without introducing performance penalties, the Linux kernel offers **modules** . A module is an object file whose code can be linked to (and unlinked from) the kernel at runtime. The object code usually consists of a set of functions that implements a filesystem, a device driver, or other features at the kernel's upper layer. The module, unlike the external layers of microkernel operating systems, does not run as a specific process. Instead, it is executed in **Kernel Mode** on behalf of the current process, like any other statically linked kernel function.

The main advantages of using modules include:

*modularized approach*

Because any module can be linked and unlinked at runtime, system programmers must introduce well-defined software interfaces to access the data structures handled by modules. This makes it easy to develop new modules.

*Platform independence*

Even if it may rely on some specific hardware features, a module doesn't depend on a fixed hardware platform. For example, a disk driver module that relies on the SCSI standard works as well on an IBM-compatible PC as it does on Hewlett-Packard's Alpha.

*Frugal main memory usage*

A module can be linked to the running kernel when its functionality is required and unlinked when it is no longer useful; this is quite useful for small embedded systems.

*No performance penalty*

Once linked in, the object code of a module is equivalent to the object code of the statically linked kernel. Therefore, no explicit message passing is required when the functions of the module are invoked. `[*]`

> `[*]` A small performance penalty occurs when the module is linked and unlinked. However, this penalty can be compared to the penalty caused by the creation and deletion of system processes in microkernel operating systems.

