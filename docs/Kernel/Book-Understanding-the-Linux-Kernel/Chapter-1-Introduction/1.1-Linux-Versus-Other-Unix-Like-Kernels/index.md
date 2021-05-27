# 1.1. Linux Versus Other Unix-Like Kernels

> NOTE: 
>
> 介绍Linux kernel的特性

The various Unix-like systems on the market, some of which have a long history and show signs of archaic（古老的，陈旧的） practices, differ in many important respects. All commercial variants were derived from either SVR4 or 4.4BSD, and all tend to agree on some common standards like IEEE's Portable
Operating Systems based on Unix (POSIX) and X/Open's Common Applications Environment (CAE).

The current standards specify only an **application programming interface** (API)that is, a **well-defined** environment in which user programs should run. Therefore, the standards do not impose any
restriction on internal(内部的) design choices of a compliant **kernel**. `[*]`

> `[*]` As a matter of fact, several non-Unix operating systems, such as Windows NT and its descendents, are POSIX-compliant.

> NOTE: 关于Unix-like system的standard，演进历程，参见《`Unix-standardization-and-implementation.md`》

To define a common user interface, Unix-like kernels often share **fundamental design ideas and features**. In this respect, Linux is comparable with the other Unix-like operating systems. Reading this book and studying the Linux kernel, therefore, may help you understand the other Unix variants, too.

> NOTE: 
>
> "Unix-philosophy哲学"

The 2.6 version of the **Linux kernel** aims to be compliant with the IEEE POSIX standard. This, of course, means that most existing Unix programs can be compiled and executed on a Linux system with very little effort or even without the need for patches to the source code. Moreover, Linux includes all the features of a modern Unix operating system, such as **virtual memory**, a **virtual** **filesystem**, **lightweight processes**, **Unix signals** , **SVR4 interprocess communications**, support for **Symmetric Multiprocessor (SMP) systems**, and so on.

When Linus Torvalds wrote the first kernel, he referred to some classical books on Unix internals, like Maurice Bach's The Design of the Unix Operating System (Prentice Hall, 1986). Actually, Linux still has some bias toward the Unix baseline described in Bach's book (i.e., SVR2). However, Linux doesn't stick to any particular variant. Instead, it tries to adopt the best features and design choices of several different Unix kernels.

The following list describes how Linux competes against some well-known commercial Unix kernels:

## *Monolithic kernel*

