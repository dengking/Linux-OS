# System Load

如何查看system load，即“系统负载”，这是本文讨论的问题。

## linuxjournal [Hack and / - Linux Troubleshooting, Part I: High Load](https://www.linuxjournal.com/article/10688)

Although it's true that there are about as many different reasons for **downtime** as there are Linux text editors, and just as many approaches to troubleshooting, over the years, I've found I perform the same sorts of steps to isolate a problem. Because my column is generally aimed more at **tips and tricks** and less on **philosophy and design**, I'm not going to talk much about overall approaches to problem solving. Instead, in this series I describe some general classes of problems you might find on a Linux system, and then I discuss how to use common tools, most of which probably are already on your system, to isolate and resolve each class of problem.

> NOTE: 作者对知识的划分：
>
> - **tips and tricks**
> - **philosophy and design**
>
> 是非常值得工程师借鉴的，在文章Thought中，引用了这个观点。

For this first column, I start with one of the most common problems you will run into on a Linux system. No, it's not getting printing to work. I'm talking about a sluggish（迟钝的） server that might have **high load**. Before I explain how to diagnose and fix high load though, let's take a step back and discuss **what load means** on a Linux machine and how to know when it's **high**.

### Uptime and Load

When administrators mention high load, generally they are talking about the *load average*. When I diagnose why a server is slow, the **first** command I run when I log in to the system is `uptime`:

```shell
$ uptime
 18:30:35 up 365 days, 5:29, 2 users, load average: 1.37, 10.15, 8.10
```

> NOTE: 关于`uptime`，参见 `Shell-and-tools\Tools\uptime.md` 



### How High Is High?

> NOTE: 多高才能算是高？

After you understand what **load average** means, the next logical question is “What load average is good and what is bad?” The answer to that is “It depends.” You see, a lot of different things can cause load to be high, each of which affects performance differently. One server might have a load of 50 and still be pretty responsive, while another server might have a load of 10 and take forever to log in to.

What really matters when you troubleshoot a system with high load is *why* the load is high. When you start to diagnose **high load**, you find that most **load** seems to fall into three categories: 

| Category                            |      |      |
| ----------------------------------- | ---- | ---- |
| CPU-bound load                      |      |      |
| load caused by out of memory issues |      |      |
| I/O-bound load                      |      |      |

I explain each of these categories in detail below and how to use tools like `top` and `iostat` to isolate the root cause.

### `top`

If the first tool I use when I log in to a sluggish system is `uptime`, the second tool I use is `top`. The great thing about `top` is that it's available for all major Linux systems, and it provides a lot of useful information in a single screen. For this column, I stick to how to interpret its output to diagnose high load.

To use `top`, simply type `top` on the command line. By default, `top` will run in interactive mode and update its output every few seconds. Listing 1 shows sample `top` output from a terminal.

**Listing 1. Sample top Output**

```SHELL
top - 14:08:25 up 38 days, 8:02, 1 user, load average: 1.70, 1.77, 1.68
Tasks: 107 total,   3 running, 104 sleeping,   0 stopped,   0 zombie
Cpu(s): 11.4%us, 29.6%sy, 0.0%ni, 58.3%id, .7%wa, 0.0%hi, 0.0%si, 0.0%st
Mem:   1024176k total,   997408k used,    26768k free,    85520k buffers
Swap:  1004052k total,     4360k used,   999692k free,   286040k cached

  PID USER    PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
 9463 mysql   16   0  686m 111m 3328 S   53  5.5 569:17.64 mysqld
18749 nagios  16   0  140m 134m 1868 S   12  6.6   1345:01 nagios2db_status
24636 nagios  17   0 34660  10m  712 S    8  0.5   1195:15 nagios
22442 nagios  24   0  6048 2024 1452 S    8  0.1   0:00.04 check_time.pl
```

