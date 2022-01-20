# 关于本章

本章描述在debug multithreaded application时，会遇到的commonissue，以及解决方法。

正如在 totalview [Debugging Common Issues in Multithreaded Applications](https://totalview.io/sites/totalview/files/pdfs/white-paper-totalview-debugging-multithreaded-apps.pdf)中所言：

> This paper describes several challenges that are commonly encountered when debugging multithreaded applications in order to compare the open source GNU GDB debugger



## `4-Running-Programs-Under-gdb`

其中有描述"debug multi thread"相关的内容

## 获得所有thread的堆栈

### stackoverflow [How do I get the backtrace for all the threads in GDB?](https://stackoverflow.com/questions/18391808/how-do-i-get-the-backtrace-for-all-the-threads-in-gdb)

```shell
thread apply all bt
```



## 如何找到目标线程

1、thread apply all bt的输出重定向到文件中

2、根据**线程执行函数**从多线程中找到你感兴趣的线程，然后切换到这个线程的stack中；

如果使用C++`std::thread`创建，则"thread apply all bt"的输出中一般是能够带出的

## 如何判断目标线程是否还在运行

还是根据线程执行函数来定位，如果"thread apply all bt"中找不到，则说明这个thread已经退出了。



## 如何判断thread的状态

wait/block: 一般都是`condition_wait`

那running呢？



## gdb breakpoint and thread

分两种情况:

1、默认情况下，break语句只给current thread下breakpoint

2、thread-specific breakpoint，参见 "5.5.4 Thread-Specific Breakpoints"



### 给当前所有living thread都下断点

stackoverflow [gdb how to break in new thread when debugging multi threaded daemon program on linux](https://stackoverflow.com/questions/55067510/gdb-how-to-break-in-new-thread-when-debugging-multi-threaded-daemon-program-on-l)

```sh
thread apply all b 'nertc_wrap.cc':4767
```

案例: 在multiple thread的情况下，调试一个`Swig::DirectorMethodException`

### 给新创建的thread下断点

需要注意的是: 新创建的thread并不会使用之前通过 `thread apply all b` 下的断点，关于此在stackoverflow [gdb how to break in new thread when debugging multi threaded daemon program on linux](https://stackoverflow.com/questions/55067510/gdb-how-to-break-in-new-thread-when-debugging-multi-threaded-daemon-program-on-l) 中进行了讨论，那如何为新创建的thread下断点呢？

一、我的思路是: 在`pthread_create`的时候break，然后下断点，关于此，参见:

stackoverflow [gdb breakpoint on pthread_create](https://stackoverflow.com/questions/1440643/gdb-breakpoint-on-pthread-create)

二、在stackoverflow  [gdb how to break in new thread when debugging multi threaded daemon program on linux](https://stackoverflow.com/questions/55067510/gdb-how-to-break-in-new-thread-when-debugging-multi-threaded-daemon-program-on-l) # [A](https://stackoverflow.com/a/55097959/10173843)



### break when new thread creation

参见: 

1、stackoverflow [gdb breakpoint on pthread_create](https://stackoverflow.com/questions/1440643/gdb-breakpoint-on-pthread-create)

[A](https://stackoverflow.com/a/1444836/10173843)

> NOTE: 
>
> `catch syscall clone` 应该是最简单的

## multiple-thread debugging and scheduler

参见:

1、stackoverflow [How does gdb multi-thread debugging coordinate with Linux thread scheduling?](https://stackoverflow.com/questions/50055181/how-does-gdb-multi-thread-debugging-coordinate-with-linux-thread-scheduling)

2、5.5.1 All-Stop Mode

## TO READ

1、csdn [线程的查看以及利用gdb调试多线程](https://blog.csdn.net/zhangye3017/article/details/80382496)

2、drdobbs [Multithreaded Debugging Techniques](https://www.drdobbs.com/cpp/multithreaded-debugging-techniques/199200938?pgno=6)

3、fayewilliams [View A Backtrace For All Threads With GDB](https://www.fayewilliams.com/2015/05/05/view-a-backtrace-for-all-threads-with-gdb/)

