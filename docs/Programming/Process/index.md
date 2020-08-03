# 前言

与process相关的主题。



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