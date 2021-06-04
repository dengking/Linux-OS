# [epoll_ctl(2) — Linux manual page](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)

`epoll_ctl` - control interface for an epoll file descriptor



## SYNOPSIS

```c
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

## DESCRIPTION

This system call is used to add, modify, or remove entries in the **interest list** of the epoll(7) instance referred to by the file descriptor `epfd`.  It requests that the operation `op` be performed for the target file descriptor, `fd`.

## `op` argument 

Valid values for the `op` argument are:

### `EPOLL_CTL_ADD`

Add `fd` to the **interest list** and associate the **settings** specified in `event` with the internal file linked to `fd`.

### `EPOLL_CTL_MOD`

Change the settings associated with `fd` in the interest list to the new settings specified in `event`.

### `EPOLL_CTL_DEL`

Remove (deregister) the target file descriptor `fd` from the **interest list**.  The `event` argument is ignored and can be NULL  (but see BUGS below).
      

The `event` argument describes the object linked to the file descriptor `fd`.  The `struct epoll_event` is defined as:
```c
typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;      /* Epoll events */
    epoll_data_t data;        /* User data variable */
};
```

## `events` member 

The `events` member is a **bit mask** composed by ORing together zero or more of the following available event types:

### `EPOLLIN`

The associated file is available for [`read(2)`](http://man7.org/linux/man-pages/man2/read.2.html) operations.



### `EPOLLOUT`

The associated file is available for [write(2)](http://man7.org/linux/man-pages/man2/write.2.html) operations.



> NOTE: 
>
> 一、`EPOLLIN` 即 可读，`EPOLLOUT`即可写
>
> 那到底何时 `EPOLLIN`、何时 `EPOLLOUT`？在下面文章中进行了介绍:
>
> 1、[socket(7) Linux Programmer's Manual](http://man7.org/linux/man-pages/man7/socket.7.html)  # `SO_RCVLOWAT` and `SO_SNDLOWAT`
>
> 2、[I/O多路复用技术（multiplexing）是什么？](I/O多路复用技术（multiplexing）是什么？ ) # [A](https://www.zhihu.com/question/28594409/answer/52763082) : 
>
> > 以`select`和tcp socket为例，
> >
> > 所谓可读事件，具体的说是指以下事件：
> >
> > 1 socket内核接收缓冲区中的可用字节数大于或等于其低水位`SO_RCVLOWAT`;
> >
> > 所谓可写事件，则是指：
> >
> > 1 socket的内核发送缓冲区的可用字节数大于或等于其低水位`SO_SNDLOWAIT`；
>
> 

### `EPOLLRDHUP` (since Linux 2.6.17)

**Stream socket** peer closed connection, or shut down writing half of connection.  (This flag is especially useful for writing simple code to detect **peer shutdown** when using **Edge Triggered** monitoring.)

> NOTE: 
>
> 参见 csdn [EPOLLRDHUP vs EPOLLHUP](https://blog.csdn.net/zhouguoqionghai/article/details/94591475)

### `EPOLLPRI`

There is an exceptional condition on the file descriptor.  See the discussion of `POLLPRI` in poll(2).

### `EPOLLERR`

Error condition happened on the associated file descriptor. This event is also reported for the **write end** of a pipe when the **read end** has been closed.  `epoll_wait(2)` will always report for this event; it is not necessary to set it in events.

### `EPOLLHUP`

Hang up happened on the associated file descriptor. `epoll_wait(2)` will always wait for this event; it is not necessary to set it in events.

> Note that when reading from a channel such as a **pipe** or a **stream socket**, this event merely indicates that the peer closed its end of the channel.  Subsequent reads from the channel will return 0 (end of file) only after all outstanding data in the channel has been consumed.

> NOTE: 
>
> 参见TLPI中关于此的解释；

### `EPOLLET`

Sets the Edge Triggered behavior for the associated **file descriptor**.  The default behavior for epoll is **Level Triggered**.  See epoll(7) for more detailed information about Edge and Level Triggered event distribution architectures.

### `EPOLLONESHOT` (since Linux 2.6.2)	

Sets the **one-shot behavior** for the associated file descriptor. This means that after an event is pulled out with `epoll_wait(2)` the associated file descriptor is internally disabled and no other events will be reported by the epoll interface.  The user must call `epoll_ctl()` with `EPOLL_CTL_MOD` to rearm the file descriptor with a new event mask.

### `EPOLLWAKEUP` (since Linux 3.5)

If `EPOLLONESHOT` and `EPOLLET` are clear and the process has the `CAP_BLOCK_SUSPEND` capability, ensure that the system does not enter "suspend" or "hibernate"(冬眠、蛰伏) while this event is pending or being processed.  The event is considered as being "processed" from the time when it is returned by a call to `epoll_wait(2)` until the next call to `epoll_wait(2)` on the same epoll(7) file descriptor, the closure of that file descriptor, the removal of the event file descriptor with `EPOLL_CTL_DEL`, or the clearing of `EPOLLWAKEUP` for the event file descriptor with `EPOLL_CTL_MOD`.  See also BUGS.

### `EPOLLEXCLUSIVE` (since Linux 4.5)

Sets an exclusive wakeup mode for the epoll file descriptor that is being attached to the target file descriptor, `fd`. When a wakeup event occurs and multiple epoll file descriptors are attached to the same target file using `EPOLLEXCLUSIVE`, one or more of the epoll file descriptors will receive an event with epoll_wait(2).  The default in this scenario (when `EPOLLEXCLUSIVE` is not set) is for all epoll file descriptors to receive an event.  `EPOLLEXCLUSIVE` is thus useful for avoiding thundering herd problems in certain scenarios.

If the same file descriptor is in multiple epoll instances, some with the `EPOLLEXCLUSIVE` flag, and others without, then events will be provided to all epoll instances that did not specify `EPOLLEXCLUSIVE`, and at least one of the epoll instances that did specify `EPOLLEXCLUSIVE`.

The following values may be specified in conjunction with `EPOLLEXCLUSIVE`: `EPOLLIN`, `EPOLLOUT`, `EPOLLWAKEUP`, and `EPOLLET`.  `EPOLLHUP` and `EPOLLERR` can also be specified, but this is not required: as usual, these events are always reported if they occur, regardless of whether they are specified in events.
Attempts to specify other values in events yield the error EINVAL.

`EPOLLEXCLUSIVE` may be used only in an `EPOLL_CTL_ADD` operation; attempts to employ it with `EPOLL_CTL_MOD` yield an error.  If `EPOLLEXCLUSIVE` has been set using `epoll_ctl()`, then a subsequent `EPOLL_CTL_MOD` on the same `epfd`, `fd` pair yields an error. A call to `epoll_ctl()` that specifies `EPOLLEXCLUSIVE` in events and specifies the target file descriptor `fd` as an epoll instance will likewise fail.  The error in all of these cases is `EINVAL`.
