# 前言

[Thread](https://en.wikipedia.org/wiki/Thread_(computing))和[Process](https://en.wikipedia.org/wiki/Process_(computing))是现代OS实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的关键所在。建立起完整、正确的process model对于在linux-like OS下进行开发、理解linux kernel的实现至关重要。

# Process model



## 理解标准

[Thread](https://en.wikipedia.org/wiki/Thread_(computing))和[Process](https://en.wikipedia.org/wiki/Process_(computing))是software engineer非常熟系的概念，它们是标准所定义的两个概念，有着准确的含义，两者之间的关系也是非常清楚的。

关于两者有如下问题需要分析：

### process和thread之间的关系是什么？

其实这个问题本质是：process model。

#### 从演进来分析

在[stanford CS 140: Operating Systems (Spring 2014)](https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/index.php)的lecture中总结了

Evolution of operating system **process model**:

- Early operating systems supported a single process with a single thread at a time (*single tasking*). They ran batch jobs (one user at a time).
- Some early personal computer operating systems used single-tasking (e.g. MS-DOS), but these systems are almost unheard of today.
- By late 1970's most operating systems were *multitasking* systems: they supported **multiple processes**, but each process had only a single thread.
- In the 1990's most systems converted to *multithreading*: multiple threads within each process.



显然，早期的时候，并没有*multithreading*: multiple threads within each process，所以早期的时候multitasking的task所指**processes**。而随着技术的发展，后来才出现了*multithreading*: multiple threads within each process。

那不禁要问：[multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))相较于[Multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing)优势是什么？

这个问题，在[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的[Multithreading](https://en.wikipedia.org/wiki/Computer_multitasking#Multithreading) 章节给出了答案解答。



#### [Threads vs. processes](https://en.wikipedia.org/wiki/Thread_(computing)#Threads_vs._processes)





## 理解标准与实现





## 实现

不同的OS有着不同的实现，但是它们肯定都会符合标准。

按照计算机科学的发展流程来看，应该是首先有计算机理论学家提出了这些概念/标准，然后操作系统厂商再实现这些概念/标准。所以从标准的出现到操作系统厂商实现这些标准，两者之间是有一个时间间隔的。不同厂商的对同一概念/标准的实现方式也会有所不同，并且它们的实现方式也会不断地演进。所以在开始进入到本书的内容之前，我们需要首先建立如下观念：

- 标准与实现之间的关系
- 以发展的眼光来看待软件的演进

下面以operating system如何来实现[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))为例来进行说明，目前存在着两种实现方式：

- user level thread，常称为user thread
- kernel level thread

两者之间的差异可以参见如下文章：

- https://www.geeksforgeeks.org/difference-between-user-level-thread-and-kernel-level-thread/
- [What is a user thread and a kernel thread?](https://superuser.com/questions/455316/what-is-a-user-thread-and-a-kernel-thread)

显然，对于标准所提出的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))，可以有多种实现方式。关于此，维基百科的[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))有着非常好的总结。









process的一系列问题。





# 生

创建process

# 占用了哪些资源



# 如何来控制process



## 如何限制资源



# process之间的关系



## process之间如何进行沟通



# 时空的角度



# process的状态







# 死



