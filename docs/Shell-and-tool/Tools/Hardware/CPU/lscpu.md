# `lscpu`



## [lscpu(1) — Linux manual page](https://man7.org/linux/man-pages/man1/lscpu.1.html)



### COLUMNS

| column | explanation                                                  |                                                              |
| ------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| CPU    | The **logical** CPU number of a CPU as used by the Linux kernel. | stackexchange [Understanding output of lscpu](https://unix.stackexchange.com/questions/468766/understanding-output-of-lscpu)中解释了它的算法 |
| CORE   | The logical core number.  A core can contain several CPUs.   |                                                              |
| SOCKET | The logical socket number.  A socket can contain several cores. | 此处的socket，不是我们平时所说的network socket，它是指wikipedia [CPU socket](https://en.wikipedia.org/wiki/CPU_socket)，根据 https://unix.stackexchange.com/a/145249 中的说法，我们可以认为，每个socket对应了一个physical processor |

> NOTE: SOCKET、CORE  、CPU    存在着containing关系，原文已经给出了说明:
>
> - A socket can contain several cores.
> - A core can contain several CPUs.
>
> 实际使用`lscpu`和原文中的描述是不同的。

## Understanding output of lscpu

### stackexchange [Understanding output of lscpu](https://unix.stackexchange.com/questions/468766/understanding-output-of-lscpu)

“CPU(s): 56” represents the number of **logical cores**, which equals “Thread(s) per core” × “Core(s) per socket” × “Socket(s)”. 

One **socket** is one **physical CPU package** (which occupies one **socket** on the **motherboard**); each **socket** hosts a number of **physical cores**, and each core can run one or more threads. In your case, you have two sockets, each containing a 14-core Xeon E5-2690 v4 CPU, and since that supports hyper-threading with two threads, each core can run two threads.

> NOTE: 上述**host**，其实就是contain；
>
> 根据 https://unix.stackexchange.com/a/145249 中的说法:
>
> > You have 2 physical sockets (`Socket(s)`), each contains 1 physical processor.
>
> 也就是说，我们可以认为，每个socket对应了一个physical processor

“NUMA node” represents the memory architecture; “NUMA” stands for [“non-uniform memory architecture”](https://en.wikipedia.org/wiki/Non-uniform_memory_access). In your system, each *socket* is attached to certain DIMM slots, and each physical CPU package contains a memory controller which handles part of the total RAM. As a result, not all physical memory is equally accessible from all CPUs: one physical CPU can directly access the memory it controls, but has to go through the other physical CPU to access the rest of memory. In your system, logical cores 0–13 and 28–41 are in one NUMA node, the rest in the other. So yes, one NUMA node equals one socket, at least in typical multi-socket Xeon systems.

### https://unix.stackexchange.com/a/145249

To answer your question about how many cores and virtual cores you have:

According to your `lscpu` output:

- You have 32 cores (`CPU(s)`) in total.

- You have 2 physical sockets (`Socket(s)`), each contains 1 physical processor.

  > NOTE: 我们可以认为，每个socket对应了一个physical processor

- Each processor of yours has 8 physical cores (`Core(s) per socket`) inside, which means you have 8 * 2 = 16 real cores.

- Each real core can have 2 threads (`Thread(s) per core`), which means you have real cores * threads = 16 * 2 = 32 cores in total.

So you have 32 virtual cores from 16 real cores.

Also see [this](http://buildwindows.wordpress.com/2012/12/13/virtualization-processor-core-logical-processor-virtual-processor-what-does-this-mean/), [this](https://kb.iu.edu/d/avfb) and [this](http://linuxconfig.org/getting-know-a-hardware-on-your-linux-box) link.

## Logical and physical

通过[lscpu(1) — Linux manual page](https://man7.org/linux/man-pages/man1/lscpu.1.html) 和 stackexchange [Understanding output of lscpu](https://unix.stackexchange.com/questions/468766/understanding-output-of-lscpu)，我们可以看到logical和physical，那如何来理解两者呢？