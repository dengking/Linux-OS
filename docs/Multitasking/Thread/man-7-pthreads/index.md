# [PTHREADS(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)

> NOTE: 
>
> 其中对很多thread相关的内容都进行了描述

## NAME

pthreads - POSIX threads

## DESCRIPTION     

POSIX.1 specifies a set of interfaces (functions, header files) for threaded programming commonly known as POSIX threads, or Pthreads.  A single process can contain multiple threads, all of which are executing the same program.  These threads share the same global memory (data and heap segments), but each thread has its own **stack** (automatic variables).

## What threads share

> NOTE: 
>
> 一、这些都是process相关的
>
> 二、"Linux process implementation-light weight process group-thread group"，参见 `Book-Understanding-the-Linux-Kernel\Chapter-3-Processes\3.1-Processes-and-Lightweight-Processes-and-Threads` ，其中对此有非常好的说明

POSIX.1 also requires that threads share a range of other attributes (i.e., these attributes are process-wide rather than per-thread):

1、process ID

2、parent process ID

3、process group ID and session ID

4、controlling terminal

5、user and group IDs

6、open file descriptors

7、record locks (see [fcntl(2)](http://man7.org/linux/man-pages/man2/fcntl.2.html))

8、signal dispositions

8、file mode creation mask ([umask(2)](http://man7.org/linux/man-pages/man2/umask.2.html))

10、current directory ([chdir(2)](http://man7.org/linux/man-pages/man2/chdir.2.html)) and root directory ([chroot(2)](http://man7.org/linux/man-pages/man2/chroot.2.html))

11、interval timers ([setitimer(2)](http://man7.org/linux/man-pages/man2/setitimer.2.html)) and POSIX timers ([timer_create(2)](http://man7.org/linux/man-pages/man2/timer_create.2.html))

12nice value ([setpriority(2)](http://man7.org/linux/man-pages/man2/setpriority.2.html))

13、resource limits ([setrlimit(2)](http://man7.org/linux/man-pages/man2/setrlimit.2.html))

14、measurements of the consumption of CPU time ([times(2)](http://man7.org/linux/man-pages/man2/times.2.html)) and resources ([getrusage(2)](http://man7.org/linux/man-pages/man2/getrusage.2.html))

> NOTE: 
>
> 如何统计the consumption of CPU of a thread？参见[PTHREAD_GETCPUCLOCKID(3)](http://man7.org/linux/man-pages/man3/pthread_getcpuclockid.3.html)

## What thread private

> NOTE: 
>
> "tag-per-thread private"

As well as the stack, POSIX.1 specifies that various other attributes  are distinct for each thread, including:

1、thread ID (the `pthread_t` data type)

2、signal mask ([pthread_sigmask(3)](http://man7.org/linux/man-pages/man3/pthread_sigmask.3.html))

3、the [`errno`](http://man7.org/linux/man-pages/man3/errno.3.html) variable

> NOTE: 
>
> 在APUE中也对此有说明

4、alternate signal stack ([sigaltstack(2)](http://man7.org/linux/man-pages/man2/sigaltstack.2.html))

5、real-time scheduling policy and priority ([sched(7)](http://man7.org/linux/man-pages/man7/sched.7.html))

The following Linux-specific features are also per-thread:

6、capabilities (see [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html))

7、CPU affinity ([sched_setaffinity(2)](http://man7.org/linux/man-pages/man2/sched_setaffinity.2.html))

> NOTE: 
>
> thread是调度单位

## Pthreads function return values

Most pthreads functions return 0 on success, and an **error number** on failure.  Note that the pthreads functions do not set [errno](http://man7.org/linux/man-pages/man3/errno.3.html).  For each of the pthreads functions that can return an error, POSIX.1-2001 specifies that the function can never fail with the error `EINTR`.

> NOTE: 
>
> linux system call是会设置`errno`的。





## Thread IDs

Each of the threads in a process has a unique thread identifier (stored in the type pthread_t).  This identifier is returned to the caller of [pthread_create(3)](http://man7.org/linux/man-pages/man3/pthread_create.3.html), and a thread can obtain its own thread identifier using [pthread_self(3)](http://man7.org/linux/man-pages/man3/pthread_self.3.html).

Thread IDs are guaranteed to be unique only within a process.  (In all pthreads functions that accept a thread ID as an argument, that ID by definition refers to a thread in the same process as the caller.)

The system may reuse a thread ID after a terminated thread has been joined, or a detached thread has terminated.  POSIX says: "If an application attempts to use a thread ID whose lifetime has ended, the behavior is undefined."

## Thread-safe functions

> NOTE: 
>
> 非常详细的总结

## Async-cancel-safe functions

An **async-cancel-safe** function is one that can be safely called in an application where **asynchronous cancelability** is enabled (see [pthread_setcancelstate(3)](http://man7.org/linux/man-pages/man3/pthread_setcancelstate.3.html)).

Only the following functions are required to be async-cancel-safe by POSIX.1-2001 and POSIX.1-2008:



```c
pthread_cancel()
pthread_setcancelstate()
pthread_setcanceltype()
```



## Cancellation points

POSIX.1 specifies that certain functions must, and certain other functions may, be **cancellation points**.  If a thread is cancelable, its cancelability type is **deferred**, and a **cancellation request** is pending for the thread, then the thread is canceled when it calls a function that is a **cancellation point**.




An implementation may also mark other functions not specified in the standard as **cancellation points**.  In particular, an implementation is likely to mark any nonstandard function that may **block** as a **cancellation point**.  (This includes most functions that can touch files.)



## Linux implementations of POSIX threads

Over time, two threading implementations have been provided by the GNU C library on Linux:

### LinuxThreads

This is the original Pthreads implementation.  Since glibc 2.4, this implementation is no longer supported.

### NPTL (Native POSIX Threads Library)

This is the modern Pthreads implementation.  By comparison with LinuxThreads, NPTL provides closer conformance to the requirements of the POSIX.1 specification and better performance when creating large numbers of threads.  NPTL is available since glibc 2.3.2, and requires features that are present in the Linux 2.6 kernel.

Both of these are so-called 1:1 implementations, meaning that each **thread** maps to a **kernel scheduling entity**.  Both threading implementations employ the Linux [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) system call.  In NPTL, thread synchronization primitives (mutexes, thread joining, and so on) are implemented using the Linux [futex(2)](http://man7.org/linux/man-pages/man2/futex.2.html) system call.

