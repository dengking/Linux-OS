# Computer multitasking

Multitasking即多任务，是现代OS的必备feature，本章就对此进行分析。

在文章[Abstraction and model](https://dengking.github.io/Post/Abstraction/Abstraction-and-model/)的[Task model](https://dengking.github.io/Post/Abstraction/Abstraction-and-model/#task-model)章节总结了Task model，支持multitasking的OS kernel是可以使用[task model](https://dengking.github.io/Post/Abstraction/Abstraction-and-model/)来进行描述的。

## 维基百科[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)

维基百科[Computer multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)对multitasking总结地非常好，下面是我的阅读笔记：

需要注意的是，我们应该以发展的眼光来看待multitask的发展，multitask是一个很早提出的**概念**：

> In [computing](https://en.wikipedia.org/wiki/Computing), **multitasking** is the [concurrent](https://en.wikipedia.org/wiki/Concurrent_computing) execution of multiple tasks

显然这个概念所强调的是task的concurrent（并发）执行。至于task所指为何？是process（进程）还是thread（线程）？不同的实现肯定答案就不同了。在早期，thread还没有出现的时候，显然task所指为process。但是随着技术的发展，提出了thread的概念，如果OS的实现支持的thread的话，那么task就可能是指thread了（显然task是一种抽象的描述，类似于[kernel control path](https://dengking.github.io/Post/Abstraction/Abstraction/#kernel-control-path)）。

在本文的[Multithreading](https://en.wikipedia.org/wiki/Computer_multitasking#Multithreading)章节就说明了这种演进：从process到thread。这一段的论述是比较好的，它说明了thread的价值所在。在本文的开头也对此进行了说明：

> Depending on the operating system, a task might be as large as an entire application program, or might be made up of smaller [threads](https://en.wikipedia.org/wiki/Thread_(computing)) that carry out portions of the overall program.



另外一个关于multitask需要进行强调的是：multitask是operating system层的概念，在hardware层没有multitask的概念，所以multitask由OS厂商实现，在hardware层比如CPU压根就没有这样的概念。不过CPU厂商肯定会为OS提供便于实现multitask的硬件支持，比如提供一些专门的指令等。



## 如何实现multitask？

那如何实现multitask呢？这是本章要重点讨论的问题，本章将分多篇对multitask的实现进行梳理。

### 关于[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)实现的一些思考

OS为了支持[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)都会衍生出一些列的问题，并且实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)往往需要hardware和OS同时支持：

问题一：正如[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的定义所支持，OS中会存在多个task，那如何保证task之间彼此的隔离、互不侵犯？

这个问题在本文的[Memory protection](https://en.wikipedia.org/wiki/Computer_multitasking#Memory_protection)进行了说明，其实最根本的措施是每个process都有自己的[address space](https://en.wikipedia.org/wiki/Virtual_address_space)。



问题二：operating system's [scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))如何实现来支持[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)？

[scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))的实现是一个非常宏大的主题，在此我们仅仅讨论[scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))的调度策略，根据[scheduler](https://en.wikipedia.org/wiki/Scheduling_(computing))的调度策略，可以将[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)分为如下两种：

- [pre-emptive multitasking](https://en.wikipedia.org/wiki/Pre-emptive_multitasking)
- [cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking)

需要注意的是，这两种方式是普遍存在的，两者各有千秋，OS的实现可以根据需求选择其中任意一种。

无论哪种[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)，在进行调度的时候，都涉及[context switch](https://en.wikipedia.org/wiki/Context_switch)。



## Task是control path

在[Control-path-&-Context-&-Context-switch](./Control-path-&-Context-&-Context-switch.md)中，我们已经将task归入了control path的范轴，在下一章中，将对它进行详细分析。



## Linux OS的实现

在本书中，其实并没有专门的章节来描述linux OS中multitask的实现，而是分散在多个章节。所以在此对linux OS的multitask的实现进行综述。



