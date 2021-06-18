# Linux OS kernel is event-driven

为了更好地理解本书，我觉得有必要建立起对OS运行概况的高屋建瓴的、整体的认知（big picture），这样才能够梳理清楚书中各个章节之间的关联。

从一个software engineer的视角来看，我觉得OS kernel可以看做是一个**event-driven system**，即整个OS kernel的运行是[event](https://en.wikipedia.org/wiki/Event_(computing))驱动的，linux OS kernel的实现采用（部分）的是[Event-driven architecture](https://en.wikipedia.org/wiki/Event-driven_architecture) ( [Event-driven programming](https://en.wikipedia.org/wiki/Event-driven_programming) )。下面对这个论断的分析：

在本书[chapter 1.4. Basic Operating System Concepts](../../Book-Understanding-the-Linux-Kernel/Chapter-1-Introduction)所介绍的：

> The operating system interact with the hardware components, servicing all low-level programmable elements included in the hardware platform.

> A Unix-like operating system hides all low-level details concerning the physical organization of the computer from applications run by the user.

显然，OS kernel直接和hardware打交道，那有哪些hardware呢？如下：

1、[I/O devices](https://en.wikipedia.org/wiki/Input/output)

Chapter 13. I/O Architecture and Device Drivers

补充：[Operating System - I/O Hardware](https://www.tutorialspoint.com/operating_system/os_io_hardware.htm)

2、Clock and Timer Circuits

"Chapter 6. Timing Measurements"

目前，基本上所有的hardware都是通过[interrupt](https://en.wikipedia.org/wiki/Interrupt)来通知OS kernel的，然后其对应的[Interrupt handler](https://en.wikipedia.org/wiki/Interrupt_handler)会被触发执行，也就是OS kernel是[interrupt-driven](https://en.wikipedia.org/wiki/Interrupt)的。拥有这样的认知对于完整地掌握本书的内容十分重要，因为它描述了OS kernel运行的概况。

本书的"Chapter 4. Interrupts and Exceptions"专门描述中断相关内容，它是后面很多章节的基础，因为OS中有太多太多的活动都是interrupt触发的，比如：

TODO: 此处添加一些例子

本书的"Chapter 6. Timing Measurements"主要描述的是timing measurements相关的hardware（主要包括Clock and Timer Circuits）以及OS kernel中由timing measurement驱动的重要的活动（下面会有介绍），正如本章开头所述：

> Countless computerized activities are driven by timing measurements

OS kernel的众多核心activity是driven by timing measurements，正如"6.2. The Linux Timekeeping Architecture"中所总结的：

1、Updates the time elapsed since system startup

2、Updates the time and date

3、Determines, for every CPU, how long the current process has been running, and preempts it if it has exceeded the time allocated to it. The allocation of time slots (also called "quanta") is discussed in Chapter 7.

> NOTE: 这个活动非常重要，它是OS实现[Time-sharing](https://en.wikipedia.org/wiki/Time-sharing)，进而实现[multitasking](https://en.wikipedia.org/wiki/Computer_multitasking)的关键所在。在linux kernel的实现中，它的入口函数是 [`scheduler_tick`](https://elixir.bootlin.com/linux/latest/ident/scheduler_tick)，搜索这个函数，可以查询到非常多关于它的分析。
>
> 本书中关于这个函数的章节：
>
> - 6.4. Updating System Statistics
>
> - 7.4. Functions Used by the Scheduler

4、Updates resource usage statistics.

5、Checks whether the interval of time associated with each software timer (see the later section "Software Timers and Delay Functions") has elapsed.



通过上面的内容可以看到：timer interrupt对系统非常重要，它就相当于系统的heartbeat，它驱动着系统的运转，它就相当于相同的系统的[Electric motor](https://en.wikipedia.org/wiki/Electric_motor)（内燃机运转带动整个系统运转起来）。



## System call也相当于interrupt

参见 `System-call` 章节。





## 总结

通过上述分析，我们可以看到OS kernel的所有activity其实都可以认为是event-driven的：OS kernel管理着hardware、process，它作为两者之间的中间层，可以认为OS的所有的activity都是由它们触发的。

建立这样的一个统一模型对于后面讨论OS kernel的实现思路是非常重要的。



我们惊喜的发现站在计算机科学的不同的层次来描述本质上非常类似的事务有着不同的说法，下面对此进行了对比：

| Hardware                                                     | Software                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [Interrupt-driven](https://en.wikipedia.org/wiki/Interrupt)  | [Event-driven architecture](https://en.wikipedia.org/wiki/Event-driven_architecture) / [Event-driven programming](https://en.wikipedia.org/wiki/Event-driven_programming) |
| [Interrupt](https://en.wikipedia.org/wiki/Interrupt)         | [Event (computing)](https://en.wikipedia.org/wiki/Event_(computing)) |
| [Interrupt handler](https://en.wikipedia.org/wiki/Interrupt_handler)/[Interrupt service routine](https://en.wikipedia.org/wiki/Interrupt_handler) | [Event handler](https://en.wikipedia.org/wiki/Event_(computing)#Event_handler)/[Callback function](https://en.wikipedia.org/wiki/Callback_(computer_programming)) |

各种interrupt就是所谓的event。

