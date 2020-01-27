[TOC]



# [Giant lock](https://en.wikipedia.org/wiki/Giant_lock)




In [operating systems](https://en.wikipedia.org/wiki/Operating_systems), a **giant lock**, also known as a **big-lock** or **kernel-lock**, is a [lock](https://en.wikipedia.org/wiki/Lock_(computer_science)) that may be used in the [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) to provide [concurrency control](https://en.wikipedia.org/wiki/Concurrency_control)required by [symmetric multiprocessing](https://en.wikipedia.org/wiki/Symmetric_multiprocessing) (SMP) systems.



A giant lock is a solitary global lock that is held whenever a [thread](https://en.wikipedia.org/wiki/Thread_(computer_science)) enters [kernel space](https://en.wikipedia.org/wiki/Kernel_space) and released when the thread returns to [user space](https://en.wikipedia.org/wiki/User_space); a [system call](https://en.wikipedia.org/wiki/System_call) is the archetypal example. In this model, threads in [user space](https://en.wikipedia.org/wiki/User_space) can run concurrently on any available [processors](https://en.wikipedia.org/wiki/Microprocessor) or [processor cores](https://en.wikipedia.org/wiki/Multi-core), but no more than one thread can run in kernel space; any other threads that try to enter kernel space are forced to wait. In other words, the giant lock eliminates all [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)) in kernel space.



By isolating the kernel from concurrency, many parts of the kernel no longer need to be modified to support SMP. However, as in giant-lock SMP systems only one processor can run the kernel code at a time, performance for applications spending significant amounts of time in the kernel is not much improved.[[1\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-rwatson2007-1) Accordingly, the giant-lock approach is commonly seen as a preliminary means of bringing SMP support to an operating system, yielding benefits only in user space. Most modern operating systems use a [fine-grained locking](https://en.wikipedia.org/wiki/Fine-grained_locking) approach.



## Linux

The [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel) had a big kernel lock (BKL) since the introduction of SMP, until [Arnd Bergmann](https://en.wikipedia.org/w/index.php?title=Arnd_Bergmann&action=edit&redlink=1) removed it in 2011 in kernel version 2.6.39,[[2\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-2)[[3\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-3) with the remaining uses of the big lock removed or replaced by finer-grained locking. [Linux distributions](https://en.wikipedia.org/wiki/Linux_distribution) at or above [CentOS 7](https://en.wikipedia.org/wiki/CentOS), [Debian 7 (Wheezy)](https://en.wikipedia.org/wiki/Debian_version_history) and [Ubuntu 11.10](https://en.wikipedia.org/wiki/Ubuntu_version_history) are therefore not using BKL.



## BSD

As of July 2019, [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD) and [NetBSD](https://en.wikipedia.org/wiki/NetBSD) are still using the [spl (Unix)](https://en.wikipedia.org/wiki/Spl_(Unix)) family of primitives to facilitate synchronisation of critical sections within the kernel,[[4\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-o/net/if-4)[[5\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-n/net/if-5)[[6\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-spl.9-6) meaning that many system calls may inhibit SMP capabilities of the system, and, according to [Matthew Dillon](https://en.wikipedia.org/wiki/Matthew_Dillon), the SMP capabilities of these two systems cannot be considered modern.[[7\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-dillon2019-7)



FreeBSD still has support for *the Giant mutex*,[[8\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-f/locking.9-8) which provides semantics akin to the old spl interface, but performance-critical core components have long as been converted to use finer-grained locking.[[1\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-rwatson2007-1)



It is claimed by [Matthew Dillon](https://en.wikipedia.org/wiki/Matthew_Dillon) that out of the [open-source software](https://en.wikipedia.org/wiki/Open-source_software) general-purpose operating systems, only [GNU/Linux](https://en.wikipedia.org/wiki/GNU/Linux), [DragonFly BSD](https://en.wikipedia.org/wiki/DragonFly_BSD) and [FreeBSD](https://en.wikipedia.org/wiki/FreeBSD) have modern SMP support, with [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD) and [NetBSD](https://en.wikipedia.org/wiki/NetBSD) falling behind.[[7\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-dillon2019-7)



The [NetBSD](https://en.wikipedia.org/wiki/NetBSD) Foundation views modern SMP support as vital to the direction of The NetBSD Project, and has offered grants to developers willing to work on SMP improvements; [NPF (firewall)](https://en.wikipedia.org/wiki/NPF_(firewall)) was one of the projects that arose as a result of these financial incentives, but further improvements to the core networking stack may still be necessary.[[5\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-n/net/if-5)[[9\]](https://en.wikipedia.org/wiki/Giant_lock#cite_note-tnf/smp-9)

