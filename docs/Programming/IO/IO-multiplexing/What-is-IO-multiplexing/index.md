# What is IO multiplexing

本章讨论"What is IO multiplexing"，重要参考的内容有:

一、zhihu [I/O多路复用技术（multiplexing）是什么？](https://www.zhihu.com/question/28594409)

收录在 `zhihu-What-is-IO-multiplexing` 章节中，通过这篇文章，基本上了解了Linux IO multiplexing。需要注意的是，这篇文章所讲述的是Linux的implementation，它并不能够代表IO multiplexing的全部。

二、APUE `14.4 I/O Multiplexing`

三、unp [Chapter 6. I/O Multiplexing: The select and poll Functions](https://notes.shichao.io/unp/ch6/)

四、wiki [Io Multiplexing](http://c2.com/cgi/fullSearch?search=IoMultiplexing)

**I/O multiplexing** means what it says - allowing the programmer to examine and block on multiple I/O streams (or other "synchronizing" events), being notified whenever any one of the streams is active so that it can process data on that stream.

In the Unix world, it's called `select()` or `poll()` (when using the [CeeLanguage](http://wiki.c2.com/?CeeLanguage)  API for Unix). In the 

MicrosoftWindowsApi  world, it's called `WaitForMultipleObjects()`. Other languages/environments have similar features:

The advantage of [IoMultiplexing](http://wiki.c2.com/?IoMultiplexing) is that it allows blocking on multiple resources **simultaneously**, without needing to use polling (which wastes CPU cycles) or **multithreading** (which can be difficult to deal with, especially if threads are introduced into an otherwise sequential app only for the purpose of pending on multiple descriptors).

> With the understanding, of course, that the CPU cycles are gonna get burned somewhere anyway, and even if your task/process is not threaded, the system as a whole will have other threads/tasks running.





## IO multiplexing是一种event notification mechansim

TODO

## Multiplexing and demultiplexing

在 `What-is-multiplexing` 章节中，我们知道了:

> 如何来理解multiplexing？multiplexing的关键在于many和one，下面是一些例子: 
>
> 在 [computing](https://en.wikipedia.org/wiki/Computing)的 **I/O multiplexing**中，many是multiple [input/output](https://en.wikipedia.org/wiki/Input/output) [events](https://en.wikipedia.org/wiki/Event_(computing)) 而one则是a single [event loop](https://en.wikipedia.org/wiki/Event_loop) object；
>
> many IO event and one event loop object；

> 在现实application中，都需要有reverse operation: **demultiplexing**，**demultiplexing**其实非常类似于dispatch

在 IO multiplexing mechansim中，同样有着 "demultiplexing" 的存在，关于此的文章有:

1、zhihu [如何深刻理解reactor和proactor？](https://www.zhihu.com/question/26943938)

> **Event Demultiplexer and Event Handler**
>
> 一般地,I/O多路复用机制都依赖于一个事件**多路分离器(Event Demultiplexer)**。**分离器对象**可将来自事件源的I/O事件分离出来，并分发到对应的**read/write事件处理器(Event Handler)**(或回调函数)。开发人员预先注册需要处理的事件及其事件处理器（或回调函数）；事件分离器负责将请求事件传递给事件处理器。

## Use pattern: reactor 和 proactor

由于reactor 和 proactor一般归入design pattern的范畴，因此，将它们放到了工程parallel-computing中了。

两种pattern都使用了IO multiplexing，但是它们之间有着差别，通过它们的差别我们能够看出IO multiplexing的本质，我们也知道，Linux IO multiplexing是使用reactor的。

关于此的非常好的文章:

1、zhihu [如何深刻理解reactor和proactor？](https://www.zhihu.com/question/26943938)