It is a large, complex do-it-yourself program, composed of several logically different components. In this, it is quite conventional; most commercial Unix variants are monolithic. (Notable exceptions are the Apple Mac OS X and the GNU Hurd operating systems, both derived from the Carnegie-Mellon's Mach, which follow a microkernel approach.)

> NOTE: See also
>
> - wikipedia [Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)

## *Compiled and statically linked traditional Unix kernels*

Most modern kernels can dynamically load and unload some portions of the kernel code (typically, **device drivers**), which are usually called ***modules*** . Linux's support for **modules** is very good, because it is able to automatically load and unload modules on demand. Among the main commercial Unix variants, only the SVR4.2 and Solaris kernels have a similar feature.

> NOTE: 
>
> 本书中，讨论module的章节：
>
> - 1.4.4. Kernel Architecture
>
> 本书中，讨论device driver的章节：
>
> - 1.6.9. Device Drivers
>
> See also
>
> - wikipedia [Loadable kernel module](https://en.wikipedia.org/wiki/Loadable_kernel_module)

## *Kernel threading*

Some Unix kernels, such as Solaris and SVR4.2/MP, are organized as a set of kernel threads .A **kernel thread** is an execution context that can be independently scheduled; it may be associated with a user program, or it may run only some kernel functions. Context switches between **kernel threads** are usually much less expensive than context switches between ordinary processes, because the former usually operate on a common address space. Linux uses **kernel threads** in a very limited way to execute a few **kernel functions** periodically; however, they do not represent the basic **execution context** abstraction. (That's the topic of the next item.)

> NOTE: 本书讨论kernel thread的章节：
>
> - 3.4.2. Kernel Threads

## *Multithreaded application support*

Most modern operating systems have some kind of support for multithreaded applications that is, user programs that are designed in terms of many relatively independent execution flows that share a large portion of the application data structures. A multithreaded user application could be composed of many **lightweight processes** (LWP), which are processes that can operate on a common address space, common physical memory pages, common opened files, and so on. Linux defines its own version of lightweight processes, which is different from the types used on other systems such as SVR4 and Solaris. While all the commercial Unix variants of **LWP** are based on **kernel threads**, Linux regards **lightweight processes** as the basic **execution context** and handles them via the nonstandard  [`clone( )`](http://man7.org/linux/man-pages/man2/clone.2.html) system call.

> NOTE: See also
>
> - [Light-weight process](https://en.wikipedia.org/wiki/Light-weight_process)
>
> 阅读以下 [`clone( )`](http://man7.org/linux/man-pages/man2/clone.2.html) system call的文档有助于理解上面这段的含义。

> NOTE: LWP VS kernel thread?
>
> 上一段中所描述的：Linux **kernel threads** do not represent the basic **execution context** abstraction.
>
> 本段中所描述的：Linux regards **lightweight processes** as the basic **execution context** and handles them via the nonstandard  `clone( )` system call.
>
> 显然，kernel thread不是linux的lightweight process。
>
> 显然linux的lightweight process是需要由linux的scheduler来进行调度的，那kernel thread是由谁来进行调度呢？下面是一些有价值的内容：
>
> - [Are kernel threads processes and daemons?](https://unix.stackexchange.com/questions/266434/are-kernel-threads-processes-and-daemons)
> - [Difference between user-level and kernel-supported threads?](https://stackoverflow.com/questions/15983872/difference-between-user-level-and-kernel-supported-threads)
> - [Kernel threads made easy](https://lwn.net/Articles/65178/)



## *Preemptive kernel*

When compiled with the "Preemptible Kernel" option, Linux 2.6 can arbitrarily interleave execution flows while they are in **privileged mode**. Besides Linux 2.6, a few other conventional, general-purpose Unix systems, such as Solaris and Mach 3.0 , are fully **preemptive kernels**. SVR4.2/MP introduces some fixed preemption points as a method to get limited preemption capability.

> NOTE: See also
>
> - wikipedia [Preemption (computing)](https://en.wikipedia.org/wiki/Preemption_(computing))
> - wikipedia [Kernel preemption](https://en.wikipedia.org/wiki/Kernel_preemption)



## *Multiprocessor support*

Several Unix kernel variants take advantage of multiprocessor systems. Linux 2.6 supports symmetric multiprocessing (SMP ) for different memory models, including NUMA: the system can use multiple processors and each processor can handle any task there is no discrimination among them. Although a few parts of the kernel code are still serialized by means of a single "**big kernel lock** ," it is fair to say that Linux 2.6 makes a near optimal use of SMP.

> NOTE: 
>
> `Giant-lock`

## *Filesystem*

Linux's standard filesystems come in many flavors. You can use the plain old Ext2 filesystem if you don't have specific needs. You might switch to Ext3 if you want to avoid lengthy filesystem checks after a system crash. If you'll have to deal with many small files, the ReiserFS filesystem is likely to be the best choice. Besides Ext3 and ReiserFS, several other journaling filesystems can be used in Linux; they include IBM AIX's Journaling File System (JFS ) and Silicon Graphics IRIX 's XFS filesystem. Thanks to a powerful **object-oriented Virtual File System technology** (inspired by Solaris and SVR4), porting a foreign filesystem to Linux is generally easier than porting to other kernels.

## *STREAMS*

Linux has no analog to the STREAMS I/O subsystem introduced in SVR4, although it is included now in most Unix kernels and has become the preferred interface for writing device drivers, terminal drivers, and network protocols.