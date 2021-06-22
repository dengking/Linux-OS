# Show thread start-rtn

本节标题的含义是：如何查看一个thread的线程执行函数，



## stackoverflow [How to list the threads along with it's appropriate function in GDB.?](https://stackoverflow.com/questions/25161364/how-to-list-the-threads-along-with-its-appropriate-function-in-gdb) 

[A](https://stackoverflow.com/a/25162479) :

> You can use `thread apply all bt` command. It will print backtraces of all your threads. You will find thread function name inside each of these backtrace near the end and before `clone` system call.

[A](https://stackoverflow.com/a/25162677) :

> I press Ctrl+L to clear the screen buffer
>
> ```
> set height 0
> thread apply all bt
> ```
>
> This will dump backtrace for all the threads but won't pause (because we set the window height to 0) if the list is long. I then copy/paste the output to a text editor for examination.

下面是我们的实践:

```bash
(gdb) info  threads 
  Id   Target Id         Frame 
  5    Thread 0x7f3a780ee700 (LWP 142466) "main" 0x00007f3a78d73cf2 in pthread_cond_timedwait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
  4    Thread 0x7f3a778ed700 (LWP 142467) "main" 0x00007f3a790431ad in nanosleep () from /lib64/libc.so.6
  3    Thread 0x7f3a770ec700 (LWP 142468) "main" 0x00007f3a7907c923 in epoll_wait () from /lib64/libc.so.6
  2    Thread 0x7f3a768eb700 (LWP 142469) "main" 0x00007f3a7907c923 in epoll_wait () from /lib64/libc.so.6
* 1    Thread 0x7f3a7a334780 (LWP 142465) "main" 0x00007f3a790431ad in nanosleep () from /lib64/libc.so.6
(gdb) thread apply all bt

Thread 5 (Thread 0x7f3a780ee700 (LWP 142466)):
#0  0x00007f3a78d73cf2 in pthread_cond_timedwait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
#1  0x00007f3a787495e2 in __gthread_cond_timedwait (__abs_timeout=0x7f3a780edd80, __mutex=<optimized out>, __cond=0x212a388)
    at /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/gthr-default.h:871
#2  __wait_until_impl<std::chrono::duration<long, std::ratio<1l, 1000000000l> > > (__atime=..., __lock=..., this=0x212a388)
    at /usr/include/c++/4.8.2/condition_variable:160
#3  wait_until<std::chrono::duration<long, std::ratio<1l, 1000000000l> > > (__atime=..., __lock=..., this=0x212a388)
    at /usr/include/c++/4.8.2/condition_variable:100
#4  wait_until<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> >, CEvent::Wait(int64_t)::__lambda0> (
    __p=..., __atime=..., __lock=..., this=0x212a388) at /usr/include/c++/4.8.2/condition_variable:123
#5  wait_for<long int, std::ratio<1l, 1000l>, CEvent::Wait(int64_t)::__lambda0> (__p=..., __rtime=..., __lock=..., this=0x212a388)
    at /usr/include/c++/4.8.2/condition_variable:139
#6  CEvent::Wait (this=0x212a360, dwMillsSecond=dwMillsSecond@entry=100) at ../../plugins/logproxy/event.cpp:44
#7  0x00007f3a787453da in Pop (iTimeOut=100, this=0x212a290) at ../../plugins/logproxy/log_queue.h:92
#8  CLogProxyImpl::Run (this=<optimized out>) at ../../plugins/logproxy/log_proxy_impl.cpp:367
#9  0x00007f3a799142b0 in ?? () from /lib64/libstdc++.so.6
#10 0x00007f3a78d6fe25 in start_thread () from /lib64/libpthread.so.0
#11 0x00007f3a7907c34d in clone () from /lib64/libc.so.6

Thread 4 (Thread 0x7f3a778ed700 (LWP 142467)):
#0  0x00007f3a790431ad in nanosleep () from /lib64/libc.so.6
#1  0x00007f3a79073ec4 in usleep () from /lib64/libc.so.6
#2  0x00007f3a78740470 in sleep_for<long, std::ratio<1l, 1000l> > (__rtime=...) at /usr/include/c++/4.8.2/thread:281
#3  CCheckConnThread::Run (this=0x2161040) at ../../utilities/tcp/tcp_factory.cpp:608
#4  0x00007f3a799142b0 in ?? () from /lib64/libstdc++.so.6
#5  0x00007f3a78d6fe25 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f3a7907c34d in clone () from /lib64/libc.so.6

Thread 3 (Thread 0x7f3a770ec700 (LWP 142468)):
#0  0x00007f3a7907c923 in epoll_wait () from /lib64/libc.so.6
#1  0x00007f3a78740b4a in CTcpSendThread::Run (this=0x2160f48) at ../../utilities/tcp/tcp_factory.cpp:228
#2  0x00007f3a799142b0 in ?? () from /lib64/libstdc++.so.6
#3  0x00007f3a78d6fe25 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f3a7907c34d in clone () from /lib64/libc.so.6
---Type <return> to continue, or q <return> to quit---

Thread 2 (Thread 0x7f3a768eb700 (LWP 142469)):
#0  0x00007f3a7907c923 in epoll_wait () from /lib64/libc.so.6
#1  0x00007f3a7874094a in CTcpRecvThread::Run (this=0x2160fc8) at ../../utilities/tcp/tcp_factory.cpp:261
#2  0x00007f3a799142b0 in ?? () from /lib64/libstdc++.so.6
#3  0x00007f3a78d6fe25 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f3a7907c34d in clone () from /lib64/libc.so.6

Thread 1 (Thread 0x7f3a7a334780 (LWP 142465)):
#0  0x00007f3a790431ad in nanosleep () from /lib64/libc.so.6
#1  0x00007f3a79073ec4 in usleep () from /lib64/libc.so.6
#2  0x0000000000406189 in sleep_for<long, std::ratio<1l, 1000l> > (__rtime=...) at /usr/include/c++/4.8.2/thread:281
#3  CMyApp::Run (this=this@entry=0x7ffcb3fa4b50) at ../HA-test-1/app.h:251
#4  0x00000000004032ac in main () at main.cpp:43

```

从上面的输出可以看出：

- Thread 1是main thread，它不是由clone system call创建的，其他thread都是由[clone system call](https://man7.org/linux/man-pages/man2/clone.2.html)创建的