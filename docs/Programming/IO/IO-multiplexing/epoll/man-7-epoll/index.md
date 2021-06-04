# [epoll(7) — Linux manual page](http://man7.org/linux/man-pages/man7/epoll.7.html) 



`epoll` - I/O event notification facility

> NOTE: 
>
> 显然`epoll`的本质是**event notifier**



## SYNOPSIS         

```C++
#include <sys/epoll.h>
```

## DESCRIPTION         

The **epoll** API performs a similar task to [**poll**(2)](https://linux.die.net/man/2/poll): monitoring multiple file descriptors to see if I/O is possible on any of them. 

The **epoll** API can be used either as an edge-triggered or a level-triggered interface and scales well to large numbers of watched file descriptors.

## `epoll` instance

The central concept of the `epoll` API is the `epoll` instance, an **in-kernel data structure** which, from a user-space perspective, can be considered as a container for two lists:

1、The ***interest list*** (sometimes also called the ***`epoll` set***): the set of file descriptors that the process has registered an interest in monitoring.

2、The ***ready list***: the set of file descriptors that are "ready" for I/O.  The ready list is a subset of (or, more precisely, a set of references to) the file descriptors in the interest list that is dynamically populated by the kernel as a result of I/O activity on those file descriptors.

## System calls

 The following system calls are provided to create and manage an **epoll** instance:

1、[**epoll_create**(2)](https://linux.die.net/man/2/epoll_create) creates an **epoll** instance and returns a file descriptor referring to that instance. (The more recent [**epoll_create1**(2)](https://linux.die.net/man/2/epoll_create1) extends the functionality of **epoll_create**(2).)

2、Interest in particular file descriptors is then registered via [**epoll_ctl**(2)](https://linux.die.net/man/2/epoll_ctl). The set of **file descriptors** currently registered on an **epoll** instance is sometimes called an ***epoll* set**.

3、[**epoll_wait**(2)](https://linux.die.net/man/2/epoll_wait) waits for I/O events, **blocking** the calling thread if no events are currently available.

> NOTE: 
>
> 如果有event已经available了，则立即返回这个event对应的`fd`。



##  Level-triggered and edge-triggered

The `epoll` event distribution interface is able to behave both as edge-triggered (ET) and as level-triggered (LT).  The difference between the two mechanisms can be described as follows.  Suppose that this scenario happens:

1、The file descriptor that represents the read side of a pipe (`rfd`) is registered on the `epoll` instance.

2、A pipe writer writes 2 kB of data on the write side of the pipe.

3、A call to `epoll_wait(2)` is done that will return `rfd` as a **ready file descriptor**.

4、The pipe reader reads 1 kB of data from `rfd`.

> NOTE: 
>
> 写入了 2 kB，但是仅仅读出了 1 kB，显然，没有将所有写入的data读出。
>
> 

5、A call to `epoll_wait(2)` is done.

### `EPOLLET` (edge-triggered)

If the `rfd` file descriptor has been added to the **epoll interface** using the `EPOLLET` (edge-triggered) flag, the call to `epoll_wait(2)` done in step 5 will probably hang(挂起，其实就是阻塞) despite the available data still present in the **file input buffer**; meanwhile the remote peer might be expecting a response based on the data it already sent.  The reason for this is that edge-triggered mode delivers events only when changes occur on the monitored file descriptor.  So, in step 5 the caller might end up waiting for some data that is already present inside the input buffer.  In the above example, an event on `rfd` will be generated because of the write done in 2 and the event is consumed in 3.  Since the read operation done in 4 does not consume the whole buffer data, the call to `epoll_wait(2)` done in step 5 might block indefinitely.

> 如果已使用EPOLLET（边缘触发）标志将rfd文件描述符添加到epoll接口，则尽管文件输入缓冲区中仍存在可用数据，但在步骤5中完成的对epoll_wait（2）的调用可能会挂起; 同时，远程对等体可能期望基于其已发送的数据进行响应。 原因是边缘触发模式仅在受监视文件描述符发生更改时才传递事件。 因此，在步骤5中，调用者可能最终等待输入缓冲区内已存在的某些数据。 在上面的示例中，将生成rfd上的事件，因为写入在2中完成并且事件在3中消耗。由于在4中完成的读取操作不消耗整个缓冲区数据，因此对epoll_wait（2）的调用已完成 在步骤5中可能会无限期地阻止。

An application that employs the `EPOLLET` flag should use nonblocking file descriptors to avoid having a blocking read or write starve a task that is handling multiple file descriptors.  The suggested way to use `epoll` as an edge-triggered (`EPOLLET`) interface is as follows:

i   with nonblocking file descriptors; and

ii  by waiting for an event only after read(2) or write(2) return [`EAGAIN`](https://stackoverflow.com/questions/4058368/what-does-eagain-mean).

> NOTE : 要理解上面这段话的含义，就需要搞清楚blocking IO和nonblocking IO，以及它们和`epoll`之间的关系，参考下面的两篇文章：
>
> 1、[Why having to use non-blocking fd in a edge triggered epoll function?](https://stackoverflow.com/questions/14643249/why-having-to-use-non-blocking-fd-in-a-edge-triggered-epoll-function)
>
> 2、[Blocking I/O, Nonblocking I/O, And Epoll](https://eklitzke.org/blocking-io-nonblocking-io-and-epoll)

### level-triggered 

By contrast, when used as a **level-triggered** interface (the default, when `EPOLLET` is not specified), `epoll` is simply a faster [poll(2)](https://man7.org/linux/man-pages/man2/poll.2.html), and can be used wherever the latter is used since it shares the same semantics.



### `EPOLLONESHOT` 

Since even with edge-triggered `epoll`, multiple events can be generated upon receipt of multiple chunks of data, the caller has the option to specify the `EPOLLONESHOT` flag, to tell `epoll` to disable the associated file descriptor after the receipt of an event with `epoll_wait(2)`.  When the `EPOLLONESHOT` flag is specified, it is the caller's responsibility to rearm the file descriptor using `epoll_ctl(2)` with `EPOLL_CTL_MOD`.

### Avoiding "thundering herd" wake-ups 

If multiple threads (or processes, if child processes have inherited the `epoll` file descriptor across `fork(2)`) are blocked in `epoll_wait(2)` waiting on the same the same `epoll` file descriptor and a file descriptor in the interest list that is marked for edge-triggered (`EPOLLET`) notification becomes ready, just one of the threads (or processes) is awoken from `epoll_wait(2)`.  This provides a useful optimization for avoiding "thundering herd" wake-ups in some scenarios.

> NOTE: 
>
> "thundering herd" 是 "惊群效应"，参见: 
>
> `Parallel-computing\docs\Concurrent-computing\Classic-problem\Thundering-herd-problem`

## Interaction with autosleep

If the system is in autosleep mode via `/sys/power/autosleep` and an event happens which wakes the device from sleep, the device driver will keep the device awake only until that event is queued.  To keep
the device awake until the event has been processed, it is necessary to use the `epoll_ctl(2)` `EPOLLWAKEUP` flag.

When the `EPOLLWAKEUP` flag is set in the events field for a `struct epoll_event`, the system will be kept awake from the moment the event is queued, through the `epoll_wait(2)` call which returns the event
until the subsequent `epoll_wait(2)` call.  If the event should keep the system awake beyond that time, then a separate `wake_lock` should be taken before the second `epoll_wait(2)` call.



## `/proc` interfaces

The following interfaces can be used to limit the amount of kernel memory consumed by `epoll`:

`/proc/sys/fs/epoll/max_user_watches` (since Linux 2.6.28)

This specifies a limit on the total number of file descriptors that a user can register across all `epoll` instances on the system.  The limit is per **real user ID**.  Each registered file descriptor costs roughly 90 bytes on a 32-bit kernel, and roughly 160 bytes on a 64-bit kernel.  Currently, the default value for `max_user_watches` is 1/25 (4%) of the available low memory, divided by the registration cost in bytes.



## Example for suggested usage

While the usage of `epoll` when employed as a **level-triggered** interface does have the same semantics as poll(2), the edge-triggered usage requires more clarification to avoid stalls(抛锚) in the application event loop.  In this example, listener is **a nonblocking socket** on which `listen(2)` has been called.  The function `do_use_fd()` uses the new ready file descriptor until `EAGAIN` is returned by either [`read(2)`](http://man7.org/linux/man-pages/man2/read.2.html) or [`write(2)`](http://man7.org/linux/man-pages/man2/write.2.html).  An **event-driven state machine** application should, after having received `EAGAIN`, record its current state so that at the next call to `do_use_fd()` it will continue to `read(2)` or `write(2)` from where it stopped before.

```c
#define MAX_EVENTS 10
struct epoll_event ev, events[MAX_EVENTS];
int listen_sock, conn_sock, nfds, epollfd;

/* Code to set up listening socket, 'listen_sock',
(socket(), bind(), listen()) omitted */

epollfd = epoll_create1(0);
if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
}

ev.events = EPOLLIN;
ev.data.fd = listen_sock;
if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, & ev) == -1) {
    perror("epoll_ctl: listen_sock");
    exit(EXIT_FAILURE);
}

for (;;) {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }

    for (n = 0; n < nfds; ++n) {
        if (events[n].data.fd == listen_sock) {
            conn_sock = accept(listen_sock,
                (struct sockaddr * ) & addr, & addrlen);
            if (conn_sock == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            setnonblocking(conn_sock);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;
            if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &
                    ev) == -1) {
                perror("epoll_ctl: conn_sock");
                exit(EXIT_FAILURE);
            }
        } else {
            do_use_fd(events[n].data.fd);
        }
    }
}
```


When used as an edge-triggered interface, for performance reasons, it is possible to add the file descriptor inside the `epoll` interface (`EPOLL_CTL_ADD`) once by specifying (`EPOLLIN|EPOLLOUT`).  This allows you to avoid continuously switching between `EPOLLIN` and `EPOLLOUT` calling `epoll_ctl(2)` with `EPOLL_CTL_MOD`.



## Questions and answers





## Possible pitfalls and ways to avoid them o Starvation (edge-triggered)

