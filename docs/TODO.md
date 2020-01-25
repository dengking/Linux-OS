# 20190817

今天在阅读《`Understanding.The.Linux.kernel.3rd.Edition`》的6.2.1.2. The jiffies variable章节的时候，其中的一段话引起了我对原子性的思考：

> You might wonder why  `jiffies` has not been directly declared as a 64-bit  `unsigned long long` integer on the 80 x 86 architecture. The answer is that accesses to 64-bit variables in 32-bit architectures cannot be done **atomically**. Therefore, every read operation on the whole 64 bits requires some synchronization technique to ensure that the counter is not updated while the two 32-bit half-counters are read; as a consequence, every 64-bit read operation is significantly slower than a 32-bit read operation.

在32位的机器中，一次能够读取的数据的长度为32位，所以读取超过32的数据就需要多条指令，显然，这就不是原子性的了；

联想到今天在阅读《计算机组成原理》的1.2.4 计算机的性能指标，我所做的笔记如下：

> 指处理机**运算器**中一次能够完成二进制数运算的**位数**，如32位，64位；
>
> **SUMMARY** : 这应该就是我们平时所说的32位，或64位；一次能够完成二进制数的运算，其实蕴含中，CPU一次CPU一次性能读取数据的二进制位数。参见[Redis内存管理的基石zmallc.c源码解读（一）](https://blog.csdn.net/guodongxiaren/article/details/44747719) ； [Data alignment: Straighten up and fly right](https://developer.ibm.com/articles/pa-dalign/)
>
> **SUMMARY** : 上述一次的含义是什么？是指一个指令周期？



现在联系到原子性，显然，上述这段话中的**一次**的含义是非常深刻的：它蕴含着原子性的保证；



其实这个问题，我在之前就已经遇到过的，记得当时阅读的文章是：[Atomic vs. Non-Atomic Operations](https://preshing.com/20130618/atomic-vs-non-atomic-operations/)，这篇文章我已经收录了；

综上所述，其实我的问题可以归纳为：why read 64 bit data in 32 bit is not atomic

Google了一下，发现了一些有价值的内容：

- [How to Customize Serialization in Java Using the Externalizable Interface](https://dzone.com/articles/how-to-customize-serialization-in-java-using-the-e)
- [Are 64 bit operations atomic for a 32 bit app on 64 bit Windows](https://stackoverflow.com/questions/27533611/are-64-bit-operations-atomic-for-a-32-bit-app-on-64-bit-windows)

# 20190829

## `epoll_wait` 、 `epoll_pwait`和信号之间的关系

http://man7.org/linux/man-pages/man2/epoll_wait.2.html





## epoll and nonblocking

使用epoll的时候，是否一定要使用nonblocking IO？

# 20190905

## passing file descriptor between process

https://docs.python.org/3.5/library/multiprocessing.html

在python的multiprocessing文档中看到了它提出的这个问题：

> forkserver
>
> When the program starts and selects the forkserver start method, a server process is started. From then on, whenever a new process is needed, the parent process connects to the server and requests that it fork a new process. The fork server process is single threaded so it is safe for it to use os.fork(). No unnecessary resources are inherited.
>
> Available on Unix platforms which support passing file descriptors over Unix pipes.


http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch17lev1sec4.html


https://openforums.wordpress.com/2016/08/07/open-file-descriptor-passing-over-unix-domain-sockets/


## semaphore tracker process

https://docs.python.org/3.5/library/multiprocessing.html


## Synchronization between processes

https://stackoverflow.com/questions/248911/how-do-i-synchronize-two-processes

https://en.wikipedia.org/wiki/Semaphore_%28programming%29


http://sce2.umkc.edu/csee/cotterr/cs431_sp13/CS431_Linux_Process_Sync_12_bw.ppt



# 20190906



https://stackoverflow.com/questions/11129212/tcp-can-two-different-sockets-share-a-port

https://lwn.net/Articles/542629/

https://stackoverflow.com/questions/1694144/can-two-applications-listen-to-the-same-port/25033226



# 20190909

## TCP backlog

https://stackoverflow.com/questions/36594400/what-is-backlog-in-tcp-connections

http://www.linuxjournal.com/files/linuxjournal.com/linuxjournal/articles/023/2333/2333s2.html


https://martin.kleppmann.com/2015/05/11/please-stop-calling-databases-cp-or-ap.html

# 20190913



## atomic & race condition & lock & consistent model 专题

今天在阅读redis source code的时候，总结了redis中socket file descriptor都是non blocking的，然后我就查阅APUE中关于文件描述符标志，文件标志的内容；又重新看了一遍APUE 3.3节中关于TOCTTOU的描述，以及APUE 3.11 原子操作的描述，我才意识到原理linux的system call也是能够保证atomic的（从底层实现来看，是因为big kernel lock ）；原来我仅仅认知到一个instruction是atomic，其实这种认知是比较局限的；联想到我之前总结过关于atomic的内容，如下：

everything中使用如下命令查找所有atomic相关的内容：

```
nowholeword:c:\users\dengkai17334\appdata\local\ynote\data\ content:atomic 
```

现在是有必要整理一番了。



## linux system call atomic



# network



## [**data integrity**](https://en.wikipedia.org/wiki/Data_integrity) in network

在[2.1. Two Types of Internet Sockets](https://beej.us/guide/bgnet/html/multi/theory.html#twotypes)中提及TCP能够保证[**data integrity**](https://en.wikipedia.org/wiki/Data_integrity)，可见[**data integrity**](https://en.wikipedia.org/wiki/Data_integrity)并不仅仅局限于一方面；

## What's the difference between 127.0.0.1 and 0.0.0.0?

[What's the difference between 127.0.0.1 and 0.0.0.0?](https://superuser.com/questions/949428/whats-the-difference-between-127-0-0-1-and-0-0-0-0)

## interface address

在很多地方都见到了这个词：

- [getaddrinfo(3) - Linux man page](https://linux.die.net/man/3/getaddrinfo)
- 

它到底是什么含义

## stream of bytes and bitstream

[Bitstream](https://en.wikipedia.org/wiki/Bitstream)

已经阅读

## Maximum segment lifetime

https://en.wikipedia.org/wiki/Maximum_segment_lifetime

# 20190909

epoll中的file descripor是否一定要设置为non blocking

`SO_RCVLOWAT` and `SO_SNDLOWAT`的值都是1，那么如何确定message boundary？

# shell



- `getconf`
- `echo "2^12" | bc`
- [How to check if port is in use on Linux or Unix](https://www.cyberciti.biz/faq/unix-linux-check-if-port-is-in-use-command/)
- https://unix.stackexchange.com/a/185767
- how to get all threads of a process
- 

## process

https://www.cyberciti.biz/faq/show-all-running-processes-in-linux/

https://unix.stackexchange.com/questions/2107/how-to-suspend-and-resume-processes



## How to print out a variable in makefile

https://stackoverflow.com/questions/16467718/how-to-print-out-a-variable-in-makefile





# Process control block

<https://www.tldp.org/LDP/lki/lki-2.html>

上面这篇文章主要讲述的是linux kernel的实现





# [How to Find Out Which Windows Process is Using a File](https://www.techsupportalert.com/content/how-find-out-which-windows-process-using-file.htm)

user the software:Process Explorer
# [How find out which process is using a file in Linux?](https://stackoverflow.com/questions/24554614/how-find-out-which-process-is-using-a-file-in-linux)

```
fuser file_name
```

# what will happen if a process exceed its resource limits

记得在redis in action这本书中有提及过类似的问题；


# C POSIX library
https://en.wikipedia.org/wiki/C_POSIX_library

http://pubs.opengroup.org/onlinepubs/9699919799/idx/head.html


# C standard library
https://en.wikipedia.org/wiki/C_standard_library




# process id

APUE 4.4  Set-User-ID and Set-Group-ID


https://en.wikipedia.org/wiki/User_identifier

# Time of check to time of use

https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use

# User identifier

https://en.wikipedia.org/wiki/User_identifier





# Secure Programming HOWTO

https://dwheeler.com/secure-programs/Secure-Programs-HOWTO/index.html





# thread-local

thread-local和reentry之间的关系

# hole in file 
hole对文件大小的影响；上周在查看https://liftoff.github.io/pyminifier/文档的时候，其中有minifying功能，是和hole in file有关的；

同时binary mode来保存文件也能够降低文件大小；




# linux memory

memory usage 

memory available


# virtual process space

https://www.tutorialspoint.com/where-are-static-variables-stored-in-c-cplusplus


https://cs61.seas.harvard.edu/wiki/2016/Kernel2X 这篇文章非常好

https://www.cs.utexas.edu/~lorenzo/corsi/cs372/06F/hw/3sol.html

https://cs.stackexchange.com/questions/56825/how-to-calculate-virtual-address-space-from-page-size-virtual-address-size-and
# process environment

7.12不同语言的environment是否不同





# file IO：python VS linux

Python与Linux类似，与文件相关的操作都是从open函数开始的



# Fragmentation (computing)

<https://en.wikipedia.org/wiki/Fragmentation_(computing)>





# page table size

<https://www.cs.cornell.edu/courses/cs4410/2015su/lectures/lec14-pagetables.html>
http://www.cs.cornell.edu/courses/cs4410/2016su/slides/lecture11.pdf

http://www.cs.cornell.edu/courses/cs4410/2016su/schedule.html



# Data segment

<https://en.wikipedia.org/wiki/Data_segment>

# ENOENT


[Why does ENOENT mean “No such file or directory”?](https://stackoverflow.com/questions/19902828/why-does-enoent-mean-no-such-file-or-directory)


# EACCES


# cron

https://en.wikipedia.org/wiki/Cron


https://www.adminschoice.com/crontab-quick-reference

# 在shell中删除掉进程使用的文件

今天在测试的时候发现了一个有趣的问题：进程运行中，这个进程会不断地向其日志文件中写入日志；然后我在shell中将这个日志文件给删除了，发现进程并没有发现它的日志文件被删了，也没有出现创建这个日志文件，程序也没有停止下来；

磁盘空间满后，也会导致process无法写入到文件中；但是当释放一部分空间后，发现process仍然不会写入，就像是放弃了一样；

# Segmentation fault

hiredis不是线程安全的，今天在多线程环境下测试出它会导致process core dump，dump的原因是`Program terminated with signal 11, Segmentation fault.`

https://kb.iu.edu/d/aqsj

https://en.wikipedia.org/wiki/Segmentation_fault


### thread unsafe and core dump


# how to test

如果是支持网络，需要测试多个client连接；

需要进行压力测试

需要进行并发测试

# process and its thread

[Is there a way to see details of all the threads that a process has in Linux?](https://unix.stackexchange.com/questions/892/is-there-a-way-to-see-details-of-all-the-threads-that-a-process-has-in-linux)

google:how to get all threads of a process

https://www.unix.com/aix/154772-how-list-all-threads-running-process.html

http://ask.xmodulo.com/view-threads-process-linux.html


# how OS know process use a illegal memory location

https://en.wikipedia.org/wiki/Memory_protection

https://stackoverflow.com/questions/41172563/how-os-catches-illegal-memory-references-at-paging-scheme

https://unix.stackexchange.com/questions/511963/how-linux-finds-out-about-illegal-memory-access-error


https://www.kernel.org/


https://www.kernel.org/doc/gorman/html/understand/index.html


https://www.kernel.org/doc/gorman/

https://www.kernel.org/doc/

# dev file 
https://unix.stackexchange.com/questions/93531/what-is-stored-in-dev-pts-files-and-can-we-open-them




# Unix memory usage

https://utcc.utoronto.ca/~cks/space/blog/linux/LinuxMemoryStats

https://utcc.utoronto.ca/~cks/space/blog/unix/UnderstandingRSS

https://stackoverflow.com/questions/131303/how-to-measure-actual-memory-usage-of-an-application-or-process

https://unix.stackexchange.com/questions/554/how-to-monitor-cpu-memory-usage-of-a-single-process

# How can I kill a process by name instead of PID?

https://stackoverflow.com/questions/160924/how-can-i-kill-a-process-by-name-instead-of-pid

http://osxdaily.com/2017/01/12/kill-process-by-name-command-line/

# APUE的《Unix-interruption-and-atom》还没有wanch

其中主要讨论了Atomicity

# Consistency models
在parallel computing中的Consistency models还没有完成

https://en.wikipedia.org/wiki/Category:Consistency_models

# epoll

https://en.wikipedia.org/wiki/Epoll


# youdao Unix-abort





# init of linux

## init进程

ch8.2中有对init进程的一个介绍



ch9.2介绍到，init会读取文件`/etc/ttys`

how to know what init system linux use

<https://unix.stackexchange.com/questions/18209/detect-init-system-using-the-shell>

<https://fedoramagazine.org/what-is-an-init-system/>

<https://en.wikipedia.org/wiki/Init>



<https://en.wikipedia.org/wiki/Systemd>

# Convert between Unix and Windows text files

https://kb.iu.edu/d/acux

https://stackoverflow.com/questions/16239551/eol-conversion-in-notepad





# Memory management algorithms

https://en.wikipedia.org/wiki/Category:Memory_management_algorithms


[Slab allocation](https://en.wikipedia.org/wiki/Slab_allocation)



# interrupt in Unix



 [interrupt vector table](https://en.wikipedia.org/wiki/Interrupt_vector_table)

<http://www.cis.upenn.edu/~lee/03cse380/lectures/ln2-process-v4.pdf>

在[Context switch](https://en.wikipedia.org/wiki/Context_switch)中也对interrupt进行了介绍


## signal 

signal也是一种interrupt，故将它放在interrupt之下

### Google unix signals and threads

https://stackoverflow.com/questions/2575106/posix-threads-and-signals

https://en.wikipedia.org/wiki/Signal_(IPC)


# Scheduling (computing)

https://en.wikipedia.org/wiki/Scheduling_(computing)


# thread join and detach


# wait

https://linux.die.net/man/2/waitpid