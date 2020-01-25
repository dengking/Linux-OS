# [Kernel (operating system)](https://en.wikipedia.org/wiki/Kernel_(operating_system))



The **kernel** is a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is the core of a computer's [operating system](https://en.wikipedia.org/wiki/Operating_system), with complete control over everything in the system.[[1\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Linfo-1) On most systems, it is one of the first programs loaded on [start-up](https://en.wikipedia.org/wiki/Booting) (after the [bootloader](https://en.wikipedia.org/wiki/Bootloader)). It handles the rest of start-up as well as [input/output](https://en.wikipedia.org/wiki/Input/output) requests from [software](https://en.wikipedia.org/wiki/Software), translating them into [data-processing](https://en.wikipedia.org/wiki/Data_processing) instructions for the [central processing unit](https://en.wikipedia.org/wiki/Central_processing_unit). It handles memory and [peripherals](https://en.wikipedia.org/wiki/Peripheral) (外设) like keyboards, monitors, printers, and speakers.



The critical code of the kernel is usually loaded into a **separate area** of memory, which is protected from access by [application programs](https://en.wikipedia.org/wiki/Application_software) or other, less critical parts of the operating system. The kernel performs its tasks, such as running processes, managing hardware devices such as the [hard disk](https://en.wikipedia.org/wiki/Hard_disk), and handling interrupts, in this protected [kernel space](https://en.wikipedia.org/wiki/Kernel_space). In contrast, everything a user does is in [user space](https://en.wikipedia.org/wiki/User_space): writing text in a text editor, running programs in a [GUI](https://en.wikipedia.org/wiki/Graphical_user_interface), etc. This **separation** prevents **user data** and **kernel data** from interfering with each other and causing instability and slowness,[[1\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Linfo-1) as well as preventing malfunctioning **application programs** from crashing the entire operating system.

***SUMMARY***:隔离原则

The kernel's [interface](https://en.wikipedia.org/wiki/Application_programming_interface) is a [low-level](https://en.wikipedia.org/wiki/High-_and_low-level) [abstraction layer](https://en.wikipedia.org/wiki/Abstraction_layer). When a [process](https://en.wikipedia.org/wiki/Process_(computing)) makes requests of the kernel, it is called a [system call](https://en.wikipedia.org/wiki/System_call). Kernel designs differ in how they manage these system calls and [resources](https://en.wikipedia.org/wiki/Resource_(computer_science)). A [monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel) runs all the operating system [instructions](https://en.wikipedia.org/wiki/Instruction_set) in the same [address space](https://en.wikipedia.org/wiki/Address_space) for speed. A [microkernel](https://en.wikipedia.org/wiki/Microkernel) runs most processes in user space,[[2\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-2) for [modularity](https://en.wikipedia.org/wiki/Modular_programming).[[3\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-mono-micro-3)



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8f/Kernel_Layout.svg/220px-Kernel_Layout.svg.png)

A kernel connects the **application software** to the **hardware** of a computer.





## Functions

The kernel's primary function is to **mediate** access to the computer's resources, including:[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4)

- The central processing unit (CPU)

  This central component of a computer system is responsible for *running* or *executing* programs. The kernel takes responsibility for deciding at any time which of the many running programs should be allocated to the processor or processors.

  ***SUMMARY*** : 上面这段话所描述的其实是schedule

