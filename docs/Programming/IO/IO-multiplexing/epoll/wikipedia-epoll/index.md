# wikipedia [epoll](https://en.wikipedia.org/wiki/Epoll) 

**epoll** is a [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel) [system call](https://en.wikipedia.org/wiki/System_call) for a scalable I/O event notification mechanism, first introduced in version 2.5.44 of the [Linux kernel mainline](https://en.wikipedia.org/wiki/Linux_kernel_mainline).[[1\]](https://en.wikipedia.org/wiki/Epoll#cite_note-1) Its function is to monitor multiple file descriptors to see whether I/O is possible on any of them. It is meant to replace the older [POSIX](https://en.wikipedia.org/wiki/POSIX) [`select(2)`](https://en.wikipedia.org/wiki/Select_(Unix)) and `poll(2)` [system calls](https://en.wikipedia.org/wiki/System_call), to achieve better performance in more demanding applications, where the number of watched [file descriptors](https://en.wikipedia.org/wiki/File_descriptor) is large (unlike the older system calls, which operate in [*O*](https://en.wikipedia.org/wiki/Big_O_notation)(*n*) time, `epoll` operates in *O*(1) time[[2\]](https://en.wikipedia.org/wiki/Epoll#cite_note-2)).

`epoll` is similar to [FreeBSD](https://en.wikipedia.org/wiki/FreeBSD)'s [`kqueue`](https://en.wikipedia.org/wiki/Kqueue), in that it consists of a set of [user-space](https://en.wikipedia.org/wiki/User-space) functions, each taking a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) argument denoting the configurable kernel object, against which they cooperatively operate. `epoll` used [red-black tree](https://en.wikipedia.org/wiki/Red-black_tree) (RB-tree) data structure to keep track of all file descriptors that are currently being monitored.[[3\]](https://en.wikipedia.org/wiki/Epoll#cite_note-3)



## API

```C
int epoll_create1(int flags);
```

Creates an `epoll` object and returns its file descriptor. The `flags` parameter allows `epoll` behavior to be modified. It has only one valid value, `EPOLL_CLOEXEC`. `epoll_create()` is an older variant of `epoll_create1()` and is deprecated as of Linux kernel version 2.6.27 and `glibc` version 2.9.[[4\]](https://en.wikipedia.org/wiki/Epoll#cite_note-4)

```C
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

Controls (configures) which file descriptors are watched by this object, and for which events. `op` can be `ADD`, `MODIFY` or `DELETE`.

```C
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

Waits for any of the events registered for with `epoll_ctl`, until at least one occurs or the timeout elapses. Returns the occurred events in `events`, up to `maxevents` at once.



## Triggering modes

`epoll` provides both [edge-triggered](https://en.wikipedia.org/wiki/Interrupt#Edge-triggered) and [level-triggered](https://en.wikipedia.org/wiki/Interrupt#Level-triggered) modes. In edge-triggered mode, a call to `epoll_wait` will return only when a new event is enqueued with the `epoll` object, while in level-triggered mode, `epoll_wait` will return as long as the condition holds.

For instance, if a [pipe](https://en.wikipedia.org/wiki/Anonymous_pipe) registered with `epoll` has received data, a call to `epoll_wait` will return, signaling the presence of data to be read. Suppose, the reader only consumed part of data from the buffer. In **level-triggered mode**, further calls to `epoll_wait` will return immediately, as long as the pipe's buffer contains data to be read. In edge-triggered mode, however, `epoll_wait` will return only once new data is written to the pipe.

> NOTE: 其实从下面的这章图片就可以理解edge-triggered和level-triggered之间的异与同：

[https://www.google.com.hk/search?q=edge+triggered+vs+level+triggered&safe=active&tbm=isch&source=iu&ictx=1&fir=ALSkVf2uzpmW1M%253A%252CAjbjCXoIRJTeoM%252C_&vet=1&usg=AI4_-kROE4ffoEn655hD260z1U4q4p5Qog&sa=X&ved=2ahUKEwjTgYLl3aHjAhXkX3wKHXKyAyoQ9QEwAHoECAQQAw#imgrc=ALSkVf2uzpmW1M:&vet=1](https://www.google.com.hk/search?q=edge+triggered+vs+level+triggered&safe=active&tbm=isch&source=iu&ictx=1&fir=ALSkVf2uzpmW1M%3A%2CAjbjCXoIRJTeoM%2C_&vet=1&usg=AI4_-kROE4ffoEn655hD260z1U4q4p5Qog&sa=X&ved=2ahUKEwjTgYLl3aHjAhXkX3wKHXKyAyoQ9QEwAHoECAQQAw#imgrc=ALSkVf2uzpmW1M:&vet=1)

## Criticism

[Bryan Cantrill](https://en.wikipedia.org/wiki/Bryan_Cantrill) pointed out that `epoll` had mistakes that could have been avoided, had it learned from its predecessors（前辈）: [input/output completion ports](https://en.wikipedia.org/wiki/Input/output_completion_port), [event ports](https://en.wikipedia.org/w/index.php?title=Event_port&action=edit&redlink=1)(Solaris) and [kqueue](https://en.wikipedia.org/wiki/Kqueue).[[5\]](https://en.wikipedia.org/wiki/Epoll#cite_note-5) However, a large part of his criticism was addressed by the `epoll`'s `EPOLLONESHOT` option[[6\]](https://en.wikipedia.org/wiki/Epoll#cite_note-6), which was added in version 2.6.2 of the Linux kernel mainline, released in February 2004.