# Classification of system call

总结system call的分类法。



## 从blocking的角度来对system call进行分类

在APUE的10.5 Interrupted System Calls中介绍了slow system call，这提示有必要对linux的system call进行一下总结；

### APUE 10.5 Interrupted System Calls

A characteristic of earlier UNIX systems was that if a process caught a signal while the process was blocked in a ‘‘**slow**’’ system call, the system call was interrupted. The system call returned an error and `errno` was set to `EINTR`. This was done under the assumption that since a signal occurred and the process caught it, there is a good chance that something has happened that should wake up the blocked system call.



To support this feature, the **system calls** are divided into two categories: the ‘‘slow’’ system calls and all the others. The slow system calls are those that can **block forever**. Included in this category are

• Reads that can block the caller forever if data isn’t present with certain file types (pipes, terminal devices, and network devices)
• Writes that can block the caller forever if the data can’t be accepted immediately by these same file types
• Opens on certain file types that block the caller until some condition occurs (such as a terminal device open waiting until an attached modem answers the phone)
• The `pause` function (which by definition puts the calling process to sleep until a signal is caught) and the `wait` function
• Certain `ioctl` operations
• Some of the interprocess communication functions (Chapter 15)

The notable exception to these slow system calls is anything related to disk I/O. Although a `read` or a `write` of a disk file can block the caller temporarily (while the disk driver queues the request and then the request is executed), unless a hardware error occurs, the I/O operation always returns and unblocks the caller quickly.

***SUMMARY*** : 显然，上述对system call的分类方法是根据这个system call是否可能会将process **block forever**的，短暂的block是不算slow的，这个短暂的block就是a `read` or a `write` of a disk file。并且slow system call是和signal密切相关的；





上述描述的是在Unix system中的情况，那么linux中的情况是怎样的呢？参见[man SIGNAL(7)](http://man7.org/linux/man-pages/man7/signal.7.html)，其中对linux中的情况进行了非常详细的说明；



### [man SIGNAL(7)](http://man7.org/linux/man-pages/man7/signal.7.html)





### [Difference between slow system calls and fast system calls](https://unix.stackexchange.com/questions/14293/difference-between-slow-system-calls-and-fast-system-calls)





### 通过Nonblocking I/O来转换slow system call



#### 前言

从上面的介绍来看，其实所谓的slow  system call是跟它所操作的device密切相关的，而Unix OS的everything in Unix is file的philosophy，将很多device都抽象成了file，我们通过对这些file的file descriptor进行操作来实现对device的操作，因此很多操作都是类似于IO；默认情况下，当我们对slow device执行system call的时候，就非常可能出现slow system call的情况；Unix OS是非常灵活的，它是有提供system call来允许用户改变这种默认行为的：这就是Unix中的nonblocking I/O，通过在指定的file descriptor上设置nonblocking标志，来告诉kernel不要block对该file descriptor进行操作的thread；



### APUE 14.2 Nonblocking I/O



在这一节对这个主题的内容进行了深入的介绍；









## 带有max blocking time的system call非常重要，有必要进行总结：
- `pthread_mutex_timedlock`
- `pthread_rwlock_timedrdlock`
- `pthread_cond_timedwait`
- `select`
- `poll`
- [`epoll_wait`](http://man7.org/linux/man-pages/man2/epoll_wait.2.html)


## 和阻塞相关问题
- 如何取消阻塞的系统调用（可以使用信号）
- `sleep`是否是阻塞，如果不是，它和阻塞有什么异同？
- 

## 非阻塞I与异步IO

非阻塞IO参见APUE 14.2

通过设置标志来实现非阻塞

异步IO参见14.5

## socket是如何实现的IO with timeout？





## Polling and non-polling

### Polling

维基百科[Polling (computer science)](https://en.wikipedia.org/wiki/Polling_(computer_science))

#### Busy-waiting

维基百科[Busy waiting](https://en.wikipedia.org/wiki/Busy_waiting)

https://practice.geeksforgeeks.org/problems/what-is-busy-wait

https://dev.to/rinsama77/process-synchronization-with-busy-waiting-4gho

https://stackoverflow.com/questions/1107593/what-are-trade-offs-for-busy-wait-vs-sleep

https://www.auto.tuwien.ac.at/~blieb/papers/busywait.pdf

#### Examples

维基百科[Spinlock](https://en.wikipedia.org/wiki/Spinlock)

polling sleep

### Non-polling

blocking、waiting、sleep



### TO READ

[what's different between the Blocked and Busy Waiting?](https://stackoverflow.com/questions/26541119/whats-different-between-the-blocked-and-busy-waiting)