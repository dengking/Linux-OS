

# Implementation(System call/API)

1、下面是 [libevent – an event notification library](https://libevent.org/) 总结的当前各种OS 中，IO multiplexing的implementation: 

> *[/dev/poll](http://download.oracle.com/docs/cd/E19253-01/816-5177/6mbbc4g9n/index.html)*, *[kqueue(2)](http://www.freebsd.org/cgi/man.cgi?query=kqueue&apropos=0&sektion=0&format=html)*, *[event ports](http://developers.sun.com/solaris/articles/event_completion.html)*, [POSIX *select(2)*](http://manpages.debian.net/cgi-bin/man.cgi?query=select), [Windows *select()*](http://msdn.microsoft.com/en-us/library/ms740141(v=vs.85).aspx), [*poll(2)*](http://manpages.debian.net/cgi-bin/man.cgi?query=poll), and *[epoll(4)](http://www.xmailserver.org/linux-patches/epoll.txt)*.

2、下面是 [libuv](https://libuv.org/) Design overview[¶](http://docs.libuv.org/en/v1.x/design.html#design-overview) # The I/O loop[¶](http://docs.libuv.org/en/v1.x/design.html#the-i-o-loop) 总结的: 

> The event loop follows the rather usual single threaded asynchronous I/O approach: all (network) I/O is performed on non-blocking sockets which are polled using the best mechanism available on the given platform: 
>
> epoll on Linux, 
>
> kqueue on OSX and other BSDs, 
>
> event ports on SunOS and 
>
> IOCP on Windows. 



执行implementation的共同点:

## 支持设置timeout(system call with timeout)

1、这一点非常重要，它是实现"Multiplex on file and time event"的基础

2、在APUE 14.4.1 select and pselect Functions 中有对timeout参数的说明，可以作为参考

> Wait the specified number of seconds and microseconds. 
>
> Return is made when one of the specified descriptors is ready or when the timeout value expires. 
>
> If the timeout expires before any of the descriptors is ready, the return value is 0.(If the system doesn’t provide microsecond resolution, the `tvptr−>tv_usec` value is rounded up to the nearest supported value.) 
>
> As with the first condition, this wait can also be interrupted by a caught signal.



> Any (or all) of the middle three arguments to `select` (the pointers to the descriptor sets) can be null pointers if we’re not interested in that condition. 
>
> If all three pointers are NULL, then we have a higher-precision timer than is provided by `sleep`. (Recall
> from Section 10.19 that sleep waits for an integral number of seconds. 
>
> With `select`, we can wait for intervals less than one second; the actual resolution depends on the system’s clock.) Exercise 14.5 shows such a function.



## 支持同时管理多个file descriptor



## Concurrent programming

广泛用于Concurrent programming，能够用于解决C10K问题。

参见工程`parallel-computing`的`The-C10K-problem`章节。