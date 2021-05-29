# Process model

[Thread](https://en.wikipedia.org/wiki/Thread_(computing))和[Process](https://en.wikipedia.org/wiki/Process_(computing))是现代OS实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的关键所在。建立起完整、正确的process model对于在linux OS下进行开发、理解linux kernel的实现至关重要。需要注意的是， 本文所述的process model是一个[Conceptual model](https://en.wikipedia.org/wiki/Conceptual_model)，也可以说本文所描述的process model是标准所定义的。不同的OS对process model的实现方式是不同的。

Process model图示如下：

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Multithreaded_process.svg/220px-Multithreaded_process.svg.png)





## Process 

主要参考文章：[Process](https://en.wikipedia.org/wiki/Process_(computing)) 

> In computing, a **process** is the [instance](https://en.wikipedia.org/wiki/Instance_(computer_science)) of a [computer program](https://en.wikipedia.org/wiki/Computer_program) that is being executed by one or many threads. It contains the program code and its activity. Depending on the [operating system](https://en.wikipedia.org/wiki/Operating_system) (OS), a process may be made up of multiple [threads of execution](https://en.wikipedia.org/wiki/Thread_(computing)) that execute instructions [concurrently](https://en.wikipedia.org/wiki/Concurrency_(computer_science)).

显然thread是process的“成分”，下面看看thread。

## Thread

主要参考文章：[Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))

> In [computer science](https://en.wikipedia.org/wiki/Computer_science), a **thread** of execution is the smallest sequence of programmed instructions that can be managed independently by a [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing)). [Multiple threads](https://en.wikipedia.org/wiki/Thread_(computing)#Multithreading) can exist within one process, executing [concurrently](https://en.wikipedia.org/wiki/Concurrent_computation) and sharing resources

## 概括process model

综合上面描述，以下我所概括Process model：

“OS是基于process的resource分配，基于[thread](https://en.wikipedia.org/wiki/Thread_(computing))的调度。一个[process](https://en.wikipedia.org/wiki/Process_(computing))可能由多个[thread](https://en.wikipedia.org/wiki/Thread_(computing))组成，[thread](https://en.wikipedia.org/wiki/Thread_(computing))共享process的resource，[并发](https://en.wikipedia.org/wiki/Concurrent_computation)执行 。”

> 注意：上述概括的是现代大多数OS的process model，并非所有OS的process model都是如此，实现上是存在差异的。



上面这段话虽然简短，但是蕴含着丰富的内涵，需要进行详细分析：

### OS是基于process的resource分配

这段话意味着：process是OS的进行resource分配的单位，process之间是彼此隔离的。

> 注意: 对于一些特殊的情况，如process之间共享memory的情况除外。

#### OS中有哪些resource？Process需要哪些resource？

参见[Process mode: resource](./01-Process-model-resource.md)


#### Process如何实现隔离？

TODO

### OS基于[thread](https://en.wikipedia.org/wiki/Thread_(computing))的调度

这段话意味着thread是OS的调度单位。显然每个thread可以独立执行，则每个thread都有执行的必备条件：

- call stack

在维基百科[Threads vs. processes](https://en.wikipedia.org/wiki/Thread_(computing)#Threads_vs._processes)中有如下描述：

显然operating system为了支持multiple thread，就必须要让每个thread有一个自己的[call stack](https://en.wikipedia.org/wiki/Call_stack)；在Wikipedia的[Thread control block](https://en.wikipedia.org/wiki/Thread_control_block)中就谈及每个thread都有一个[Stack pointer](https://en.wikipedia.org/wiki/Stack_pointer)，而[Process control block](https://en.wikipedia.org/wiki/Process_control_block)中，可能就不需要[Stack pointer](https://en.wikipedia.org/wiki/Stack_pointer)了；



## Process model的演进历史

在[stanford CS 140: Operating Systems (Spring 2014)](https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/index.php)的lecture中总结了Evolution of operating system **process model**:

1、Early operating systems supported a single process with a single thread at a time (*single tasking*). They ran batch jobs (one user at a time).

2、Some early personal computer operating systems used single-tasking (e.g. MS-DOS), but these systems are almost unheard of today.

3、By late 1970's most operating systems were *multitasking* systems: they supported **multiple processes**, but each process had only a single thread.

4、In the 1990's most systems converted to *multithreading*: multiple threads within each process.



显然，早期的时候，并没有"*multithreading*: multiple threads within each process"，所以早期的时候multitasking的task所指**processes**。而随着技术的发展，后来才出现了"*multithreading*: multiple threads within each process"。



## [Multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)) VS [Multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing)

不禁要问：[multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))相较于[Multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing)优势是什么？

对-两者的比较，落脚点都在 "multiple thread 处于同一个process address space"，这带来了如下优势:

1、inter-thread communication 比 inter-process communication是更加高效的

multiple thread天然的share the same process address space。

2、"switching between threads does not involve changing the memory context"

> 这段话源自: wikipedia [Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking) # [Multithreading](https://en.wikipedia.org/wiki/Computer_multitasking#Multithreading) 章节

### wikipedia [Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的 [Multithreading](https://en.wikipedia.org/wiki/Computer_multitasking#Multithreading) 

As multitasking greatly improved the throughput of computers, programmers started to implement applications as sets of cooperating processes (e. g., one process gathering input data, one process processing input data, one process writing out results on disk). This, however, required some tools to allow processes to efficiently exchange data.

[Threads](https://en.wanweibaike.com/wiki-Thread_(computer_science)) were born from the idea that the most efficient way for cooperating processes to **exchange data** would be to share their entire memory space. Thus, threads are effectively processes that run in the same memory context and share other resources with their [parent processes](https://en.wanweibaike.com/wiki-Parent_process), such as open files. Threads are described as *lightweight processes* because switching between threads does not involve changing the memory context.[[8\]](https://en.wanweibaike.com/wiki-Multitasking#cite_note-8)[[9\]](https://en.wanweibaike.com/wiki-Multitasking#cite_note-9)[[10\]](https://en.wanweibaike.com/wiki-Multitasking#cite_note-10)

> NOTE: 
>
> 对 "cooperating processes" 而言，最最高效的 "**exchange data**" 的方式是: "share their entire memory space"
>
> "Threads are described as *lightweight processes* because switching between threads does not involve changing the memory context"
>
> context switch的角度来进行分析的



### 另外一个优势

我觉得另外一个优势是：thread使concurrency编程更加容易实现。我们常常需要使用第三方库，如果想要充分实现concurrency，如果不支持thread，则库中只能够使用process，在这种情况下，就涉及和第三方库中的process中的IPC，显然这会导致和第三库的交互会变得非常困难；而如果使用thread，则库的使用者和库处于同一个process space，两者之间的交互是非常容易的，显然这种设计能够设计发挥concurrency的优势。



## 总结

process是OS的概念，在instruction层级并没有process的概念（[分层思想](https://dengking.github.io/Post/Abstraction/Abstraction-and-architecture-and-layer/)）。OS使用process的目的是为了实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)，为了充分利用hardware（one-to-many model）。process是program的执行，它是OS进行resource分配的单位，不同process之间的资源需要完全隔离（特殊情况除外），OS中的所有process共享OS所管理的hardware资源。OS需要清楚地知道process和资源之间的关系，即一个process拥有哪些resource（所以，每个process需要有自己独立的address space、file table等）。

