# 前言

在本书中频繁出现process，lightweight process，thread 这些词语，有必要对它们进行区别，否则很难准确理解书中内容；

## 理解标准与实现

[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))和[Process (computing)](https://en.wikipedia.org/wiki/Process_(computing))是software engineer非常熟系的概念，它们是标准所定义的两个概念，有着准确的含义，两者之间的关系也是非常清楚的。按照计算机科学的发展流程来看，应该是首先有计算机理论学家提出了这些概念/标准，然后操作系统厂商再实现这些概念/标准。所以从标准的出现到操作系统厂商实现这些标准，两者之间是有一个时间间隔的。不同厂商的对同一概念/标准的实现方式也会有所不同，并且它们的实现方式也会不断地演进。所以在开始进入到本书的内容之前，我们需要首先建立如下观念：

- 标准与实现之间的关系
- 以发展的眼光来看待软件的演进

下面以operating system如何来实现[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))为例来进行说明，目前存在着两种实现方式：

- user level thread，常称为user thread
- kernel level thread

两者之间的差异可以参见如下文章：

- https://www.geeksforgeeks.org/difference-between-user-level-thread-and-kernel-level-thread/
- [What is a user thread and a kernel thread?](https://superuser.com/questions/455316/what-is-a-user-thread-and-a-kernel-thread)

显然，对于标准所提出的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))，可以有多种实现方式。

关于此，维基百科的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))有着非常好的总结。

那linux kernel是如何来实现[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))的呢？下面是从本书的一些介绍：

chapter 1.1. Linux Versus Other Unix-Like Kernels

> Multithreaded application support
>
> Most modern operating systems have some kind of support for multithreaded applications that is, user programs that are designed in terms of many relatively independent execution flows that share a large portion of the application data structures. A multithreaded user application could be composed of many lightweight processes (LWP), which are processes that can operate on a common address space, common physical memory pages, common opened files, and so on. Linux defines its own version of lightweight processes, which is different from the types used on other systems such as SVR4 and Solaris. While all the commercial Unix variants of LWP are based on kernel threads, Linux regards lightweight processes as the basic execution context and handles them via the nonstandard  `clone( )` system call.