As you can see, there's a lot of information in only a few lines. The first line mirrors the information you would get from the `uptime` command and will update every few seconds with the latest **load averages**. In this case, you can see my system is busy, but not what I would call heavily loaded. All the same, this output breaks down well into our different **load categories**. When I troubleshoot a sluggish system, I generally will rule out **CPU-bound load**, then **RAM issues**, then finally **I/O issues** in that order, so let's start with **CPU-bound load**.

> NOTE: 最后一句话是作者给出的troubleshoot的次序，这个次序非常这样，后面的内容就是沿着这个次序展开的，并且后面作者还会介绍使用这个次序的原因。

### CPU-Bound Load

CPU-bound load is load caused when you have too many CPU-intensive processes running at once. Because each process needs CPU resources, they all must wait their turn. To check whether load is **CPU-bound**, check the CPU line in the top output:

```shell
Cpu(s): 11.4%us, 29.6%sy, 0.0%ni, 58.3%id, .7%wa, 0.0%hi, 0.0%si, 0.0%st
```

Each of these percentages are a percentage of the CPU time tied up doing a particular task. Again, you could spend an entire column on all of the output from `top`, so here's a few of these values and how to read them:

| Category | 简介            | 详细说明                                                     |
| -------- | --------------- | ------------------------------------------------------------ |
| `us`     | user CPU time   | More often than not, when you have CPU-bound load, it's due to a process run by a user on the system, such as Apache, MySQL or maybe a shell script. If this percentage is high, a user process such as those is a likely cause of the load. |
| `sy`     | system CPU time | The system CPU time is the percentage of the CPU tied up by kernel and other system processes. **CPU-bound load** should manifest either as a high percentage of user or high system CPU time. |
| `id`     | CPU idle time   | This is the percentage of the time that the CPU spends idle. The higher the number here the better! In fact, if you see really high CPU idle time, it's a good indication that any high load is not **CPU-bound**. |
| `wa`     | I/O wait        | The **I/O wait value** tells the percentage of time the CPU is spending waiting on I/O (typically disk I/O). If you have high load and this value is high, it's likely the load is not **CPU-bound** but is due to either RAM issues or **high disk I/O**. |

#### Track Down CPU-Bound Load

If you do see a high percentage in the **user** or **system** columns, there's a good chance your load is **CPU-bound**. To track down the root cause, skip down a few lines to where `top` displays a list of current processes running on the system. By default, `top` will sort these based on the percentage of CPU used with the processes using the most on `top` (Listing 2).

**Listing 2. Current Processes Example**

```shell
  PID USER   PR NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
 9463 mysql  16  0  686m 111m 3328 S   53  5.5 569:17.64 mysqld
18749 nagios 16  0  140m 134m 1868 S   12  6.6   1345:01 nagios2db_status
24636 nagios 17  0 34660  10m  712 S    8  0.5   1195:15 nagios
22442 nagios 24  0  6048 2024 1452 S    8  0.1   0:00.04 check_time.pl
```

The `%CPU` column tells you just how much CPU each process is taking up. In this case, you can see that MySQL is taking up 53% of my CPU. 

As you look at this output during **CPU-bound load**, you probably will see one of two things: either you will have a single process tying up 99% of your CPU, or you will see a number of smaller processes all fighting for a percentage of CPU time. In either case, it's relatively simple to see the processes that are causing the problem. There's one final note I want to add on **CPU-bound load**: I've seen systems get incredibly high load simply because a multithreaded program spawned a huge number of threads on a system without many CPUs. If you spawn 20 threads on a single-CPU system, you might see a high **load average**, even though there are no particular processes that seem to tie up CPU time.

> NOTE: 对于**CPU-bound load**，大多数情况下，都是如下两种情况:
>
> | 问题                                                         | 解释         |
> | ------------------------------------------------------------ | ------------ |
> | a single process tying up 99% of your CPU                    | 进程占用太高 |
> | a number of smaller processes all fighting for a percentage of CPU time | 进程太多     |
>
> 



