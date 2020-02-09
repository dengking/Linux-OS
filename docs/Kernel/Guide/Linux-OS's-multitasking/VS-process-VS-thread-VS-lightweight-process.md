# 理解标准与实现

[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))和[Process (computing)](https://en.wikipedia.org/wiki/Process_(computing))是software engineer非常熟系的概念，它们是标准所定义的两个概念，有着准确的含义，两者之间的关系也是非常清楚的。按照计算机科学的发展流程来看，应该是首先有计算机理论学家提出了这些概念/标准，然后操作系统厂商再实现这些概念/标准。所以从标准的出现到操作系统厂商实现这些标准，两者之间是有一个时间间隔的。不同厂商的对同一概念/标准的实现方式也会有所不同，并且它们的实现方式也会不断地演进。所以在开始进入到本书的内容之前，我们需要首先建立如下观念：

- 标准与实现之间的关系
- 以发展的眼光来看待软件的演进

下面以operating system如何来实现[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))为例来进行说明，目前存在着两种实现方式：

- user level thread，常称为user thread
- kernel level thread

两者之间的差异可以参见如下文章：

- https://www.geeksforgeeks.org/difference-between-user-level-thread-and-kernel-level-thread/
- [What is a user thread and a kernel thread?](https://superuser.com/questions/455316/what-is-a-user-thread-and-a-kernel-thread)

显然，对于标准所提出的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))，可以有多种实现方式。关于此，维基百科的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))有着非常好的总结。



## 理解标准

> 描述标准的process和thread定义，两者之间的关系。
>
> 以下是一些需要着重强调的：
>
> - process是OS的概念，在instruction层级并没有process的概念。OS使用process的目的是为了实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)，为了充分利用hardware。process是program的执行，它是OS进行resource分配的单位，不同process之间的资源需要完全隔离（特殊情况除外），OS中的所有process共享OS所管理的hardware资源。OS需要清楚地知道process和资源之间的关系，即一个process拥有哪些resource。



# 补充内容

下面是检索到的一些分析地比较好的文章。

## [What the difference between lightweight process and thread?](https://stackoverflow.com/questions/10484355/what-the-difference-between-lightweight-process-and-thread)

I found an answer to the question [here](http://wiki.answers.com/Q/What_is_the_difference_between_LWP_and_threads). But I don't understand some ideas in the answer. For instance, lightweight process is said to share its logical address space with other processes. What does it mean? I can understand the same situation with 2 threads: both of them share one address space, so both of them can read any variables from bss segment (for example). But we've got a lot of different processes with different bss sections and I dunno how to share all of them.



### [A](https://stackoverflow.com/a/10485868)

From MSDN, [Threads and Processes](http://msdn.microsoft.com/en-us/library/ms164740.aspx):

> Processes exist in the operating system and correspond to what users see as programs or applications. A thread, on the other hand, exists within a process. **For this reason, threads are sometimes referred to as light-weight processes.** Each process consists of one or more threads.



### [A](https://stackoverflow.com/a/40848101)

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





## [What is the difference between LWP and threads?](https://www.answers.com/Q/What_is_the_difference_between_LWP_and_threads)

This explains the difference between LWP-Process-Thread:

A **light-weight process** (LWP) is a means of achieving multitasking. In contrast to a regular (full-blown) process, an LWP shares all (or most of) its logical address space and system resources with other process(es) （注意的是，这里的process所指的是light weight process，而不是我们寻常意义的process，在这篇文章中，传统意义的process使用full-blown process来表示）; in contrast to a thread, a light-weight process has its own private **process identifier** and parenthood relationships with other processes. Moreover, while a **thread** can either be managed at the **application level** or by the **kernel**, an **LWP** is always managed by the **kernel** and it is scheduled as a regular process. One significant example of a kernel that supports LWPs is the **Linux kernel**. On most systems, a light-weight process also differs from a **full-blown process**, in that it only consists of the bare minimum execution context and accounting information that is needed by the scheduler, hence the term *light-weight*. Generally, a **process**（full-blown process） refers to an instance of a program, while an LWP represents a thread of execution of a program (indeed, **LWP**s can be conveniently used to implement **thread**s, if the underlying kernel does not directly support them). Since a thread of execution does not need as much state information as a process, a light-weight process does not carry such information. As a consequence of the fact that LWPs share most of their resources with other LWPs, they are unsuitable for certain applications, where multiple full-blown processes are needed, e.g. to avoid memory leaks (a process can be replaced by another one) or to achieve privilege separation (processes can run under other credentials and have other permissions). Using multiple processes also allows the application to more easily survive if a process of the pool crashes or is exploited.





# [What are the relations between processes, kernel threads, lightweight processes and user threads in Unix? [closed]](https://unix.stackexchange.com/questions/472324/what-are-the-relations-between-processes-kernel-threads-lightweight-processes)