- Random-access memory (RAM)

  [Random-access memory](https://en.wikipedia.org/wiki/Random-access_memory) is used to store both program instructions and data. Typically, both need to be present in memory in order for a program to execute. Often multiple programs will want access to memory, frequently demanding more memory than the computer has available. The kernel is responsible for deciding which memory each process can use, and determining what to do when not enough memory is available.

- Input/output (I/O) devices

  I/O devices include such peripherals as keyboards, mice, disk drives, printers, USB devices, **network adapters**, and [display devices](https://en.wikipedia.org/wiki/Display_device). The kernel allocates requests from applications to perform I/O to an appropriate device and provides convenient methods for using the device (typically abstracted to the point where the application does not need to know implementation details of the device).
  
  ***SUMMARY*** : 需要搞清楚有哪些IO device



### Resource Management

Key aspects necessary in resource management are the definition of an execution domain ([address space](https://en.wikipedia.org/wiki/Address_space)) and the protection mechanism used to mediate access to the resources within a domain.[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4) Kernels also provide methods for [synchronization](https://en.wikipedia.org/wiki/Synchronization_(computer_science))and [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication) (IPC). These implementations may be within the Kernel itself or the kernel can also rely on other processes it is running. Although the kernel must provide **inter-process communication** in order to provide access to the facilities provided by each other, kernels must also provide running programs with a method to make requests to access these facilities.



### Memory management

*Further information:* [Memory management (operating systems)](https://en.wikipedia.org/wiki/Memory_management_(operating_systems))

The kernel has full access to the system's memory and must allow processes to safely access this memory as they require it. Often the first step in doing this is [virtual addressing](https://en.wikipedia.org/wiki/Virtual_addressing), usually achieved by [paging](https://en.wikipedia.org/wiki/Paging) and/or [segmentation](https://en.wikipedia.org/wiki/Segmentation_(memory)). Virtual addressing allows the kernel to make a given physical address appear to be another address, the virtual address. Virtual address spaces may be different for different processes; the memory that one process accesses at a particular (virtual) address may be different memory from what another process accesses at the same address. This allows every program to behave as if it is the only one (apart from the kernel) running and thus prevents applications from crashing each other.[[5\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-OS-Concepts-5)

On many systems, a program's virtual address may refer to data which is not currently in memory. The layer of indirection provided by virtual addressing allows the operating system to use other data stores, like a [hard drive](https://en.wikipedia.org/wiki/Hard_drive), to store what would otherwise have to remain in main memory ([RAM](https://en.wikipedia.org/wiki/Random-access_memory)). As a result, operating systems can allow programs to use more memory than the system has physically available. When a program needs data which is not currently in RAM, the **CPU** signals to the **kernel** that this has happened, and the kernel responds by writing the contents of an inactive memory block to disk (if necessary) and replacing it with the data requested by the program. The program can then be resumed from the point where it was stopped. This scheme is generally known as [demand paging](https://en.wikipedia.org/wiki/Demand_paging).

Virtual addressing also allows creation of virtual partitions of memory in two disjointed areas, one being reserved for the kernel ([kernel space](https://en.wikipedia.org/wiki/Kernel_space)) and the other for the applications ([user space](https://en.wikipedia.org/wiki/User_space)). The applications are not permitted by the processor to address kernel memory, thus preventing an application from damaging the running kernel. This fundamental partition of memory space has contributed much to the current designs of actual general-purpose kernels and is almost universal in such systems, although some research kernels (e.g. [Singularity](https://en.wikipedia.org/wiki/Singularity_(operating_system))) take other approaches.

***SUMMARY*** : 参见[Virtual address space](https://en.wikipedia.org/wiki/Virtual_address_space)，其中提及:

> On [Microsoft Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) 32-bit, by default, only 2 GiB are made available to processes for their own use.[[2\]](https://en.wikipedia.org/wiki/Virtual_address_space#cite_note-2) The other 2 GiB are used by the operating system.
>
> For [x86](https://en.wikipedia.org/wiki/X86) CPUs, [Linux](https://en.wikipedia.org/wiki/Linux) 32-bit allows splitting the user and kernel address ranges in different ways: *3G/1G user/kernel* (default), *1G/3G user/kernel* or *2G/2G user/kernel*.[[9\]](https://en.wikipedia.org/wiki/Virtual_address_space#cite_note-9)



### Device management

To perform useful functions, processes need access to the [peripherals](https://en.wikipedia.org/wiki/Peripheral) connected to the computer, which are controlled by the kernel through [device drivers](https://en.wikipedia.org/wiki/Device_driver). A **device driver** is a computer program that enables the operating system to interact with a **hardware device**. It provides the operating system with information of how to control and communicate with a certain piece of hardware. The driver is an important and vital piece to a program application. The design goal of a driver is abstraction; the function of the driver is to translate the OS-mandated abstract function calls (programming calls) into device-specific calls. In theory, the device should work correctly with the suitable driver. **Device drivers** are used for such things as video cards, sound cards, printers, scanners, modems, and LAN cards. The common levels of abstraction of device drivers are:

\1. On the hardware side:

- Interfacing directly.
- Using a high level interface (Video [BIOS](https://en.wikipedia.org/wiki/BIOS)).
- Using a lower-level device driver (file drivers using disk drivers).
- Simulating work with hardware, while doing something entirely different.

\2. On the software side:

- Allowing the operating system direct access to hardware resources.
- Implementing only primitives.
- Implementing an interface for non-driver software (Example: [TWAIN](https://en.wikipedia.org/wiki/TWAIN)).
- Implementing a language, sometimes high-level (Example [PostScript](https://en.wikipedia.org/wiki/PostScript)).



For example, to show the user something on the screen, an application would make a request to the kernel, which would forward the request to its display driver, which is then responsible for actually plotting the character/pixel.[[5\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-OS-Concepts-5)



A kernel must maintain a list of available devices. This list may be known in advance (e.g. on an embedded system where the kernel will be rewritten if the available hardware changes), configured by the user (typical on older PCs and on systems that are not designed for personal use) or detected by the operating system at run time (normally called [plug and play](https://en.wikipedia.org/wiki/Plug_and_play)). In a plug and play system, a device manager first performs a scan on different [hardware buses](https://en.wikipedia.org/wiki/Hardware_bus), such as [Peripheral Component Interconnect](https://en.wikipedia.org/wiki/Peripheral_Component_Interconnect) (PCI) or [Universal Serial Bus](https://en.wikipedia.org/wiki/Universal_Serial_Bus) (USB), to detect installed devices, then searches for the appropriate drivers.



As device management is a very [OS](https://en.wikipedia.org/wiki/Operating_system)-specific topic, these drivers are handled differently by each kind of kernel design, but in every case, the kernel has to provide the [I/O](https://en.wikipedia.org/wiki/Input/Output) to allow **drivers** to physically access their **devices** through some [port](https://en.wikipedia.org/wiki/Port_(computer_networking)) or **memory location**. Very important decisions have to be made when designing the device management system, as in some designs accesses may involve [context switches](https://en.wikipedia.org/wiki/Context_switch), making the operation very CPU-intensive and easily causing a significant performance overhead.[*citation needed*]



### System calls

*Main article:* [System call](https://en.wikipedia.org/wiki/System_call)

In computing, a system call is how a process requests a service from an operating system's kernel that it does not normally have permission to run. **System calls** provide the interface between a process and the operating system. Most operations interacting with the system require permissions not available to a user level process, e.g. I/O performed with a device present on the system, or any form of communication with other processes requires the use of **system calls**.

A system call is a mechanism that is used by the application program to request a service from the operating system. They use a **machine-code instruction** that causes the processor to change **mode**. An example would be from **supervisor mode** to **protected mode**. This is where the operating system performs actions like accessing hardware devices or the memory management unit. Generally the operating system provides a **library** that sits between the operating system and normal programs. Usually it is a C library such as **Glibc** or Windows API. The library handles the low-level details of passing information to the **kernel** and switching to **supervisor mode**. System calls include `close`, `open`, `read`, `wait` and `write`.

To actually perform useful work, a process must be able to access the services provided by the kernel. This is implemented differently by each kernel, but most provide a [C library](https://en.wikipedia.org/wiki/C_library) or an [API](https://en.wikipedia.org/wiki/Application_programming_interface), which in turn invokes the related kernel functions.[[6\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-6)

The method of invoking the kernel function varies from kernel to kernel. If memory isolation is in use, it is impossible for a user process to call the kernel directly, because that would be a violation of the processor's access control rules. A few possibilities are:

- Using a software-simulated [interrupt](https://en.wikipedia.org/wiki/Interrupt). This method is available on most hardware, and is therefore very common.
- Using a [call gate](https://en.wikipedia.org/wiki/Call_gate). A call gate is a special address stored by the kernel in a list in kernel memory at a location known to the processor. When the processor detects a call to that address, it instead redirects to the target location without causing an access violation. This requires hardware support, but the hardware for it is quite common.
- Using a special [system call](https://en.wikipedia.org/wiki/System_call) instruction. This technique requires special hardware support, which common architectures (notably, [x86](https://en.wikipedia.org/wiki/X86)) may lack. System call instructions have been added to recent models of x86 processors, however, and some operating systems for PCs make use of them when available.
- Using a memory-based queue. An application that makes large numbers of requests but does not need to wait for the result of each may add details of requests to an area of memory that the kernel periodically scans to find requests.

## Kernel design decisions

TO READ



## Kernel-wide design approaches

Naturally, the above listed tasks and features can be provided in many ways that differ from each other in design and implementation.

The principle of [*separation of mechanism and policy*](https://en.wikipedia.org/wiki/Separation_of_mechanism_and_policy) （机制和政策的分离） is the substantial difference between the philosophy of **micro** and **monolithic** kernels.[[24\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-24)[[25\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Levin75-25) Here a *mechanism* is the support that allows the implementation of many different policies, while a policy is a particular "mode of operation". For instance, a mechanism may provide for user log-in attempts to call an authorization server to determine whether access should be granted; a policy may be for the authorization server to request a password and check it against an encrypted password stored in a database. Because the mechanism is generic, the policy could more easily be changed (e.g. by requiring the use of a [security token](https://en.wikipedia.org/wiki/Security_token)) than if the mechanism and policy were integrated in the same module.

In minimal microkernel just some very basic policies are included,[[25\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Levin75-25) and its mechanisms allows what is running on top of the kernel (the remaining part of the operating system and the other applications) to decide which policies to adopt (as memory management, high level process scheduling, file system management, etc.).[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4)[[21\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Hansen70-21) A monolithic kernel instead tends to include many policies, therefore restricting the rest of the system to rely on them.

[Per Brinch Hansen](https://en.wikipedia.org/wiki/Per_Brinch_Hansen) presented arguments in favour of **separation of mechanism and policy**.[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4)[[21\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Hansen70-21) The failure to properly fulfill this separation is one of the major causes of the lack of substantial innovation in existing operating systems,[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4) a problem common in computer architecture.[[26\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Denning80-26)[[27\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Nehmer91-27)[[28\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-28) The monolithic design is induced by the "kernel mode"/"user mode" architectural approach to protection (technically called [hierarchical protection domains](https://en.wikipedia.org/wiki/Hierarchical_protection_domains)), which is common in conventional commercial systems;[[29\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Levy84privilegedmode-29) in fact, every module needing protection is therefore preferably included into the kernel.[[29\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Levy84privilegedmode-29) This link between monolithic design and "privileged mode" can be reconducted to the key issue of mechanism-policy separation;[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4) in fact the "privileged mode" architectural approach melds together the protection mechanism with the security policies, while the major alternative architectural approach, [capability-based addressing](https://en.wikipedia.org/wiki/Capability-based_addressing), clearly distinguishes between the two, leading naturally to a microkernel design[[4\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-Wulf74-4) (see [Separation of protection and security](https://en.wikipedia.org/wiki/Separation_of_protection_and_security)).

While [monolithic kernels](https://en.wikipedia.org/wiki/Monolithic_kernel) execute all of their code in the same address space ([kernel space](https://en.wikipedia.org/wiki/Kernel_space)), [microkernels](https://en.wikipedia.org/wiki/Microkernel) try to run most of their services in user space, aiming to improve maintainability and modularity of the codebase.[[3\]](https://en.wikipedia.org/wiki/Kernel_(operating_system)#cite_note-mono-micro-3) Most kernels do not fit exactly into one of these categories, but are rather found in between these two designs. These are called [hybrid kernels](https://en.wikipedia.org/wiki/Hybrid_kernel). More exotic designs such as [nanokernels](https://en.wikipedia.org/wiki/Nanokernel) and [exokernels](https://en.wikipedia.org/wiki/Exokernel) are available, but are seldom used for production systems. The [Xen](https://en.wikipedia.org/wiki/Xen)hypervisor, for example, is an exokernel.



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



**TO READE**



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

TO READ