### Out of RAM Issues

The next cause for **high load** is a system that has run out of available **RAM** and has started to go into **swap**. Because **swap space** is usually on a hard drive that is much slower than **RAM**, when you use up available **RAM** and go into **swap**, each process slows down dramatically as the disk gets used. 

Usually this causes a downward spiral as processes that have been swapped run slower, take longer to respond and cause more processes to stack up until the system either runs out of RAM or slows down to an absolute crawl. 

> 通常这会导致螺旋式下降，因为交换过的进程运行得更慢，响应时间更长，并导致更多进程堆积在一起，直到系统耗尽RAM或慢到完全爬行。

What's tricky about swap issues is that because they hit the disk so hard, it's easy to misdiagnose them as **I/O-bound load**. After all, if your disk is being used as RAM, any processes that actually want to access files on the disk are going to have to wait in line. So, if I see high **I/O wait** in the CPU row in `top`, I check RAM next and rule it out before I troubleshoot any other I/O issues.

> NOTE: 当“a system that has run out of available **RAM** and has started to go into **swap**”时，由于disk is being used as RAM, any processes that actually want to access files on the disk are going to have to wait in line，所以我们就看到了high **I/O wait** in the CPU row in `top`

When I want to diagnose **out of memory issues**, the first place I look is the next couple of lines in the `top` output:

```shell
Mem: 1024176k total, 997408k used, 26768k free, 85520k buffers
Swap: 1004052k total, 4360k used, 999692k free, 286040k cached
```

These lines tell you the total amount of RAM and swap along with how much is used and free; however, look carefully, as these numbers can be misleading. I've seen many new and even experienced administrators who would look at the above output and conclude the system was almost out of RAM because there was only 26768k free. Although that does show how much RAM is currently unused, it doesn't tell the full story.

> NOTE: 在“The Linux File Cache”中会对此进行解释

#### The Linux File Cache

When you access a file and the Linux kernel loads it into RAM, the kernel doesn't necessarily unload the file when you no longer need it. If there is enough free RAM available, the kernel tries to cache as many files as it can into RAM. That way, if you access the file a second time, the kernel can retrieve it from RAM instead of the disk and give much better performance. As a system stays running, you will find the free RAM actually will appear to get rather small. If a process needs more RAM though, the kernel simply uses some of its **file cache**. In fact, I see a lot of the overclocking crowd who want to improve performance and create a ramdisk to store their files. What they don't realize is that more often than not, if they just let the kernel do the work for them, they'd probably see much better results and make more efficient use of their RAM.

> 事实上，我看到许多超频用户希望提高性能并创建一个ramdisk来存储他们的文件。他们没有意识到的是，通常情况下，如果让内核为他们做这些工作，他们可能会看到更好的结果，并更有效地使用他们的RAM。

To get a more accurate amount of **free RAM**, you need to combine the values from the **free column** with the **cached column**. In my example, I would have 26768k + 286040k, or over 300Mb of free RAM. In this case, I could safely assume my system was not experiencing an out of RAM issue. Of course, even a system that has very little free RAM may not have gone into swap. That's why you also must check the Swap: line and see if a high proportion of your swap is being used.

> NOTE: 最后一句话作者并没有给出结论，我觉得结论是：如果swap的使用比例较高，则说明out of RAM的可能性就比较大了

#### Track Down High RAM Usage

If you do find you are low on free RAM, go back to the same process output from `top`, only this time, look in the `%MEM` column. By default, `top` will sort by the `%CPU` column, so simply type `M` and it will re-sort to show you which processes are using the highest percentage of RAM. In the output in Listing 3, I sorted the same processes by RAM, and you can see that the `nagios2db_status` process is using the most at 6.6%.

**Listing 3. Processes Sorted by RAM**

