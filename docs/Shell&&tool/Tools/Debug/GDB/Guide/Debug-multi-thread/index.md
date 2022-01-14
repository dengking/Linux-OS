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

## 给所有thread都下断点

stackoverflow [gdb how to break in new thread when debugging multi threaded daemon program on linux](https://stackoverflow.com/questions/55067510/gdb-how-to-break-in-new-thread-when-debugging-multi-threaded-daemon-program-on-l)

```sh
thread apply all b 'nertc_wrap.cc':4767
```



案例: 在multiple thread的情况下，调试一个`Swig::DirectorMethodException`

### TO READ

1、csdn [线程的查看以及利用gdb调试多线程](https://blog.csdn.net/zhangye3017/article/details/80382496)

2、drdobbs [Multithreaded Debugging Techniques](https://www.drdobbs.com/cpp/multithreaded-debugging-techniques/199200938?pgno=6)

3、fayewilliams [View A Backtrace For All Threads With GDB](https://www.fayewilliams.com/2015/05/05/view-a-backtrace-for-all-threads-with-gdb/)

