# [signal(7) ](http://man7.org/linux/man-pages/man7/signal.7.html)

## DESCRIPTION

Linux supports both POSIX reliable signals (hereinafter "standard signals") and POSIX real-time signals.

## Signal dispositions

> NOTE: "disposition"是"处置、处理"的意思

Each signal has a current ***disposition***, which determines how the process behaves when it is delivered the signal.

The entries in the "Action" column of the table below specify the **default disposition** for each signal, as follows:

|      |                                                              |
| ---- | ------------------------------------------------------------ |
| Term | Default action is to terminate the process.                  |
| Ign  | Default action is to ignore the signal                       |
| Core | Default action is to terminate the process and dump core (see [core(5)](http://man7.org/linux/man-pages/man5/core.5.html)) |
| Stop | Default action is to stop the process.                       |
| Cont | Default action is to continue the process if it is currently stopped |

> NOTE: term VS stop？被stop的process是可以再continue的；

A process can change the **disposition** of a signal using [sigaction(2)](http://man7.org/linux/man-pages/man2/sigaction.2.html) or [signal(2)](http://man7.org/linux/man-pages/man2/signal.2.html).  (The latter is less portable when establishing a **signal handler**; see [signal(2)](http://man7.org/linux/man-pages/man2/signal.2.html) for details.)  Using these system calls, a process can elect one of the following behaviors to occur on delivery of the signal: 

1、perform the default action; 

2、ignore the signal; 

3、catch the signal with a **signal handler**, a programmer-defined function that is automatically invoked when the signal is delivered.

By default, a **signal handler** is invoked on the normal **process stack**. It is possible to arrange that the **signal handler** uses an alternate stack; see [sigaltstack(2)](http://man7.org/linux/man-pages/man2/sigaltstack.2.html) for a discussion of how to do this and when it might be useful.

> NOTE: 
>
> [sigaltstack(2)](http://man7.org/linux/man-pages/man2/sigaltstack.2.html) custom stack

The signal disposition is a **per-process attribute**: in a multithreaded application, the **disposition** of a particular signal is the same for all threads.

> tag-thread share公共有signal disposition is a per-process attribute

A child created via [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html) inherits a copy of its parent's signal dispositions.  During an [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html), the **dispositions of handled signals** are reset to the default; the **dispositions of ignored signals** are left unchanged.

## Sending a signal

> NOTE: 
>
> 如何发送一个signal

The following system calls and library functions allow the caller to send a signal:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [raise(3)](http://man7.org/linux/man-pages/man3/raise.3.html) | Sends a signal to the calling thread.                        |
| [kill(2)](http://man7.org/linux/man-pages/man2/kill.2.html)  | Sends a signal to a specified process, to all members of a specified process group, or to all processes on the system. |
| [killpg(3)](http://man7.org/linux/man-pages/man3/killpg.3.html) | Sends a signal to all of the members of a specified process group. |
| [pthread_kill(3)](http://man7.org/linux/man-pages/man3/pthread_kill.3.html) | Sends a signal to a specified POSIX thread in the same process as the caller. |
| [tgkill(2)](http://man7.org/linux/man-pages/man2/tgkill.2.html) | Sends a signal to a specified thread within a specific process.  (This is the system call used to implement [pthread_kill(3)](http://man7.org/linux/man-pages/man3/pthread_kill.3.html).) |
| [sigqueue(3)](http://man7.org/linux/man-pages/man3/sigqueue.3.html) | Sends a real-time signal with accompanying data to a specified process. |
|                                                              |                                                              |

## Waiting for a signal to be caught
The following system calls suspend execution of the calling thread until a signal is caught (or an unhandled signal terminates the process):

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [pause(2)](http://man7.org/linux/man-pages/man2/pause.2.html) | Suspends execution until **any** signal is caught.           |
| [sigsuspend(2)](http://man7.org/linux/man-pages/man2/sigsuspend.2.html) | Temporarily changes the signal mask (see below) and suspends execution until one of the unmasked signals is caught. |

## Synchronously accepting a signal

> tag-Async to sync-blocking-等待-synchronously accepting a signal

Rather than **asynchronously** catching a signal via a **signal handler**, it is possible to synchronously accept the signal, that is, to block execution until the signal is delivered, at which point the kernel returns information about the signal to the caller.  There are two general ways to do this:

1、[sigwaitinfo(2)](http://man7.org/linux/man-pages/man2/sigwaitinfo.2.html), [sigtimedwait(2)](http://man7.org/linux/man-pages/man2/sigtimedwait.2.html), and [sigwait(3)](http://man7.org/linux/man-pages/man3/sigwait.3.html) suspend execution until one of the signals in a specified set is delivered.  Each of these calls returns information about the delivered signal.

2、[signalfd(2)](http://man7.org/linux/man-pages/man2/signalfd.2.html) returns a file descriptor that can be used to read information about signals that are delivered to the caller.  Each [read(2)](http://man7.org/linux/man-pages/man2/read.2.html) from this file descriptor blocks until one of the signals in the set specified in the [signalfd(2)](http://man7.org/linux/man-pages/man2/signalfd.2.html) call is delivered to the caller.  The buffer returned by  [read(2)](http://man7.org/linux/man-pages/man2/read.2.html) contains a structure describing the signal.

> tag-notify via fd通过文件来通知-Self-Pipe Trick-signalfd

## Signal mask and pending signals

A signal may be ***blocked***, which means that it will not be delivered until it is later unblocked.  Between the time when it is generated and when it is delivered a signal is said to be ***pending***.



Each thread in a process has an independent ***signal mask***, which indicates the set of signals that the thread is currently blocking. A thread can manipulate its signal mask using [pthread_sigmask(3)](http://man7.org/linux/man-pages/man3/pthread_sigmask.3.html).  In a traditional single-threaded application, [sigprocmask(2)](http://man7.org/linux/man-pages/man2/sigprocmask.2.html) can be used to manipulate the signal mask.



A child created via [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html) inherits a copy of its parent's signal mask; the signal mask is preserved across [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html).

> NOTE: 
>
> 这和signal disposition是不同的

A signal may be generated (and thus pending) for a process as a whole (e.g., when sent using [kill(2)](http://man7.org/linux/man-pages/man2/kill.2.html)) or for a specific thread (e.g., certain signals, such as `SIGSEGV` and `SIGFPE`, generated as a consequence of executing a specific machine-language instruction are thread directed, as are signals targeted at a specific thread using [pthread_kill(3)](http://man7.org/linux/man-pages/man3/pthread_kill.3.html)).  A process-directed signal may be delivered to any one of the threads that does not currently have the signal blocked. If more than one of the threads has the signal unblocked, then the kernel chooses an arbitrary thread to which to deliver the signal.

> NOTE: process-directed signal的一个典型代表就是[SIGALRM](http://man7.org/linux/man-pages/man7/signal.7.html)，根据APUE12.8节的介绍：闹钟定时器是进程资源，并且所有的线程共享相同的闹钟。所以，进程中的多个线程不可能互不干扰地使用闹钟定时器。参见redis中的`SIGALARM`。

A thread can obtain the set of signals that it currently has pending using [sigpending(2)](http://man7.org/linux/man-pages/man2/sigpending.2.html).  This set will consist of the union of the set of pending process-directed signals and the set of signals pending for the calling thread.



A child created via [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html) initially has an empty pending signal set; the pending signal set is preserved across an [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html).

## Execution of signal handlers

> NOTE: 
>
> 未读



## Interruption of system calls and library functions by signal handlers

> NOTE: 
>
> 在 "APUE 10.5 Interrupted System Calls" 中对此也有说明

If a signal handler is invoked while a system call or library function call is blocked, then either:

1、the call is automatically restarted after the signal handler returns; or

2、the call fails with the error `EINTR`.



Which of these two behaviors occurs depends on the interface and whether or not the **signal handler** was established using the `SA_RESTART` flag (see [sigaction(2)](http://man7.org/linux/man-pages/man2/sigaction.2.html)).  The details vary across UNIX systems; below, the details for Linux.



If a **blocked call** to one of the following interfaces is interrupted by a **signal handler**, then the call is automatically restarted after the **signal handler** returns if the `SA_RESTART` flag was used; otherwise  the call fails with the error `EINTR`:

1、[read(2)](http://man7.org/linux/man-pages/man2/read.2.html), [readv(2)](http://man7.org/linux/man-pages/man2/readv.2.html), [write(2)](http://man7.org/linux/man-pages/man2/write.2.html), [writev(2)](http://man7.org/linux/man-pages/man2/writev.2.html), and [ioctl(2)](http://man7.org/linux/man-pages/man2/writev.2.html) calls on "slow" devices.  

A "**slow**" device is one where the I/O call may block for an indefinite time(无限时间), for example, a **terminal**, **pipe**, or **socket**.  If an I/O call on a **slow device** has already transferred some data by the time it is interrupted by a **signal handler**, then the call will return a **success status** (normally, the number of bytes transferred).  Note that a (local) **disk** is not a slow device according to this definition; I/O operations on disk devices are not interrupted by signals.

> NOTE: 
>
> If an I/O call on a **slow device** has already transferred some data by the time it is interrupted by a **signal handler**, then the call will return a **success status** (normally, the number of bytes transferred).对于这种情况要如何处理呢？

2、[open(2)](http://man7.org/linux/man-pages/man2/open.2.html), if it can block (e.g., when opening a FIFO; see [fifo(7)](http://man7.org/linux/man-pages/man2/open.2.html)).

3、[wait(2)](http://man7.org/linux/man-pages/man2/open.2.html), [wait3(2)](http://man7.org/linux/man-pages/man2/wait3.2.html), [wait4(2)](http://man7.org/linux/man-pages/man2/wait4.2.html), [waitid(2)](http://man7.org/linux/man-pages/man2/waitid.2.html), and [waitpid(2)](http://man7.org/linux/man-pages/man2/waitpid.2.html).

4、Socket interfaces: [accept(2)](http://man7.org/linux/man-pages/man2/accept.2.html), [connect(2)](http://man7.org/linux/man-pages/man2/connect.2.html), [recv(2)](http://man7.org/linux/man-pages/man2/connect.2.html), [recvfrom(2)](http://man7.org/linux/man-pages/man2/recvfrom.2.html), [recvmmsg(2)](http://man7.org/linux/man-pages/man2/recvmmsg.2.html), [recvmsg(2)](http://man7.org/linux/man-pages/man2/recvmsg.2.html), [send(2)](http://man7.org/linux/man-pages/man2/send.2.html), [sendto(2)](http://man7.org/linux/man-pages/man2/sendto.2.html), and [sendmsg(2)](http://man7.org/linux/man-pages/man2/sendmsg.2.html), unless a timeout has been set on the socket (see below).

5、File locking interfaces: [flock(2)](http://man7.org/linux/man-pages/man2/flock.2.html) and the `F_SETLKW` and `F_OFD_SETLKW` operations of [fcntl(2)](http://man7.org/linux/man-pages/man2/fcntl.2.html)

6、POSIX message queue interfaces: [mq_receive(3)](http://man7.org/linux/man-pages/man3/mq_receive.3.html), [mq_timedreceive(3)](http://man7.org/linux/man-pages/man3/mq_timedreceive.3.html),[mq_send(3)](http://man7.org/linux/man-pages/man3/mq_timedreceive.3.html), and [mq_timedsend(3)](http://man7.org/linux/man-pages/man3/mq_timedreceive.3.html).

7、[futex(2)](http://man7.org/linux/man-pages/man3/mq_timedreceive.3.html) `FUTEX_WAIT` (since Linux 2.6.22; beforehand, always failed with `EINTR`).

8、[getrandom(2)](http://man7.org/linux/man-pages/man2/getrandom.2.html).

9、`pthread_mutex_lock`(3), `pthread_cond_wait`(3), and related APIs.

10、[futex(2)](http://man7.org/linux/man-pages/man2/futex.2.html) `FUTEX_WAIT_BITSET`.

11、POSIX semaphore interfaces: [sem_wait(3)](http://man7.org/linux/man-pages/man3/sem_wait.3.html) and [sem_timedwait(3)](http://man7.org/linux/man-pages/man3/sem_wait.3.html) (since Linux 2.6.22; beforehand, always failed with `EINTR`).

12、[read(2)](http://man7.org/linux/man-pages/man2/read.2.html) from an [inotify(7)](http://man7.org/linux/man-pages/man2/read.2.html) file descriptor (since Linux 3.8; beforehand, always failed with `EINTR`).

The following interfaces are never restarted after being interrupted by a **signal handler**, regardless of the use of `SA_RESTART`; they always fail with the error `EINTR` when interrupted by a signal handler:

* "Input" socket interfaces, when a timeout (`SO_RCVTIMEO`) has been set on the socket using [setsockopt(2)](http://man7.org/linux/man-pages/man2/setsockopt.2.html): [accept(2)](http://man7.org/linux/man-pages/man2/accept.2.html), [recv(2)](http://man7.org/linux/man-pages/man2/recv.2.html), [recvfrom(2)](http://man7.org/linux/man-pages/man2/recvfrom.2.html), [recvmmsg(2)](http://man7.org/linux/man-pages/man2/recvmmsg.2.html) (also with a non-NULL timeout argument),
and [recvmsg(2)](http://man7.org/linux/man-pages/man2/recvmsg.2.html).

* "Output" socket interfaces, when a timeout (`SO_RCVTIMEO`) has been set on the socket using [setsockopt(2)](http://man7.org/linux/man-pages/man2/setsockopt.2.html): [connect(2)](http://man7.org/linux/man-pages/man2/sendmsg.2.html), [send(2)](http://man7.org/linux/man-pages/man2/sendmsg.2.html), [sendto(2)](http://man7.org/linux/man-pages/man2/sendmsg.2.html), and [sendmsg(2)](http://man7.org/linux/man-pages/man2/sendmsg.2.html).

* Interfaces used to wait for signals: [pause(2)](http://man7.org/linux/man-pages/man2/pause.2.html), [sigsuspend(2)](http://man7.org/linux/man-pages/man2/sigsuspend.2.html), [sigtimedwait(2)](http://man7.org/linux/man-pages/man2/sigtimedwait.2.html), and [sigwaitinfo(2)](http://man7.org/linux/man-pages/man2/sigwaitinfo.2.html).

* File descriptor multiplexing interfaces: [epoll_wait(2)](http://man7.org/linux/man-pages/man2/epoll_wait.2.html), [epoll_pwait(2)](http://man7.org/linux/man-pages/man2/epoll_pwait.2.html), [poll(2)](http://man7.org/linux/man-pages/man2/epoll_pwait.2.html), [ppoll(2)](http://man7.org/linux/man-pages/man2/ppoll.2.html), [select(2)](http://man7.org/linux/man-pages/man2/ppoll.2.html), and [pselect(2)](http://man7.org/linux/man-pages/man2/pselect.2.html).

* System V IPC interfaces: [msgrcv(2)](http://man7.org/linux/man-pages/man2/msgrcv.2.html), [msgsnd(2)](http://man7.org/linux/man-pages/man2/msgsnd.2.html), [semop(2)](http://man7.org/linux/man-pages/man2/semop.2.html), and [semtimedop(2)](http://man7.org/linux/man-pages/man2/semtimedop.2.html).

* Sleep interfaces: [clock_nanosleep(2)](http://man7.org/linux/man-pages/man2/clock_nanosleep.2.html), [nanosleep(2)](http://man7.org/linux/man-pages/man2/nanosleep.2.html), and [usleep(3)](http://man7.org/linux/man-pages/man3/usleep.3.html).

* [io_getevents(2)](http://man7.org/linux/man-pages/man2/io_getevents.2.html).

The [sleep(3)](http://man7.org/linux/man-pages/man3/sleep.3.html) function is also never restarted if interrupted by a handler, but gives a success return: the number of seconds remaining to sleep.



## Interruption of system calls and library functions by stop signals