```
  PID USER   PR NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
18749 nagios 16  0  140m 134m 1868 S   12  6.6   1345:01 nagios2db_status
 9463 mysql  16  0  686m 111m 3328 S   53  5.5 569:17.64 mysqld
24636 nagios 17  0 34660  10m  712 S    8  0.5   1195:15 nagios
22442 nagios 24  0  6048 2024 1452 S    8  0.1   0:00.04 check_time.pl
```

### I/O-Bound Load

**I/O-bound load** can be tricky to track down sometimes. As I mentioned earlier, if your system is swapping, it can make the load appear to be I/O-bound. Once you rule out swapping though, if you do have a high I/O wait, the next step is to attempt to track down which disk and partition is getting the bulk of the I/O traffic. To do this, you need a tool like `iostat`.

The `iostat` tool, like `top`, is a complicated and full-featured tool that could fill up its own article. Unlike `top`, although it should be available for your distribution, it may not be installed on your system by default, so you need to track down which package provides it. Under Red Hat and Debian-based systems, you can get it in the sysstat package. Once it's installed, simply run `iostat` with no arguments to get a good overall view of your disk I/O statistics:

```shell
Linux 2.6.24-19-server (hostname) 	01/31/2009

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           5.73    0.07    2.03    0.53    0.00   91.64

Device:    tps  Blk_read/s  Blk_wrtn/s   Blk_read   Blk_wrtn
sda       9.82       417.96        27.53   30227262    1990625
sda1      6.55       219.10         7.12   15845129     515216
sda2      0.04         0.74         3.31      53506     239328
sda3      3.24       198.12        17.09   14328323    1236081
```

Like with `top`, `iostat` gives you the CPU percentage output. Below that, it provides a breakdown of each drive and partition on your system and statistics for each:

| column       | explanation                |      |
| ------------ | -------------------------- | ---- |
| `tps`        | transactions per second.   |      |
| `Blk_read/s` | blocks read per second.    |      |
| `Blk_wrtn/s` | blocks written per second. |      |
| `Blk_read`   | total blocks read.         |      |
| `Blk_wrtn`   | total blocks written.      |      |

By looking at these different values and comparing them to each other, ideally you will be able to find out first, which partition (or partitions) is getting the bulk of the I/O traffic, and second, whether the majority of that traffic is reads (`Blk_read/s`) or writes (`Blk_wrtn/s`). As I said, tracking down the cause of I/O issues can be tricky, but hopefully, those values will help you isolate what **processes** might be causing the load.

For instance, if you have an **I/O-bound load** and you suspect that your remote backup job might be the culprit（元凶）, compare the read and write statistics. Because you know that a remote backup job is primarily going to read from your disk, if you see that the majority of the disk I/O is writes, you reasonably can assume it's not from the backup job. If, on the other hand, you do see a heavy amount of read I/O on a particular partition, you might run the `lsof` command and `grep` for that **backup process** and see whether it does in fact have some open file handles on that partition.

As you can see, tracking down I/O issues with `iostat` is not straightforward. Even with no arguments, it can take some time and experience to make sense of the output. That said, `iostat` does have a number of arguments you can use to get more information about different types of I/O, including modes to find details about NFS shares. Check out the man page for `iostat` if you want to know more.

Up until recently, tools like `iostat` were about the limit systems administrators had in their toolboxes for tracking down I/O issues, but due to recent developments in the kernel, it has become easier to find the causes of I/O on a per-process level. If you have a relatively new system, check out the `iotop` tool. Like with `iostat`, it may not be installed by default, but as the name implies, it essentially acts like `top`, only for disk I/O. In Listing 4, you can see that an `rsync` process on this machine is using the most I/O (in this case, read I/O).

**Listing 4. Example iotop Tool Output**

