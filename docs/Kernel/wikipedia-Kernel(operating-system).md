# [Kernel (operating system)](https://en.wikipedia.org/wiki/Kernel_(operating_system))

The **kernel** is a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is the core of a computer's [operating system](https://en.wikipedia.org/wiki/Operating_system), with complete control over everything in the system. On most systems, it is one of the first programs loaded on [start-up](https://en.wikipedia.org/wiki/Booting) (after the [bootloader](https://en.wikipedia.org/wiki/Bootloader)). It handles the rest of start-up as well as [input/output](https://en.wikipedia.org/wiki/Input/output) requests from [software](https://en.wikipedia.org/wiki/Software), translating them into [data-processing](https://en.wikipedia.org/wiki/Data_processing) instructions for the [central processing unit](https://en.wikipedia.org/wiki/Central_processing_unit). It handles memory and [peripherals](https://en.wikipedia.org/wiki/Peripheral) (外设) like keyboards, monitors, printers, and speakers.

The critical code of the kernel is usually loaded into a **separate area** of memory, which is protected from access by [application programs](https://en.wikipedia.org/wiki/Application_software) or other, less critical parts of the operating system. The kernel performs its tasks, such as running processes, managing hardware devices such as the [hard disk](https://en.wikipedia.org/wiki/Hard_disk), and handling interrupts, in this protected [kernel space](https://en.wikipedia.org/wiki/Kernel_space). In contrast, everything a user does is in [user space](https://en.wikipedia.org/wiki/User_space): writing text in a text editor, running programs in a [GUI](https://en.wikipedia.org/wiki/Graphical_user_interface), etc. This **separation** prevents **user data** and **kernel data** from interfering with each other and causing instability and slowness, as well as preventing malfunctioning **application programs** from crashing the entire operating system.

> NOTE:隔离带来安全

The kernel's [interface](https://en.wikipedia.org/wiki/Application_programming_interface) is a [low-level](https://en.wikipedia.org/wiki/High-_and_low-level) [abstraction layer](https://en.wikipedia.org/wiki/Abstraction_layer). When a [process](https://en.wikipedia.org/wiki/Process_(computing)) makes requests of the kernel, it is called a [system call](https://en.wikipedia.org/wiki/System_call). Kernel designs differ in how they manage these system calls and [resources](https://en.wikipedia.org/wiki/Resource_(computer_science)). A [monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel) runs all the operating system [instructions](https://en.wikipedia.org/wiki/Instruction_set) in the same [address space](https://en.wikipedia.org/wiki/Address_space) for speed. A [microkernel](https://en.wikipedia.org/wiki/Microkernel) runs most processes in user space, for [modularity](https://en.wikipedia.org/wiki/Modular_programming). 



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8f/Kernel_Layout.svg/220px-Kernel_Layout.svg.png)

> A kernel connects the **application software** to the **hardware** of a computer.

## Function of Kernel

