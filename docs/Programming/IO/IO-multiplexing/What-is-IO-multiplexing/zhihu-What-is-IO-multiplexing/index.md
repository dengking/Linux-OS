# zhihu [I/O多路复用技术（multiplexing）是什么？](https://www.zhihu.com/question/28594409)



## [A](https://www.zhihu.com/question/28594409/answer/52763082)

> 作者：知乎用户
>
> 链接：https://www.zhihu.com/question/28594409/answer/52763082
>
> 来源：知乎
>
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

题主是看redis相关书籍碰到了困惑，那就结合redis源码来回答题主这个问题。

redis源码地址：[antirez/redis · GitHub](https://link.zhihu.com/?target=https%3A//github.com/antirez/redis)。

关于I/O多路复用(又被称为“事件驱动”)，首先要理解的是，操作系统为你提供了一个功能，当你的某个socket可读或者可写的时候，它可以给你一个通知。这样当配合非阻塞的`socket`使用时，只有当系统通知我哪个**描述符**可读了，我才去执行`read`操作，可以保证每次`read`都能读到有效数据而不做纯返回`-1`和`EAGAIN`的无用功。写操作类似。操作系统的这个功能通过`select`/`poll`/`epoll`/`kqueue`之类的系统调用函数来使用，这些函数都可以同时监视多个**描述符**的读写就绪状况，这样，多个**描述符**的I/O操作都能在一个线程内并发交替地顺序完成，这就叫**I/O多路复用**，这里的“**复用**”指的是**复用同一个线程**。

> NOTE: 
>
> 1、使用many-one来进行理解
>
> 2、event notifier/notification

以select和tcp socket为例:

所谓**可读事件**，具体的说是指以下事件：

1 **socket内核接收缓冲区**中的可用字节数大于或等于其低水位`SO_RCVLOWAT`;

2 socket通信的对方关闭了连接，这个时候在缓冲区里有个文件结束符`EOF`，此时读操作将返回0；

3 监听socket的**backlog队列**有已经完成三次握手的连接请求，可以调用accept；

4 socket上有未处理的错误，此时可以用`getsockopt`来读取和清除该错误。

所谓**可写事件**，则是指：

1 socket的内核发送缓冲区的可用字节数大于或等于其低水位`SO_SNDLOWAIT`；

2 socket的写端被关闭，继续写会收到SIGPIPE信号；

3 非阻塞模式下，connect返回之后，发起连接成功或失败；

4  socket上有未处理的错误，此时可以用getsockopt来读取和清除该错误。

Linux环境下，Redis数据库服务器大部分时间以**单进程单线程模式**运行(执行持久化**BGSAVE**任务时会开启子进程)，网络部分属于**Reactor模式**，**同步非阻塞模型**，即**非阻塞的socket文件描述符号**加上监控这些描述符的**I/O多路复用机制**（在Linux下可以使用`select`/`poll`/`epoll`）。

服务器运行时主要关注两大类型事件：**文件事件**和**时间事件**。**文件事件**指的是**socket文件描述符**的读写就绪情况，**时间事件**分为**一次性定时器**和**周期性定时器**。相比**nginx**和**haproxy**内置的**高精度高性能定时器**，redis的定时器机制并不那么先进复杂，它只用了一个链表来管理时间事件，而且目前链表也没有对各个事件的到点时间进行排序，也就是说，每次都要遍历链表检查每个事件是否需要到点执行。个人猜想是因为redis目前并没有太多的定时事件需要管理，redis以数据库服务器角色运行时，定时任务回调函数只有位于`redis/src/redis.c`下的`serverCron`函数，所有的定时任务都在这个函数下执行，也就是说，链表里面其实目前就一个节点元素，所以目前也无需实现高性能定时器。

Redis网络事件驱动模型代码：`redis/src/`目录下的`ae.c`, `ae.h`, `ae_epoll.c`, `ae_evport.c`, `ae_select.c`, `ae_kqueue.c` , `ae_evport.c`。其中`ae.c/ae.h`:头文件里定义了描述**文件事件**和**事件时间**的结构体， 即`aeFileEvent`和`aeTimeEvent`；事件驱动状态结构体`aeEventLoop`, 这个结构体只有一个名为`eventloop`的全局变量在整个服务器进程中；事件就绪回调函数指针`aeFileProc`和`aeTimeProc`；以及操作事件驱动模型的各种API（`aeCreateEventLoop`以及之后全部的函数声明）。`ae_epoll.c`, `ae_select.c`, `ae_keque.c`和`ae_evport.c`封装了`select`/`epoll`/`kqueue`等系统调用，Linux下当然不支持`kqueue`和`evport`。至于究竟选择哪一种I/O多路复用技术，在`ae.c`里有预处理控制，也就是说，这些源文件只有一个能最后被编译。优先选择`epoll`或者`kqueue`(FREEBSD和Mac OSX可用)，其次是`select`。

> NOTE: 
> 1、static polymorphism

redis事件驱动整体流程：redis服务器main函数位于文件`redis/src/redis.c`, 事件驱动入口函数位于main函数的倒数第三行：

```c
aeMain(server.el); /* 实现代码位于ae.c */
```

这个函数调用`aeProcessEvent`进入事件循环，`aeProcessEvent`函数源码(同样位于`ae.c`源文件)：

```c
/* Process every pending time event, then every pending file event
 * (that may be registered by time event callbacks just processed).
 * Without special flags the function sleeps until some file event
 * fires, or when the next time event occurs (if any).
 *
 * If flags is 0, the function does nothing and returns.
 * if flags has AE_ALL_EVENTS set, all the kind of events are processed.
 * if flags has AE_FILE_EVENTS set, file events are processed.
 * if flags has AE_TIME_EVENTS set, time events are processed.
 * if flags has AE_DONT_WAIT set the function returns ASAP until all
 * the events that's possible to process without to wait are processed.
 *
 * The function returns the number of events processed. */
int aeProcessEvents(aeEventLoop *eventLoop, int flags)
{
    int processed = 0, numevents;

    /* Nothing to do? return ASAP */
    if (!(flags & AE_TIME_EVENTS) && !(flags & AE_FILE_EVENTS)) return 0;

    /* Note that we want call select() even if there are no
     * file events to process as long as we want to process time
     * events, in order to sleep until the next time event is ready
     * to fire. */
    if (eventLoop->maxfd != -1 ||
        ((flags & AE_TIME_EVENTS) && !(flags & AE_DONT_WAIT))) {
        int j;
        aeTimeEvent *shortest = NULL;
        struct timeval tv, *tvp;

        if (flags & AE_TIME_EVENTS && !(flags & AE_DONT_WAIT))
            shortest = aeSearchNearestTimer(eventLoop);
        if (shortest) {
            long now_sec, now_ms;

            /* Calculate the time missing for the nearest
             * timer to fire. */
            aeGetTime(&now_sec, &now_ms);
            tvp = &tv;
            tvp->tv_sec = shortest->when_sec - now_sec;
            if (shortest->when_ms < now_ms) {
                tvp->tv_usec = ((shortest->when_ms+1000) - now_ms)*1000;
                tvp->tv_sec --;
            } else {
                tvp->tv_usec = (shortest->when_ms - now_ms)*1000;
            }
            if (tvp->tv_sec < 0) tvp->tv_sec = 0;
            if (tvp->tv_usec < 0) tvp->tv_usec = 0;
        } else {
            /* If we have to check for events but need to return
             * ASAP because of AE_DONT_WAIT we need to set the timeout
             * to zero */
            if (flags & AE_DONT_WAIT) {
                tv.tv_sec = tv.tv_usec = 0;
                tvp = &tv;
            } else {
                /* Otherwise we can block */
                tvp = NULL; /* wait forever */
            }
        }

        numevents = aeApiPoll(eventLoop, tvp);
        for (j = 0; j < numevents; j++) {
            aeFileEvent *fe = &eventLoop->events[eventLoop->fired[j].fd];
            int mask = eventLoop->fired[j].mask;
            int fd = eventLoop->fired[j].fd;
            int rfired = 0;

	    /* note the fe->mask & mask & ... code: maybe an already processed
             * event removed an element that fired and we still didn't
             * processed, so we check if the event is still valid. */
            if (fe->mask & mask & AE_READABLE) {
                rfired = 1;
                fe->rfileProc(eventLoop,fd,fe->clientData,mask);
            }
            if (fe->mask & mask & AE_WRITABLE) {
                if (!rfired || fe->wfileProc != fe->rfileProc)
                    fe->wfileProc(eventLoop,fd,fe->clientData,mask);
            }
            processed++;
        }
    }
    /* Check time events */
    if (flags & AE_TIME_EVENTS)
        processed += processTimeEvents(eventLoop);

    return processed; /* return the number of processed file/time events */
}
```

读完后可以看出，`aeProcess`先根据全局变量`eventloop`中的距离当前最近时间事件来设置事件驱动器`aeApiPoll`函数(其实就是select, epoll_wait, kevent等函数的时间参数)的超时参数，`aeApiPoll`函数的实现位于每一个I/O多路复用器的封装代码中(即`ae_epoll.c`, `ae_evport.c`, `ae_select.c`, `ae_kqueue.c` , `ae_evport.c`)。`aeApiPoll`函数执行后，将就绪文件事件返回到`eventloop`的`fired`成员中，然后依次处理就绪的文件事件，执行其回调函数。最后，检查定时任务链表(`processTimeEvents`函数)， 执行时间任务。这就是redis服务器运行的大致主流程。



## [A](https://www.zhihu.com/question/28594409/answer/52835876)

> 作者：知乎用户
>
> 链接：https://www.zhihu.com/question/28594409/answer/52835876
>
> 来源：知乎
>
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

下面举一个例子，模拟一个tcp服务器处理30个客户socket。

假设你是一个老师，让30个学生解答一道题目，然后检查学生做的是否正确，你有下面几个选择：

\1. 第一种选择：

按顺序逐个检查，先检查A，然后是B，之后是C、D。。。这中间如果有一个学生卡主，全班都会被耽误。

这种模式就好比，你用循环挨个处理socket，根本不具有并发能力。

\2. 第二种选择：

你创建30个分身，每个分身检查一个学生的答案是否正确。 这种类似于为每一个用户创建一个进程或者线程处理连接。

\3. 第三种选择

你站在讲台上等，谁解答完谁举手。这时C、D举手，表示他们解答问题完毕，你下去依次检查C、D的答案，然后继续回到讲台上等。此时E、A又举手，然后去处理E和A。。。 

这种就是IO复用模型，Linux下的`select`、`poll`和`epoll`就是干这个的。将用户socket对应的`fd`注册进`epoll`，然后`epoll`帮你监听哪些socket上有消息到达，这样就避免了大量的无用操作。此时的socket应该采用非阻塞模式。

这样，整个过程只在调用`select`、`poll`、`epoll`这些调用的时候才会阻塞，收发客户消息是不会阻塞的，整个进程或者线程就被充分利用起来，这就是事件驱动，所谓的**reactor模式**。

