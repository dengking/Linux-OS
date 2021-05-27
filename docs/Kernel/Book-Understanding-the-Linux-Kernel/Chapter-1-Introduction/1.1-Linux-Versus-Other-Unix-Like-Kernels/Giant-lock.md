

# wikipedia [Giant lock](https://en.wikipedia.org/wiki/Giant_lock)


In [operating systems](https://en.wikipedia.org/wiki/Operating_systems), a **giant lock**, also known as a **big-lock** or **kernel-lock**, is a [lock](https://en.wikipedia.org/wiki/Lock_(computer_science)) that may be used in the [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) to provide [concurrency control](https://en.wikipedia.org/wiki/Concurrency_control) required by [symmetric multiprocessing](https://en.wikipedia.org/wiki/Symmetric_multiprocessing) (SMP) systems.

A giant lock is a solitary global lock that is held whenever a [thread](https://en.wikipedia.org/wiki/Thread_(computer_science)) enters [kernel space](https://en.wikipedia.org/wiki/Kernel_space) and released when the thread returns to [user space](https://en.wikipedia.org/wiki/User_space); a [system call](https://en.wikipedia.org/wiki/System_call) is the archetypal example. In this model, threads in [user space](https://en.wikipedia.org/wiki/User_space) can run concurrently on any available [processors](https://en.wikipedia.org/wiki/Microprocessor) or [processor cores](https://en.wikipedia.org/wiki/Multi-core), but no more than one thread can run in kernel space; any other threads that try to enter kernel space are forced to wait. In other words, the giant lock eliminates all [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)) in kernel space.

By isolating the kernel from concurrency, many parts of the kernel no longer need to be modified to support SMP. However, as in giant-lock SMP systems only one processor can run the kernel code at a time, performance for applications spending significant amounts of time in the kernel is not much improved. Accordingly, the giant-lock approach is commonly seen as a preliminary means of bringing SMP support to an operating system, yielding benefits only in user space. Most modern operating systems use a [fine-grained locking](https://en.wikipedia.org/wiki/Fine-grained_locking) approach.



## Linux

The [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel) had a big kernel lock (BKL) since the introduction of SMP, until [Arnd Bergmann](https://en.wikipedia.org/w/index.php?title=Arnd_Bergmann&action=edit&redlink=1) removed it in 2011 in kernel version 2.6.39, with the remaining uses of the big lock removed or replaced by finer-grained locking. [Linux distributions](https://en.wikipedia.org/wiki/Linux_distribution) at or above [CentOS 7](https://en.wikipedia.org/wiki/CentOS), [Debian 7 (Wheezy)](https://en.wikipedia.org/wiki/Debian_version_history) and [Ubuntu 11.10](https://en.wikipedia.org/wiki/Ubuntu_version_history) are therefore not using BKL.