关于内核的功能，在本篇文章中没有进行详细的分类介绍，所以此处进行省略；在[Operating system](https://en.wikipedia.org/wiki/Operating_system)的[Kernel](https://en.wikipedia.org/wiki/Operating_system#Kernel)章节进行了非常好的介绍，推荐去阅读。



## [Kernel design decisions](https://en.wikipedia.org/wiki/Kernel_(operating_system)#Kernel_design_decisions)



## [Kernel-wide design approaches](https://en.wikipedia.org/wiki/Kernel_(operating_system)#Kernel-wide_design_approaches)

Naturally, the above listed tasks and features can be provided in many ways that differ from each other in design and implementation.

The principle of [*separation of mechanism and policy*](https://en.wikipedia.org/wiki/Separation_of_mechanism_and_policy) （机制和政策的分离） is the substantial difference between the philosophy of **micro** and **monolithic** kernels. Here a *mechanism* is the support that allows the implementation of many different policies, while a policy is a particular "mode of operation". For instance, a mechanism may provide for user log-in attempts to call an authorization server to determine whether access should be granted; a policy may be for the authorization server to request a password and check it against an encrypted password stored in a database. Because the mechanism is generic, the policy could more easily be changed (e.g. by requiring the use of a [security token](https://en.wikipedia.org/wiki/Security_token)) than if the mechanism and policy were integrated in the same module.

In minimal microkernel just some very basic policies are included, and its mechanisms allows what is running on top of the kernel (the remaining part of the operating system and the other applications) to decide which policies to adopt (as memory management, high level process scheduling, file system management, etc.). A monolithic kernel instead tends to include many policies, therefore restricting the rest of the system to rely on them.

[Per Brinch Hansen](https://en.wikipedia.org/wiki/Per_Brinch_Hansen) presented arguments in favour of **separation of mechanism and policy**. The failure to properly fulfill this separation is one of the major causes of the lack of substantial innovation in existing operating systems, a problem common in computer architecture. The monolithic design is induced by the "kernel mode"/"user mode" architectural approach to protection (technically called [hierarchical protection domains](https://en.wikipedia.org/wiki/Hierarchical_protection_domains)), which is common in conventional commercial systems; in fact, every module needing protection is therefore preferably included into the kernel. This link between monolithic design and "privileged mode" can be reconducted to the key issue of mechanism-policy separation; in fact the "privileged mode" architectural approach melds together the protection mechanism with the security policies, while the major alternative architectural approach, [capability-based addressing](https://en.wikipedia.org/wiki/Capability-based_addressing), clearly distinguishes between the two, leading naturally to a microkernel design (see [Separation of protection and security](https://en.wikipedia.org/wiki/Separation_of_protection_and_security)).

While [monolithic kernels](https://en.wikipedia.org/wiki/Monolithic_kernel) execute all of their code in the same address space ([kernel space](https://en.wikipedia.org/wiki/Kernel_space)), [microkernels](https://en.wikipedia.org/wiki/Microkernel) try to run most of their services in user space, aiming to improve maintainability and modularity of the codebase. Most kernels do not fit exactly into one of these categories, but are rather found in between these two designs. These are called [hybrid kernels](https://en.wikipedia.org/wiki/Hybrid_kernel). More exotic designs such as [nanokernels](https://en.wikipedia.org/wiki/Nanokernel) and [exokernels](https://en.wikipedia.org/wiki/Exokernel) are available, but are seldom used for production systems. The [Xen](https://en.wikipedia.org/wiki/Xen)hypervisor, for example, is an exokernel.



### Monolithic kernels

Main article: [Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/Kernel-simple.svg/170px-Kernel-simple.svg.png)



Diagram of a monolithic kernel

In a monolithic kernel, all OS services run along with the main kernel thread, thus also residing in the same memory area. This approach provides rich and powerful hardware access. Some developers, such as [UNIX](https://en.wikipedia.org/wiki/Unix)developer [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson), maintain that it is "easier to implement a monolithic kernel"[[30\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Linuxisobsoletedebate-30) than microkernels. The main disadvantages of monolithic kernels are the dependencies between system components – a bug in a device driver might crash the entire system – and the fact that large kernels can become very difficult to maintain.

Monolithic kernels, which have traditionally been used by Unix-like operating systems, contain all the operating system core functions and the device drivers. This is the traditional design of UNIX systems. A monolithic kernel is one single program that contains all of the code necessary to perform every kernel related task. Every part which is to be accessed by most programs which cannot be put in a library is in the kernel space: Device drivers, Scheduler, Memory handling, File systems, Network stacks. Many system calls are provided to applications, to allow them to access all those services. A monolithic kernel, while initially loaded with subsystems that may not be needed, can be tuned to a point where it is as fast as or faster than the one that was specifically designed for the hardware, although more relevant in a general sense. Modern monolithic kernels, such as those of [Linux](https://en.wikipedia.org/wiki/Linux) and [FreeBSD](https://en.wikipedia.org/wiki/FreeBSD), both of which fall into the category of Unix-like operating systems, feature the ability to load modules at runtime, thereby allowing easy extension of the kernel's capabilities as required, while helping to minimize the amount of code running in kernel space. In the monolithic kernel, some advantages hinge on these points:

- Since there is less software involved it is faster.
- As it is one single piece of software it should be smaller both in source and compiled forms.
- Less code generally means fewer bugs which can translate to fewer security problems.

Most work in the monolithic kernel is done via system calls. These are interfaces, usually kept in a tabular structure, that access some subsystem within the kernel such as disk operations. Essentially calls are made within programs and a checked copy of the request is passed through the system call. Hence, not far to travel at all. The monolithic Linux kernel can be made extremely small not only because of its ability to dynamically load modules but also because of its ease of customization. In fact, there are some versions that are small enough to fit together with a large number of utilities and other programs on a single floppy disk and still provide a fully functional operating system (one of the most popular of which is [muLinux](https://en.wikipedia.org/wiki/MuLinux)). This ability to miniaturize its kernel has also led to a rapid growth in the use of Linux in [embedded systems](https://en.wikipedia.org/wiki/Embedded_systems).

These types of kernels consist of the core functions of the operating system and the device drivers with the ability to load modules at runtime. They provide rich and powerful abstractions of the underlying hardware. They provide a small set of simple hardware abstractions and use applications called servers to provide more functionality. This particular approach defines a high-level virtual interface over the hardware, with a set of system calls to implement operating system services such as process management, concurrency and memory management in several modules that run in supervisor mode. This design has several flaws and limitations:

- Coding in kernel can be challenging, in part because one cannot use common libraries (like a full-featured [libc](https://en.wikipedia.org/wiki/C_standard_library)), and because one needs to use a source-level debugger like [gdb](https://en.wikipedia.org/wiki/GNU_Debugger). Rebooting the computer is often required. This is not just a problem of convenience to the developers. When debugging is harder, and as difficulties become stronger, it becomes more likely that code will be "buggier".
- Bugs in one part of the kernel have strong side effects; since every function in the kernel has all the privileges, a bug in one function can corrupt data structure of another, totally unrelated part of the kernel, or of any running program.
- Kernels often become very large and difficult to maintain.
- Even if the modules servicing these operations are separate from the whole, the code integration is tight and difficult to do correctly.
- Since the modules run in the same [address space](https://en.wikipedia.org/wiki/Address_space), a bug can bring down the entire system.
- Monolithic kernels are not portable; therefore, they must be rewritten for each new architecture that the operating system is to be used on.



### Microkernels

Main article: [Microkernel](https://en.wikipedia.org/wiki/Microkernel)

Microkernel (also abbreviated μK or uK) is the term describing an approach to operating system design by which the functionality of the system is moved out of the traditional "kernel", into a set of "servers" that communicate through a "minimal" kernel, leaving as little as possible in "system space" and as much as possible in "user space". A microkernel that is designed for a specific platform or device is only ever going to have what it needs to operate. The microkernel approach consists of defining a simple abstraction over the hardware, with a set of primitives or [system calls](https://en.wikipedia.org/wiki/System_call) to implement minimal OS services such as [memory management](https://en.wikipedia.org/wiki/Memory_management), [multitasking](https://en.wikipedia.org/wiki/Computer_multitasking), and [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication). Other services, including those normally provided by the kernel, such as [networking](https://en.wikipedia.org/wiki/Computer_networking), are implemented in user-space programs, referred to as *servers*. Microkernels are easier to maintain than monolithic kernels, but the large number of system calls and [context switches](https://en.wikipedia.org/wiki/Context_switch) might slow down the system because they typically generate more overhead than plain function calls.

Only parts which really require being in a privileged mode are in kernel space: IPC (Inter-Process Communication), basic scheduler, or scheduling primitives, basic memory handling, basic I/O primitives. Many critical parts are now running in user space: The complete scheduler, memory handling, file systems, and network stacks. Micro kernels were invented as a reaction to traditional "monolithic" kernel design, whereby all system functionality was put in a one static program running in a special "system" mode of the processor. In the microkernel, only the most fundamental of tasks are performed such as being able to access some (not necessarily all) of the hardware, manage memory and coordinate message passing between the processes. Some systems that use micro kernels are QNX and the HURD. In the case of [QNX](https://en.wikipedia.org/wiki/QNX) and [Hurd](https://en.wikipedia.org/wiki/GNU_Hurd) user sessions can be entire snapshots of the system itself or views as it is referred to. The very essence of the microkernel architecture illustrates some of its advantages:

- Maintenance is generally easier.
- Patches can be tested in a separate instance, and then swapped in to take over a production instance.
- Rapid development time and new software can be tested without having to reboot the kernel.
- More persistence in general, if one instance goes hay-wire, it is often possible to substitute it with an operational mirror.

Most micro kernels use a message passing system of some sort to handle requests from one server to another. The message passing system generally operates on a port basis with the microkernel. As an example, if a request for more memory is sent, a port is opened with the microkernel and the request sent through. Once within the microkernel, the steps are similar to system calls. The rationale was that it would bring modularity in the system architecture, which would entail a cleaner system, easier to debug or dynamically modify, customizable to users' needs, and more performing. They are part of the operating systems like [GNU Hurd](https://en.wikipedia.org/wiki/GNU_Hurd), [MINIX](https://en.wikipedia.org/wiki/MINIX), [MkLinux](https://en.wikipedia.org/wiki/MkLinux), [QNX](https://en.wikipedia.org/wiki/QNX) and [Redox OS](https://en.wikipedia.org/wiki/Redox_OS). Although micro kernels are very small by themselves, in combination with all their required auxiliary code they are, in fact, often larger than monolithic kernels. Advocates of monolithic kernels also point out that the two-tiered structure of microkernel systems, in which most of the operating system does not interact directly with the hardware, creates a not-insignificant cost in terms of system efficiency. These types of kernels normally provide only the minimal services such as defining memory address spaces, Inter-process communication (IPC) and the process management. The other functions such as running the hardware processes are not handled directly by micro kernels. Proponents of micro kernels point out those monolithic kernels have the disadvantage that an error in the kernel can cause the entire system to crash. However, with a microkernel, if a kernel process crashes, it is still possible to prevent a crash of the system as a whole by merely restarting the service that caused the error.

Other services provided by the kernel such as networking are implemented in user-space programs referred to as *servers*. Servers allow the operating system to be modified by simply starting and stopping programs. For a machine without networking support, for instance, the networking server is not started. The task of moving in and out of the kernel to move data between the various applications and servers creates overhead which is detrimental to the efficiency of micro kernels in comparison with monolithic kernels.

Disadvantages in the microkernel exist however. Some are:

- Larger running [memory footprint](https://en.wikipedia.org/wiki/Memory_footprint)
- More software for interfacing is required, there is a potential for performance loss.
- Messaging bugs can be harder to fix due to the longer trip they have to take versus the one off copy in a monolithic kernel.
- Process management in general can be very complicated.

The disadvantages for micro kernels are extremely context based. As an example, they work well for small single purpose (and critical) systems because if not many processes need to run, then the complications of process management are effectively mitigated.

A microkernel allows the implementation of the remaining part of the operating system as a normal application program written in a [high-level language](https://en.wikipedia.org/wiki/High-level_language), and the use of different operating systems on top of the same unchanged kernel.[[21\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Hansen70-21) It is also possible to dynamically switch among operating systems and to have more than one active simultaneously.[[21\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Hansen70-21)



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ec/Kernel-microkernel.svg/260px-Kernel-microkernel.svg.png)





In the microkernel approach, the kernel itself only provides basic functionality that allows the execution of servers, separate programs that assume former kernel functions, such as device drivers, GUI servers, etc.





# [Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)

A **monolithic kernel** is an operating system architecture where the entire operating system is working in [kernel space](https://en.wikipedia.org/wiki/Kernel_space). The monolithic model differs from other operating system architectures (such as the [microkernel](https://en.wikipedia.org/wiki/Microkernel) architecture)[[1\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-2) in that it alone defines a high-level virtual interface over computer hardware. A set of primitives or [system calls](https://en.wikipedia.org/wiki/System_call) implement all operating system services such as [process](https://en.wikipedia.org/wiki/Process_(computing)) management, [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)), and [memory management](https://en.wikipedia.org/wiki/Memory_management). Device drivers can be added to the kernel as [modules](https://en.wikipedia.org/wiki/Module_(programming)).

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/OS-structure2.svg/800px-OS-structure2.svg.png)





Structure of monolithic kernel,microkernel and hybrid kernel-based operating systems

## Loadable modules

Modular operating systems such as [OS-9](https://en.wikipedia.org/wiki/OS-9) and most modern monolithic operating systems such as [OpenVMS](https://en.wikipedia.org/wiki/OpenVMS), [Linux](https://en.wikipedia.org/wiki/Linux_kernel), [BSD](https://en.wikipedia.org/wiki/BSD), [SunOS](https://en.wikipedia.org/wiki/SunOS), [AIX](https://en.wikipedia.org/wiki/AIX), and [MULTICS](https://en.wikipedia.org/wiki/MULTICS) can dynamically load (and unload) executable modules at runtime.

This modularity of the operating system is at the binary (image) level and not at the architecture level. **Modular monolithic operating systems** are not to be confused with the architectural level of modularity inherent in [server-client](https://en.wikipedia.org/wiki/Microkernel) operating systems (and its derivatives sometimes marketed as [hybrid kernel](https://en.wikipedia.org/wiki/Hybrid_kernel)) which use microkernels and servers (not to be mistaken for modules or daemons).

Practically speaking, dynamically loading modules is simply a more flexible way of handling the operating system image at runtime—as opposed to rebooting with a different operating system image. The modules allow easy extension of the operating systems' capabilities as required.[[3\]](https://en.wikipedia.org/wiki/Monolithic_kernel#cite_note-3) Dynamically loadable modules incur a small overhead when compared to building the module into the operating system image.

However, in some cases, loading modules dynamically (as-needed) helps to keep the amount of code running in [kernel space](https://en.wikipedia.org/wiki/Kernel_space) to a minimum; for example, to minimize operating system footprint for embedded devices or those with limited hardware resources. Namely, an unloaded module need not be stored in scarce [random access memory](https://en.wikipedia.org/wiki/Random_access_memory).

## Monolithic architecture examples

- Unix kernels
  - BSD
    - [FreeBSD](https://en.wikipedia.org/wiki/FreeBSD)
    - [NetBSD](https://en.wikipedia.org/wiki/NetBSD)
    - [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD)
    - [MirOS BSD](https://en.wikipedia.org/wiki/MirOS_BSD)
    - [SunOS](https://en.wikipedia.org/wiki/SunOS)
  - UNIX System V
    - [AIX](https://en.wikipedia.org/wiki/IBM_AIX)
    - [HP-UX](https://en.wikipedia.org/wiki/HP-UX)
    - Solaris
      - [OpenSolaris](https://en.wikipedia.org/wiki/OpenSolaris) / [illumos](https://en.wikipedia.org/wiki/Illumos)
- Unix-like kernels
  - [Linux](https://en.wikipedia.org/wiki/Linux_kernel)
- DOS
  - [DR-DOS](https://en.wikipedia.org/wiki/DR-DOS)
  - MS-DOS
    - Microsoft [Windows 9x](https://en.wikipedia.org/wiki/Windows_9x) series ([95](https://en.wikipedia.org/wiki/Windows_95), [98](https://en.wikipedia.org/wiki/Windows_98), [98 SE](https://en.wikipedia.org/wiki/Windows_98#Windows_98_Second_Edition), [ME](https://en.wikipedia.org/wiki/Windows_ME))
  - [FreeDOS](https://en.wikipedia.org/wiki/FreeDOS)
- [OpenVMS](https://en.wikipedia.org/wiki/OpenVMS)
- [XTS-400](https://en.wikipedia.org/wiki/XTS-400)
- [z/TPF](https://en.wikipedia.org/wiki/Z/TPF)

## See also

- [Exokernel](https://en.wikipedia.org/wiki/Exokernel)
- [Hybrid kernel](https://en.wikipedia.org/wiki/Hybrid_kernel)
- [Kernel (computer science)](https://en.wikipedia.org/wiki/Kernel_(computer_science))
- [Microkernel](https://en.wikipedia.org/wiki/Microkernel)
- [Nanokernel](https://en.wikipedia.org/wiki/Nanokernel)
- [Tanenbaum–Torvalds debate](https://en.wikipedia.org/wiki/Tanenbaum–Torvalds_debate)