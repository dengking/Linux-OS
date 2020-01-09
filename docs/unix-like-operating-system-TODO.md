[TOC]

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