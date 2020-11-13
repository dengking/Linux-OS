# Linux sync and async VS blocking and non-blocking

前面介绍了Linux OS中的IO model，现在有必要对Linux OS中的这些概念进行总结了。



## Signal

信号是一种软件中断，所以也是一种异步。

在APUE的10.2 Signal Concepts中有下面这样的一段话：

> Signals are classic examples of **asynchronous events**. They occur at what appear to be random times to the process. The process can’t simply test a variable (such as errno) to see whether a signal has occurred; instead, the process has to tell the kernel ‘‘if and when this signal occurs, do the following.’’We can tell the kernel to do one of three things when a signal occurs. We call this the disposition of the signal, or the action associated with a signal.

Linux的signal的event handler一般被称为**signal handler**，OS提供了注册的signal handler的接口给用户，让他们来指定对signal的处理；



## APUE 14.2 非阻塞IO

阻塞的函数往往是和进程的阻塞状态有关的，一旦阻塞，则表示进程将暂停执行。

这一节最后一段引起了我的思考:前面它说，执行低速的系统调用是可能会使进程永远阻塞的一类系统调用。对于这段话我的想法是当进程被阻塞的时候，此时进程的状态是blocking。

在最后一段中，作者又介绍，可以使用多线程，让其中一个线程来执行低速的io操作，其他线程则无需阻塞，可以继续执行。

显然，此时进程的一个线程被阻塞了，但是进程中的其他线程仍然继续运行，那么此时进程的状态是什么呢？



## APUE 16.8

这一节描述了非阻塞和异步的socket IO。

非阻塞的IO，调用者为了知道可以进行IO了，需要不断地去尝试，如果可以，则执行，如果不可以则返回，如此往复。异步IO，则不需要调用者去主动地不断尝试，OS会在IO操作可以执行的情况下，通过消息或者其他的方式来通知调用者。显然，这是非阻塞IO和异步IO的一个非常重要的差别。

除了本节所描述的这两种形式的IO，还存在IO multiplex

在APUE的第14章，对这些内容进行了整体地介绍。




## Linux中基于signal的asynchronous IO

在[pipe(7) - Linux man page](https://linux.die.net/man/7/pipe)的I/O on pipes and FIFOs章节，介绍了pipe和FIFO的blocking 和nonblocking IO，以及asynchronous IO，从其中可以看到，pipe的asynchronous IO是基于signal的；

