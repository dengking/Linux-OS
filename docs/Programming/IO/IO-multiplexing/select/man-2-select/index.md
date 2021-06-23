# [select(2)](https://www.man7.org/linux/man-pages/man2/select.2.html)

`select`, `pselect`, `FD_CLR`, `FD_ISSET`, `FD_SET`, `FD_ZERO` - synchronous I/O multiplexing

## SYNOPSIS         

```C++
#include <sys/select.h>

int select(int nfds, fd_set *restrict readfds,
           fd_set *restrict writefds, fd_set *restrict exceptfds,
           struct timeval *restrict timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

int pselect(int nfds, fd_set *restrict readfds,
            fd_set *restrict writefds, fd_set *restrict exceptfds,
            const struct timespec *restrict timeout,
            const sigset_t *restrict sigmask);
```

> NOTE: 
>
> 一、通过原文的"File descriptor sets"、"NOTES"、"BUGS"可以总结出select设计上的缺陷:
>
> 1、`fd_set` 的大小是固定的，这就导致了`select`需要逐个遍历来找到用户设置的需要监控的file descriptor，显然这浪费了空间、时间
>
> 2、`fd_set` 的大小是固定的，注定到了`select`无法解决C10K问题，因为当用户量非常大的时候，线性遍历是非常耗时的
>
> 3、如"File descriptor sets"段中所描绘的:
>
> "Thus, if using select() within a loop, the sets must be reinitialized before each call.  The implementation of the `fd_set` arguments as value-result arguments is a design error that is avoided in poll(2) and epoll(7)."
>
> 这就需要用户进行频繁的copy(在Redis中，演示了实现方式)，显然这就浪费了时间、导致了编程的麻烦
>
> 



## File descriptor sets

The principal arguments of select() are three "sets" of file descriptors (declared with the type `fd_set`), which allow the caller to wait for three classes of events on the specified set of file descriptors.  Each of the `fd_set` arguments may be specified as NULL if no file descriptors are to be watched for the corresponding class of events.

Note well: Upon return, each of the file descriptor sets is modified in place to indicate which file descriptors are currently "ready".  Thus, if using select() within a loop, the sets must be reinitialized before each call.  The implementation of the `fd_set` arguments as value-result arguments is a design error that is avoided in poll(2) and epoll(7).

## NOTES

An `fd_set` is a fixed size buffer.  Executing `FD_CLR()` or `FD_SET()` with a value of `fd` that is negative or is equal to or larger than `FD_SETSIZE` will result in undefined behavior.  Moreover, POSIX requires `fd` to be a valid file descriptor.

> NOTE: 
>
> 结合后面的"BUGS" 段，就可知[select(2)](https://www.man7.org/linux/man-pages/man2/select.2.html)的设计是多么地不合理

### The self-pipe trick

## BUGS         

POSIX allows an implementation to define an upper limit, advertised via the constant `FD_SETSIZE`, on the range of file descriptors that can be specified in a file descriptor set.  The Linux kernel imposes no fixed limit, but the glibc implementation makes `fd_set` a fixed-size type, with `FD_SETSIZE` defined as 1024, and the `FD_*()` macros operating according to that limit.  To monitor file descriptors greater than 1023, use poll(2) or epoll(7) instead.

