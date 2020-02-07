# Kernel (operating system)概述

本章开始套利OS的kernel，本节是对Kernel的概述，参考的是维基百科[Kernel (operating system)](https://en.wikipedia.org/wiki/Kernel_(operating_system))。

The **kernel** is a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is the core of a computer's [operating system](https://en.wikipedia.org/wiki/Operating_system), with complete control over everything in the system. On most systems, it is one of the first programs loaded on [start-up](https://en.wikipedia.org/wiki/Booting) (after the [bootloader](https://en.wikipedia.org/wiki/Bootloader)). It handles the rest of start-up as well as [input/output](https://en.wikipedia.org/wiki/Input/output) requests from [software](https://en.wikipedia.org/wiki/Software), translating them into [data-processing](https://en.wikipedia.org/wiki/Data_processing) instructions for the [central processing unit](https://en.wikipedia.org/wiki/Central_processing_unit). It handles memory and [peripherals](https://en.wikipedia.org/wiki/Peripheral) (外设) like keyboards, monitors, printers, and speakers.

The critical code of the kernel is usually loaded into a **separate area** of memory, which is protected from access by [application programs](https://en.wikipedia.org/wiki/Application_software) or other, less critical parts of the operating system. The kernel performs its tasks, such as running processes, managing hardware devices such as the [hard disk](https://en.wikipedia.org/wiki/Hard_disk), and handling interrupts, in this protected [kernel space](https://en.wikipedia.org/wiki/Kernel_space). In contrast, everything a user does is in [user space](https://en.wikipedia.org/wiki/User_space): writing text in a text editor, running programs in a [GUI](https://en.wikipedia.org/wiki/Graphical_user_interface), etc. This **separation** prevents **user data** and **kernel data** from interfering with each other and causing instability and slowness, as well as preventing malfunctioning **application programs** from crashing the entire operating system.

> NOTE:隔离带来安全

The kernel's [interface](https://en.wikipedia.org/wiki/Application_programming_interface) is a [low-level](https://en.wikipedia.org/wiki/High-_and_low-level) [abstraction layer](https://en.wikipedia.org/wiki/Abstraction_layer). When a [process](https://en.wikipedia.org/wiki/Process_(computing)) makes requests of the kernel, it is called a [system call](https://en.wikipedia.org/wiki/System_call). Kernel designs differ in how they manage these system calls and [resources](https://en.wikipedia.org/wiki/Resource_(computer_science)). A [monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel) runs all the operating system [instructions](https://en.wikipedia.org/wiki/Instruction_set) in the same [address space](https://en.wikipedia.org/wiki/Address_space) for speed. A [microkernel](https://en.wikipedia.org/wiki/Microkernel) runs most processes in user space, for [modularity](https://en.wikipedia.org/wiki/Modular_programming). 



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8f/Kernel_Layout.svg/220px-Kernel_Layout.svg.png)

> A kernel connects the **application software** to the **hardware** of a computer.

## Function of Kernel

关于内核的功能，在本篇文章中没有进行详细的分类介绍，所以此处进行省略；在[Operating system](https://en.wikipedia.org/wiki/Operating_system)的[Kernel](https://en.wikipedia.org/wiki/Operating_system#Kernel)章节进行了非常好的介绍，推荐去阅读。



## [Kernel design decisions](https://en.wikipedia.org/wiki/Kernel_(operating_system)#Kernel_design_decisions)

> 原文本节所描述的是在设计一个kernel的时候需要考虑哪些问题，读者应该对这些问题有些了解，这些问题直接影响了kernel的实现。

## [Kernel-wide design approaches](https://en.wikipedia.org/wiki/Kernel_(operating_system)#Kernel-wide_design_approaches)

> 原文本节所描述的是实现kernel（本质上kernel是一个software）时，采取怎样的软件架构。目前主流的的架构有两种。原文中还对这两种软件架构背后的philosophy即 [*separation of mechanism and policy*](https://en.wikipedia.org/wiki/Separation_of_mechanism_and_policy)  进行了分析，我读完仍然一头雾水。

While [monolithic kernels](https://en.wikipedia.org/wiki/Monolithic_kernel) execute all of their code in the same address space ([kernel space](https://en.wikipedia.org/wiki/Kernel_space)), [microkernels](https://en.wikipedia.org/wiki/Microkernel) try to run most of their services in user space, aiming to improve maintainability and modularity of the codebase. Most kernels do not fit exactly into one of these categories, but are rather found in between these two designs. These are called [hybrid kernels](https://en.wikipedia.org/wiki/Hybrid_kernel). More exotic designs such as [nanokernels](https://en.wikipedia.org/wiki/Nanokernel) and [exokernels](https://en.wikipedia.org/wiki/Exokernel) are available, but are seldom used for production systems. The [Xen](https://en.wikipedia.org/wiki/Xen)hypervisor, for example, is an exokernel.



### Monolithic kernels

Main article: [Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/Kernel-simple.svg/170px-Kernel-simple.svg.png)



> Diagram of a monolithic kernel

In a monolithic kernel, all OS services run along with the main kernel thread, thus also residing in the same memory area. This approach provides rich and powerful hardware access. Some developers, such as [UNIX](https://en.wikipedia.org/wiki/Unix)developer [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson), maintain that it is "easier to implement a monolithic kernel" than microkernels. The main disadvantages of monolithic kernels are the dependencies between system components – a bug in a device driver might crash the entire system – and the fact that large kernels can become very difficult to maintain.



### Microkernels

Main article: [Microkernel](https://en.wikipedia.org/wiki/Microkernel)

Microkernel (also abbreviated μK or uK) is the term describing an approach to operating system design by which the functionality of the system is moved out of the traditional "kernel", into a set of "servers" that communicate through a "minimal" kernel, leaving as little as possible in "system space" and as much as possible in "user space". A microkernel that is designed for a specific platform or device is only ever going to have what it needs to operate. The microkernel approach consists of defining a simple abstraction over the hardware, with a set of primitives or [system calls](https://en.wikipedia.org/wiki/System_call) to implement minimal OS services such as [memory management](https://en.wikipedia.org/wiki/Memory_management), [multitasking](https://en.wikipedia.org/wiki/Computer_multitasking), and [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication). Other services, including those normally provided by the kernel, such as [networking](https://en.wikipedia.org/wiki/Computer_networking), are implemented in user-space programs, referred to as *servers*. Microkernels are easier to maintain than monolithic kernels, but the large number of system calls and [context switches](https://en.wikipedia.org/wiki/Context_switch) might slow down the system because they typically generate more overhead than plain function calls.


