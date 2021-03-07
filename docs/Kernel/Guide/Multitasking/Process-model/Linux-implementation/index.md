# Linux OS implementation of process model

在本书的chapter 1.1. Linux Versus Other Unix-Like Kernels对linux OS中process model的实现思路进行了概括：

> Most modern operating systems have some kind of support for multithreaded applications that is, user programs that are designed in terms of many relatively independent execution flows that share a large portion of the application data structures. A multithreaded user application could be composed of many **lightweight processes** (LWP), which are **processes** that can operate on a common address space, common physical memory pages, common opened files, and so on. Linux defines its own version of **lightweight processes**, which is different from the types used on other systems such as SVR4 and Solaris. While all the commercial Unix variants of LWP are based on **kernel threads**, Linux regards **lightweight processes** as the basic **execution context** and handles them via the nonstandard   [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html)  system call.

Process和Thread的概念在前面的章节已经描述了，上面这段话引入了一个新的概念：**lightweight processes** (LWP)，**lightweight processes** 是一个实现层面的概念，而Process和Thread是标准定义的概念。

结合前面章节关于process model的描述和上面这段关于linux OS中process model实现概述，可以总结：

- Linux OS的kernel scheduling entity是**lightweight processes**

- linux OS通过它的**lightweight processes**来实现process model的；linux OS中，light weight process对应的是标准的thread，linux OS中，一个process由n（n>=1）个light weight process组成（显然，当n为1时，一个process只有一个lightweight process，这就是我们通常所说的single-thread process）。

  在本书chapter 3.1. Processes, Lightweight Processes, and Threads中定义了*thread group*的概念，*thread group*相当于process。

  在本书chapter 3.1. Processes, Lightweight Processes, and Threads中提出：对于面向process的system call，thread group要“act as a whole”即表示为一个整体，这些system call包括：[getpid](http://man7.org/linux/man-pages/man2/getpid.2.html)、[kill](http://man7.org/linux/man-pages/man2/kill.2.html)。



---

需要注意的是，在本书中有时候会将lightweight process简称为process，比如上面这段话中的这句：

> A multithreaded user application could be composed of many **lightweight processes** (LWP), which are **processes** that can operate on a common address space, common physical memory pages, common opened files, and so on. 

所以在本书中，process不一定指的是标准的process，有的时候指的是lightweight process；在本书中，使用**thread group**来表示标准的process。记住这一点，否则本书中的很多地方都会搞混淆。

关于lightweight process，参见：

- [Light-weight process](https://en.wikipedia.org/wiki/Light-weight_process)

---



## 更加深入的分析

上面这段话告诉了我们，lightweight process是由nonstandard   [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html)  system call创建。标准给出的创建process的api是[fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html)，POSIX标准所定义的创建thread的api是[pthread_create(3)](http://man7.org/linux/man-pages/man3/pthread_create.3.html)，下面通过linux的man来探索它们的实现细节：

在[PTHREADS(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)的Linux implementations of POSIX threads章节给出了linux中POSIX threads的实现方式的详细信息

> Over time, two threading implementations have been provided by the GNU C library on Linux:
>
> LinuxThreads
>
> ​      This is the original Pthreads implementation.  Since glibc 2.4, this implementation is no longer supported.
>
> NPTL (Native POSIX Threads Library)
>
> ​      This is the modern Pthreads implementation.  By comparison  with LinuxThreads, NPTL provides closer conformance to the requirements of the POSIX.1 specification and better performance when creating large numbers of threads.  NPTL is available since glibc 2.3.2, and requires features that are present in the Linux 2.6 kernel.
>
> Both of these are so-called 1:1 implementations, meaning that each thread maps to a kernel scheduling entity.  Both threading implementations employ the Linux [clone(2](http://man7.org/linux/man-pages/man2/clone.2.html)) system call.  In NPTL, thread synchronization primitives (mutexes, thread joining, and so on) are implemented using the Linux [futex(2)](http://man7.org/linux/man-pages/man2/futex.2.html) system call.

可以看到无论采用哪种方式，最终都是依赖 [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) 。

在[fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html)的[NOTES](http://man7.org/linux/man-pages/man2/fork.2.html#NOTES)章节描述了`fork`的实现细节：

> Since version 2.3.3, rather than invoking the kernel's fork() system call, the glibc fork() wrapper that is provided as part of the NPTL threading implementation invokes [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) with flags that provide the
> same effect as the traditional system call.  (A call to fork() is equivalent to a call to [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) specifying flags as just SIGCHLD.) The glibc wrapper invokes any **fork handlers** that have been established using [pthread_atfork(3)](http://man7.org/linux/man-pages/man3/pthread_atfork.3.html).

显然，[fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html)的实现也是依赖 [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) 。



## linux kernel如何实现process与thread

参见3.1. Processes, Lightweight Processes, and Threads

我觉得要想解释好这个问题，需要梳理一下linux的fork，clone之间的关系。在[Fork (system call)](https://en.wikipedia.org/wiki/Fork_(system_call))这篇文章中梳理地非常好。在3.4. Creating Processes中也有相关的描述。



### per-process kernel data structures

在3.4. Creating Processes中提出了这个说法，它让我想起了两件事情：

- process作为system resource分配单位，它有哪些resource呢？显然，它的所有的resource都需要使用一个 kernel data structures来进行描述。有必要总结per-process的resource以及对应的kernel data structures。与此相关的一个问题就是，这些resource哪些是child process可以继承的，哪些是无法继承的。

- 显然，多个lightweight process是可以共享per-process kernel data structure的（这是标准规定的），这种共享，我觉得实现上应该也是非常简单的，无非就是传入一个指针。



## LWP VS thread VS kernel thread?

关于本段，有疑问：LWP VS thread VS kernel thread?

上一段中所描述的：Linux **kernel threads** do not represent the basic **execution context** abstraction.

本段中所描述的：Linux regards **lightweight processes** as the basic **execution context** and handles them via the nonstandard  `clone( )` system call.

显然，kernel thread不是linux的lightweight process。

显然linux的lightweight process是需要由linux的scheduler来进行调度的，那kernel thread是由谁来进行调度呢？下面是一些有价值的内容：

- [Are kernel threads processes and daemons?](https://unix.stackexchange.com/questions/266434/are-kernel-threads-processes-and-daemons)
- [Difference between user-level and kernel-supported threads?](https://stackoverflow.com/questions/15983872/difference-between-user-level-and-kernel-supported-threads)
- [Kernel threads made easy](https://lwn.net/Articles/65178/)



## Linux OS lightweigh thread所共享的

- 标准process ID

## See also

参见章节：

1.6.2. Process Implementation
1.6.4. Process Address Space







## Linux OS process model的实现

之前我一直有一个疑问就是：一个process的所有的thread都共享该process的address space，而每个thread有一个自己的[call stack](https://en.wikipedia.org/wiki/Call_stack)，并且call stack是向下生长的，当时我就非常疑惑，这要如何实现呀？今天在阅读[Call stack](https://en.wikipedia.org/wiki/Call_stack)、[Stack register](https://en.wikipedia.org/wiki/Stack_register)的时候，我有了如下的认知：

- 函数调用所使用的是JMP指令
- x86有segment register，这样就可以指定call stack
- 其实call stack就是一片内存区域而已，只要指定一片内存区域作为call stack，就可以使用calling convention来实现函数调用了。实现函数调用、执行的指令是与这片内存区域在何处无关的，所以用户是可以指定任意的、合法的内存区域来作为call stack的。

所以我就去看了[pthread_create](https://linux.die.net/man/3/pthread_create)的文档，其中是有这样的描述的：

> On Linux/x86-32, the default stack size for a new thread is 2 megabytes. Under the NPTL threading implementation, if the **RLIMIT_STACK** soft resource limit *at the time the program started* has any value other than "unlimited", then it determines the default stack size of new threads. Using **[pthread_attr_setstacksize](https://linux.die.net/man/3/pthread_attr_setstacksize)**(3), the stack size attribute can be explicitly set in the *attr* argument used to create a thread, in order to obtain a stack size other than the default.

即新创建的thread的默认的call stack的大小默认是2M，这说明是可以由用户了来指定新创建的thread的call stack的，我们知道，[pthread_create](https://linux.die.net/man/3/pthread_create)最终是通过调用[clone(2)](https://linux.die.net/man/2/clone)，该函数的第二个入参就是由用户来指定该lightweight process的call stack的。

看到了上面的描述， 其实我又想到了一个问题：一个函数，如果声明的自动变量大小超过了call stack的大小，会发生什么？会发生[Stack overflow](https://en.wikipedia.org/wiki/Stack_overflow)，关于这个问题，参见：

https://www.cnblogs.com/zmlctt/p/3987181.html

https://blog.csdn.net/zDavid_2018/article/details/89255630

维基百科的[Stack overflow](https://en.wikipedia.org/wiki/Stack_overflow)总结的非常好。



## Process VS thread VS lightweight-process

下面是一些我觉得比较好的关于这个问题的讨论：

- [What the difference between lightweight process and thread?](https://stackoverflow.com/questions/10484355/what-the-difference-between-lightweight-process-and-thread)
- [What is the difference between LWP and threads?](https://www.answers.com/Q/What_is_the_difference_between_LWP_and_threads)
- [What are the relations between processes, kernel threads, lightweight processes and user threads in Unix? [closed]](https://unix.stackexchange.com/questions/472324/what-are-the-relations-between-processes-kernel-threads-lightweight-processes)
- [What are Linux Processes, Threads, Light Weight Processes, and Process State](https://www.thegeekstuff.com/2013/11/linux-process-and-threads/)

