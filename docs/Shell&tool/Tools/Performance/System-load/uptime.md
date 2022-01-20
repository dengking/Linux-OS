# `uptime`

是在阅读linuxjournal [Hack and / - Linux Troubleshooting, Part I: High Load](https://www.linuxjournal.com/article/10688)时，发现的这个命令。

## [uptime(1) - Linux man page](https://man7.org/linux/man-pages/man1/uptime.1.html)

**System load averages** is the average number of processes that are either in a **runnable** or **uninterruptable state**.  

A process in a **runnable state** is either using the CPU or waiting to use the CPU.  

A process in **uninterruptable state** is waiting for some I/O access, eg waiting for disk.  

The averages are taken over the three time intervals.  

Load averages are not **normalized** for the number of CPUs in a system, so a load average of 1 means a single CPU system is
loaded all the time while on a 4 CPU system it means it was idle 75% of the time.

> NOTE: 理解load average是关键所在，而理解load average的关键在于理解上面这段话中的**normalized**，它的意思是：uptime输出中的load average指的是process个数，它并没有除以 CPU 个数，这就是 **normalized** 的含义所在。关于此，在 [Hack and / - Linux Troubleshooting, Part I: High Load](https://www.linuxjournal.com/article/10688) 中也对它进行了详细介绍，作者将它作为查看系统 *load average* 的第一命令。