```shell
Total DISK READ: 189.52 K/s | Total DISK WRITE: 0.00 B/s
  TID  PRIO  USER DISK READ DISK WRITE  SWAPIN     IO>    COMMAND          
 8169 be/4 root  189.52 K/s   0.00 B/s  0.00 %  0.00 % rsync --server --se
 4243 be/4 kyle    0.00 B/s   3.79 K/s  0.00 %  0.00 % cli /usr/lib/gnome-
 4244 be/4 kyle    0.00 B/s   3.79 K/s  0.00 %  0.00 % cli /usr/lib/gnome-
    1 be/4 root    0.00 B/s   0.00 B/s  0.00 %  0.00 % init
```

#### Once You Track Down the Culprit

How you deal with these load-causing processes is up to you and depends on a lot of factors. In some cases, you might have a script that has gone out of control and is something you can easily kill. In other situations, such as in the case of a database process, it might not be safe simply to kill the process, because it could leave corrupted data behind. Plus, it could just be that your service is running out of capacity, and the real solution is either to add more resources to your current server or add more servers to share the load. It might even be load from a one-time job that is running on the machine and shouldn't impact load in the future, so you just can let the process complete. Because so many different things can cause processes to tie up（占用） server resources, it's hard to list them all here, but hopefully, being able to identify the causes of your high load will put you on the right track the next time you get an alert that a machine is slow.

Kyle Rankin is a Systems Architect in the San Francisco Bay Area and the author of a number of books, including *The Official Ubuntu Server Book*, *Knoppix Hacks* and *Ubuntu Hacks*. He is currently the president of the North Bay Linux Users' Group.



## redhat [Troubleshooting slow servers: How to check CPU, RAM, and Disk I/O](https://www.redhat.com/sysadmin/troubleshooting-slow-servers)

If you been doing sysadmin work long enough, you’ve seen the dreaded "Server is slow" incidents. For a long time, these types of incidents would give me a pit in my stomach. How the heck do you troubleshoot something so subjective（你怎么能解决这么主观的问题呢）? An everyday user’s "slow" might just be caused by other processes (scheduled or not) running and consuming more resources than usual, or something could actually be wrong with the server.



### The "Big 3" (aka CPU, RAM, and Disk I/O)

Now, let’s look at the three biggest causes of server slowdown: CPU, RAM, and disk I/O. CPU usage can cause overall slowness on the host, and difficulty completing tasks in a timely fashion. Some tools I use when looking at CPU are `top` and`sar`.

### Checking CPU usage with top

The `top` utility gives you a real-time look at what’s going on with the server. By default, when `top` starts, it shows activity for all CPUs:

Image

![The first three rows of top&#039;s initial output.](https://www.redhat.com/sysadmin/sites/default/files/styles/embed_large/public/2019-09/how-to-check-big-3-top-1.png?itok=2e43MxSN)

This view can be changed by pressing the numeric 1 key, which adds more detail regarding the usage values for each CPU:

Image

![Press 1 in top to see details for each CPU.](https://www.redhat.com/sysadmin/sites/default/files/styles/embed_large/public/2019-09/how-to-check-big-3-top-2.png?itok=NQUQnE3U)

Some things to look for in this view would be the load average (displayed on the right side of the top row), and the value of the following for each CPU:

- `us`: This percentage represents the amount of CPU consumed by user processes.
- `sy`: This percentage represents the amount of CPU consumed by system processes.
- `id`: This percentage represents how idle each CPU is.

Each of these three values can give you a fairly good, real-time idea of whether CPUs are bound by user processes or system processes.

**Note:** For more information about load average and why some people think it’s a silly number, check out [Brendan Gregg’s in-depth research](http://www.brendangregg.com/blog/2017-08-08/linux-load-averages.html).

### Checking all of the "Big 3" with sar

For historical CPU performance data I rely on the `sar` command, which is provided by the `sysstat` package. On most server versions of Linux, `sysstat` is installed by default, but if it’s not, you can add it with your distro’s package manager. The `sar` utility collects system data every 10 minutes via a cron job located in `/etc/cron.d/sysstat` (CentOS 7.6). Here’s how to check all of the "Big 3" using `sar`.