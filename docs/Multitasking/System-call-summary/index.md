# 关于本章

multitasking是Linux OS的核心特性，本章将对它与它相关的programming进行描述。



## Thread functions and the process functions

在APUE 11.5 Thread Termination中总结了“similarities between the thread functions and the process functions”

> By now, you should begin to see similarities between the thread functions and the process functions. Figure 11.6 summarizes the similar functions.

| Process primitive | Thread primitive       | Description                                                 |
| ----------------- | ---------------------- | ----------------------------------------------------------- |
| `fork`            | `pthread_create`       | create a new flow of control                                |
| `exit`            | `pthread_exit`         | exit from an existing flow of control                       |
| `waitpid`         | `pthread_join`         | get exit status from flow of control                        |
| `atexit`          | `pthread_cleanup_push` | register function to be called at exit from flow of control |
| `getpid`          | `pthread_self`         | get ID for flow of control                                  |
| `abort`           | `pthread_cancel`       | request abnormal termination of flow of control             |

> Figure 11.6 Comparison of process and thread primitives



## Fork-join model

在工程[parallel-computing](https://dengking.github.io/machine-learning/)的`Model\Fork–join-model.md`中总结了Fork–join model，可以看到上述thread functions和process functions显然是遵循这种model的：

下面是草稿

fork api：

| entity  | api                                                          |
| ------- | ------------------------------------------------------------ |
| process | [`fork`](https://www.man7.org/linux/man-pages/man2/fork.2.html) |
| thread  | [`pthread_create`](https://man7.org/linux/man-pages/man3/pthread_create.3.html) |

join api

| entity  | api                                                          |
| ------- | ------------------------------------------------------------ |
| process | [WAIT(2)](http://man7.org/linux/man-pages/man2/waitpid.2.html)、[WAIT4(2)](http://man7.org/linux/man-pages/man2/wait4.2.html) |
| thread  | [PTHREAD_JOIN(3)](http://man7.org/linux/man-pages/man3/pthread_join.3.html)、[pthread_barrier_wait(3)](https://linux.die.net/man/3/pthread_barrier_wait) |



## `clone`

之前已经谈论了Linux OS中process、thread的实现，我们已经知道: 它们都依赖于`clone` system call，这是Linux OS中，非常重要的一个system call，我们将它单独放到一个章节中进行描述。