其实更好的方式不是根据本书中的内容来推断Linux OS实现POSIX threads的方式，最好的方式是阅读linux的man，在[PTHREADS(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)的Linux implementations of POSIX threads章节给出了linux实现POSIX threads的方式的详细信息，其中也给出了查看相关实现的命令。可以确定的是，无论采用哪种方式，最终都是依赖 [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) 。



关于本段，有疑问：LWP VS thread VS kernel thread?

上一段中所描述的：Linux **kernel threads** do not represent the basic **execution context** abstraction.

本段中所描述的：Linux regards **lightweight processes** as the basic **execution context** and handles them via the nonstandard  `clone( )` system call.

显然，kernel thread不是linux的lightweight process。

显然linux的lightweight process是需要由linux的scheduler来进行调度的，那kernel thread是由谁来进行调度呢？下面是一些有价值的内容：

- [Are kernel threads processes and daemons?](https://unix.stackexchange.com/questions/266434/are-kernel-threads-processes-and-daemons)
- [Difference between user-level and kernel-supported threads?](https://stackoverflow.com/questions/15983872/difference-between-user-level-and-kernel-supported-threads)
- [Kernel threads made easy](https://lwn.net/Articles/65178/)

在linux中，lightweight process对应的是thread吗？



需要注意的是，在本书中有时候会将lightweight process简称为process，比如上面这段话中的这句：

> A multithreaded user application could be composed of many **lightweight processes** (LWP), which are **processes** that can operate on a common address space, common physical memory pages, common opened files, and so on. 

所以在本书中，process不一定指的是标准的[Process (computing)](https://en.wikipedia.org/wiki/Process_(computing))，有的时候指的是lightweight process，为了便于区分，会在note中进行特殊说明。

关于lightweight process，参见：

- [Light-weight process](https://en.wikipedia.org/wiki/Light-weight_process)





下面是检索到的一些分析地比较好的文章。

# [What the difference between lightweight process and thread?](https://stackoverflow.com/questions/10484355/what-the-difference-between-lightweight-process-and-thread)

I found an answer to the question [here](http://wiki.answers.com/Q/What_is_the_difference_between_LWP_and_threads). But I don't understand some ideas in the answer. For instance, lightweight process is said to share its logical address space with other processes. What does it mean? I can understand the same situation with 2 threads: both of them share one address space, so both of them can read any variables from bss segment (for example). But we've got a lot of different processes with different bss sections and I dunno how to share all of them.



## [A](https://stackoverflow.com/a/10485868)

From MSDN, [Threads and Processes](http://msdn.microsoft.com/en-us/library/ms164740.aspx):

> Processes exist in the operating system and correspond to what users see as programs or applications. A thread, on the other hand, exists within a process. **For this reason, threads are sometimes referred to as light-weight processes.** Each process consists of one or more threads.



## [A](https://stackoverflow.com/a/40848101)

I am not sure that answers are correct here, so let me post my version.

There is a difference between **process** - **LWP** (lightweight process) and **user thread**. I will leave process definition aside since that's more or less known and focus on `LWP vs user threads`. **LWP** is what essentially are called **today threads**. Originally, **user thread** meant a thread that is managed by the **application** itself and the **kernel** does not know anything about it. **LWP**, on the other hand, is a unit of scheduling and execution by the **kernel**.

Example: Let's assume that system has 3 other processes running and scheduling is round-robin without priorities. And you have 1 processor/core.

*Option 1*. You have 2 user threads using one LWP. That means that from OS perspective you have ONE scheduling unit. Totally there are 4 LWP running (3 others + 1 yours). Your LWP gets 1/4 of total CPU time and since you have 2 user threads, each of them gets 1/8 of total CPU time (depends on your implementation)

*Option2*. You have 2 LWP. From OS perspective, you have TWO scheduling units. Totally there are 5 LWP running. Your LWP gets 1/5 of total CPU time EACH and your application get's 2/5 of CPU.

Another rough difference - LWP has pid (process id), user threads do not.

For some reason, naming got little messed and we refer to LWP as threads.

There are definitely more differences, but please, refer to slides.http://www.cosc.brocku.ca/Offerings/4P13/slides/threads.ppt

EDIT:

After posting, I found a good article that explains everything in more details and is in better English than I write. http://www.thegeekstuff.com/2013/11/linux-process-and-threads/





# [What is the difference between LWP and threads?](https://www.answers.com/Q/What_is_the_difference_between_LWP_and_threads)

This explains the difference between LWP-Process-Thread:

A **light-weight process** (LWP) is a means of achieving multitasking. In contrast to a regular (full-blown) process, an LWP shares all (or most of) its logical address space and system resources with other process(es) （注意的是，这里的process所指的是light weight process，而不是我们寻常意义的process，在这篇文章中，传统意义的process使用full-blown process来表示）; in contrast to a thread, a light-weight process has its own private **process identifier** and parenthood relationships with other processes. Moreover, while a **thread** can either be managed at the **application level** or by the **kernel**, an **LWP** is always managed by the **kernel** and it is scheduled as a regular process. One significant example of a kernel that supports LWPs is the **Linux kernel**. On most systems, a light-weight process also differs from a **full-blown process**, in that it only consists of the bare minimum execution context and accounting information that is needed by the scheduler, hence the term *light-weight*. Generally, a **process**（full-blown process） refers to an instance of a program, while an LWP represents a thread of execution of a program (indeed, **LWP**s can be conveniently used to implement **thread**s, if the underlying kernel does not directly support them). Since a thread of execution does not need as much state information as a process, a light-weight process does not carry such information. As a consequence of the fact that LWPs share most of their resources with other LWPs, they are unsuitable for certain applications, where multiple full-blown processes are needed, e.g. to avoid memory leaks (a process can be replaced by another one) or to achieve privilege separation (processes can run under other credentials and have other permissions). Using multiple processes also allows the application to more easily survive if a process of the pool crashes or is exploited.





# [What are Linux Processes, Threads, Light Weight Processes, and Process State](https://www.thegeekstuff.com/2013/11/linux-process-and-threads/)

Linux has evolved a lot since its inception. It has become the most widely used operating system when in comes to servers and mission critical work. Though its not easy to understand Linux as a whole but there are aspects which are fundamental to Linux and worth understanding.

In this article, we will discuss about Linux processes, threads and light weight processes and understand the difference between them. Towards the end, we will also discuss various states for Linux processes.

### Linux Processes

In a very basic form, Linux process can be visualized as running instance of a program. For example, just open a text editor on your Linux box and a text editor process will be born.

Here is an example when I opened `gedit` on my machine :

```
$ gedit &
[1] 5560

$ ps -aef | grep gedit
1000      5560  2684  9 17:34 pts/0    00:00:00 gedit
```

First command (`gedit` &) opens `gedit` window while second [ps command](https://www.thegeekstuff.com/2011/04/ps-command-examples/) (`ps -aef | grep gedit`) checks if there is an associated process. In the result you can see that there is a process associated with `gedit`.

Processes are fundamental to Linux as each and every work done by the OS is done in terms of and by the processes. Just think of anything and you will see that it is a process. This is because any work that is intended to be done requires system resources ( that are provided by kernel) and it is a process that is viewed by kernel as an entity to which it can provide system resources.

Processes have priority based on which kernel context switches them. A process can be pre-empted if a process with higher priority is ready to be executed.



For example, if a process is waiting for a system resource like some text from text file kept on disk then kernel can schedule a higher priority process and get back to the waiting process when data is available. This keeps the ball rolling for an operating system as a whole and gives user a feeling that tasks are being run in parallel.

Processes can talk to other processes using Inter process communication methods and can share data using techniques like shared memory.

In Linux, fork() is used to create new processes. These new processes are called as child processes and each child process initially shares all the segments like text, stack, heap etc until child tries to make any change to stack or heap. In case of any change, a separate copy of stack and heap segments are prepared for child so that changes remain child specific. The text segment is read-only so both parent and child share the same text segment. [C fork function](https://www.thegeekstuff.com/2012/05/c-fork-function/) article explains more about fork().

### Linux Threads vs Light Weight Processes

Threads in Linux are nothing but a flow of execution of the process. A process containing multiple execution flows is known as multi-threaded process.

For a non multi-threaded process there is only execution flow that is the main execution flow and hence it is also known as single threaded process. **For Linux kernel , there is no concept of thread**. Each thread is viewed by kernel as a separate process but these processes are somewhat different from other normal processes. I will explain the difference in following paragraphs.

Threads are often mixed with the term Light Weight Processes or LWPs. The reason dates back to those times when **Linux supported threads at user level only**. This means that even a multi-threaded application was viewed by kernel as a single process only. This posed big challenges for the library that managed these user level threads because it had to take care of cases that a thread execution did not hinder if any other thread issued a blocking call.

Later on the implementation changed and processes were attached to each thread so that kernel can take care of them. But, as discussed earlier, Linux kernel does not see them as threads, each thread is viewed as a process inside kernel. These processes are known as **light weight processes**.

The main difference between a light weight process (LWP) and a normal process is that LWPs share same address space and other resources like open files etc. As some resources are shared so these processes are considered to be light weight as compared to other normal processes and hence the name light weight processes.

So, effectively we can say that threads and light weight processes are same. It’s just that thread is a term that is used at user level while light weight process is a term used at kernel level.

From implementation point of view, threads are created using functions exposed by POSIX compliant `pthread` library in Linux. Internally, the `clone()` function is used to create a normal as well as a **light weight process**. This means that to create a normal process **fork()** is used that further calls **clone()** with appropriate arguments while to create a thread or LWP, a function from `pthread` library calls `clone()` with relevant flags. So, the main difference is generated by using different flags that can be passed to `clone()` function.

Read more about `fork()` and `clone()` on their respective man pages.

[How to Create Threads in Linux](https://www.thegeekstuff.com/2012/04/create-threads-in-linux/) explains more about threads.

### Linux Process States

Life cycle of a normal Linux process seems pretty much like real life. Processes are born, share resources with parents for sometime, get their own copy of resources when they are ready to make changes, go through various states depending upon their priority and then finally die. In this section will will discuss various states of Linux processes :

- RUNNING – This state specifies that the process is either in execution or waiting to get executed.
- INTERRUPTIBLE – This state specifies that the process is waiting to get interrupted as it is in sleep mode and waiting for some action to happen that can wake this process up. The action can be a hardware interrupt, signal etc.
- UN-INTERRUPTIBLE – It is just like the INTERRUPTIBLE state, the only difference being that a process in this state cannot be waken up by delivering a signal.
- STOPPED – This state specifies that the process has been stopped. This may happen if a signal like SIGSTOP, SIGTTIN etc is delivered to the process.
- TRACED – This state specifies that the process is being debugged. Whenever the process is stopped by debugger (to help user debug the code) the process enters this state.
- ZOMBIE – This state specifies that the process is terminated but still hanging around in kernel process table because the parent of this process has still not fetched the termination status of this process. Parent uses wait() family of functions to fetch the termination status.
- DEAD – This state specifies that the process is terminated and entry is removed from process table. This state is achieved when the parent successfully fetches the termination status as explained in ZOMBIE state.



# [What are the relations between processes, kernel threads, lightweight processes and user threads in Unix? [closed]](https://unix.stackexchange.com/questions/472324/what-are-the-relations-between-processes-kernel-threads-lightweight-processes)

