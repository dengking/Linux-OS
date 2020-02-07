# Process model

[Thread](https://en.wikipedia.org/wiki/Thread_(computing))和[Process](https://en.wikipedia.org/wiki/Process_(computing))是现代OS实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的关键所在。建立起完整、正确的process model对于在linux-like OS下进行开发、理解linux kernel的实现至关重要。

Process model图示如下：

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Multithreaded_process.svg/220px-Multithreaded_process.svg.png)





## Process 

主要参考文章：[Process](https://en.wikipedia.org/wiki/Process_(computing)) 

> In computing, a **process** is the [instance](https://en.wikipedia.org/wiki/Instance_(computer_science)) of a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is being executed by one or many threads. It contains the program code and its activity. Depending on the [operating system](https://en.wikipedia.org/wiki/Operating_system) (OS), a process may be made up of multiple [threads of execution](https://en.wikipedia.org/wiki/Thread_(computing)) that execute instructions [concurrently](https://en.wikipedia.org/wiki/Concurrency_(computer_science)).

显然thread是process的“成分”，下面看看thread。

### Thread

主要参考文章：[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))

> In [computer science](https://en.wikipedia.org/wiki/Computer_science), a **thread** of execution is the smallest sequence of programmed instructions that can be managed independently by a [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)). [Multiple threads](https://en.wikipedia.org/wiki/Thread_(computing)#Multithreading) can exist within one process, executing [concurrently](https://en.wikipedia.org/wiki/Concurrent_computation) and sharing resources

## 概括process model

综合上面描述，以下我所概括Process model：

“OS是基于process的resource分配，基于[thread](https://en.wikipedia.org/wiki/Thread_(computing))的调度。一个[process](https://en.wikipedia.org/wiki/Process_(computing))可能由多个[thread](https://en.wikipedia.org/wiki/Thread_(computing))组成，[thread](https://en.wikipedia.org/wiki/Thread_(computing))共享process的resource、[并发](https://en.wikipedia.org/wiki/Concurrent_computation)执行 。”

> 注意：上述概括的是现代大多数OS的process model，并非所有OS的process model都是如此，实现上是存在差异的。



上面这段话虽然简短，但是蕴含着丰富的内涵，需要进行详细分析：

### “OS是基于process的resource分配”

这段话意味着：process是OS的进行resource分配的单位，process之间是彼此隔离的。

> 注意: 对于一些特殊的情况，如process之间共享memory的情况除外。

#### OS中有哪些resource？Process需要哪些resource？



- OS是基于process的resource分配，resource包括：
  - Memory 
  - [address space](https://en.wikipedia.org/wiki/Virtual_address_space)




#### process如何实现隔离？



### “基于[thread](https://en.wikipedia.org/wiki/Thread_(computing))的调度”

这段话意味着thread是OS的调度单位。显然每个thread可以独立执行，则每个thread都有执行的必备条件：

- call stack





## process model的演进历史

在[stanford CS 140: Operating Systems (Spring 2014)](https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/index.php)的lecture中总结了Evolution of operating system **process model**:

- Early operating systems supported a single process with a single thread at a time (*single tasking*). They ran batch jobs (one user at a time).
- Some early personal computer operating systems used single-tasking (e.g. MS-DOS), but these systems are almost unheard of today.
- By late 1970's most operating systems were *multitasking* systems: they supported **multiple processes**, but each process had only a single thread.
- In the 1990's most systems converted to *multithreading*: multiple threads within each process.



显然，早期的时候，并没有*multithreading*: multiple threads within each process，所以早期的时候multitasking的task所指**processes**。而随着技术的发展，后来才出现了*multithreading*: multiple threads within each process。

### [multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))相较于[Multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing)优势是什么？

不禁要问：[multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))相较于[Multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing)优势是什么？

这个问题，在[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的[Multithreading](https://en.wikipedia.org/wiki/Computer_multitasking#Multithreading) 章节给出了答案解答。



## [Threads vs. processes](https://en.wikipedia.org/wiki/Thread_(computing)#Threads_vs._processes)





# Linux OS中Process model的实现

参见章节：

1.6.2. Process Implementation
1.6.4. Process Address Space









# process的一系列问题





## 生

创建process

## 占用了哪些资源



## 如何来控制process



### 如何限制资源



## process之间的关系



### process之间如何进行沟通



## 时空的角度



## process的状态







## 死



