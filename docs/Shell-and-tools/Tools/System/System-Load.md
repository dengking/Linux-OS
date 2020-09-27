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

The next cause for **high load** is a system that has run out of available RAM and has started to go into **swap**. Because **swap space** is usually on a hard drive that is much slower than RAM, when you use up available RAM and go into swap, each process slows down dramatically as the disk gets used. Usually this causes a downward spiral as processes that have been swapped run slower, take longer to respond and cause more processes to stack up until the system either runs out of RAM or slows down to an absolute crawl. What's tricky about swap issues is that because they hit the disk so hard, it's easy to misdiagnose them as I/O-bound load. After all, if your disk is being used as RAM, any processes that actually want to access files on the disk are going to have to wait in line. So, if I see high I/O wait in the CPU row in top, I check RAM next and rule it out before I troubleshoot any other I/O issues.

#### The Linux File Cache



#### Track Down High RAM Usage



### I/O-Bound Load



#### Once You Track Down the Culprit