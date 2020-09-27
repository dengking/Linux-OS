# top

## [top(1) - Linux man page](https://linux.die.net/man/1/top)

### Overview

The remaining Table of Contents 

1 COMMAND-LINE Options 

2 FIELDS / Columns 

a. DESCRIPTIONS of Fields 

b. SELECTING and ORDERING Columns 

3 INTERACTIVE Commands 

a. GLOBAL Commands 

b. SUMMARY Area Commands 

c. TASK Area Commands 

d. COLOR Mapping 

4 ALTERNATE-DISPLAY Mode 

a. WINDOWS Overview 

b. COMMANDS for Windows 

5 FILES 

a. SYSTEM Configuration File 

b. PERSONAL Configuration File 

6 STUPID TRICKS Sampler 

a. Kernel Magic 

b. Bouncing Windows 

c. The Big Bird Window 

7 BUGS

8 HISTORY Former top

9 AUTHOR

10 SEE ALSO

### 1. COMMAND-LINE Options

### 2. FIELDS / Columns

### 2a. DESCRIPTIONS of Fields

### 2b. SELECTING and ORDERING Columns

### 2c. SUMMARY Area Fields

### 3. INTERACTIVE Commands

### 3a. GLOBAL Commands

### 3b. SUMMARY Area Commands

**'1'**

*Toggle_Single/Separate_Cpu_States* **--** On/Off

> NOTE: 简单说来，键入1，表示我们想要查看: Show CPU Usage on all cores，这是我在阅读haydenjames [Linux server performance: Is disk I/O slowing your application?](https://haydenjames.io/linux-server-performance-disk-io-slowing-application/) 时发现的，它的视频中展示了CPU-wise usage info。下面是一些对此进行说明的文章:
>
> - bencane [Top: Show CPU Usage on all cores](https://bencane.com/2011/08/28/top-show-cpu-usage-on-all-cores/) 
> - stackexchange [top command on multi core processor](https://unix.stackexchange.com/questions/146085/top-command-on-multi-core-processor) 
> - cyberciti [How to display cpu wise usage using top command on FreeBSD Unix operating system](https://www.cyberciti.biz/faq/how-to-find-the-usage-of-individual-cpu-top-command-usage-freebsd/)



## top %CPU over 100%

下面文章对这个问题进行了解释: 

- askubuntu [top command on ubuntu multicore cpu shows cpu usage >100%](https://askubuntu.com/questions/707203/top-command-on-ubuntu-multicore-cpu-shows-cpu-usage-100)

- stackexchange [Understanding %CPU while running top command [duplicate]](https://unix.stackexchange.com/questions/145247/understanding-cpu-while-running-top-command)
- superuser [Why is the “top” command showing a CPU usage of 799%?](https://superuser.com/questions/457624/why-is-the-top-command-showing-a-cpu-usage-of-799)

下面是我觉得最好的回答:

[A](https://unix.stackexchange.com/a/145249): 

> **%CPU** -- CPU Usage : The percentage of your CPU that is being used by the process. **By default, `top` displays this as a percentage of a single CPU.** On multi-core systems, you can have percentages that are greater than 100%. For example, if 3 cores are at 60% use, `top` will show a CPU use of 180%. See [here](https://superuser.com/a/457634/333431) for more information. **You can toggle this behavior by hitting Shifti while `top` is running to show the overall percentage of available CPUs in use.**

[Source for above quote](https://superuser.com/a/575330/333431).

You can use `htop` instead.

------

To answer your question about how many cores and virtual cores you have:

According to your `lscpu` output:

- You have 32 cores (`CPU(s)`) in total.
- You have 2 physical sockets (`Socket(s)`), each contains 1 physical processor.
- Each processor of yours has 8 physical cores (`Core(s) per socket`) inside, which means you have 8 * 2 = 16 real cores.
- Each real core can have 2 threads (`Thread(s) per core`), which means you have real cores * threads = 16 * 2 = 32 cores in total.

So you have 32 virtual cores from 16 real cores.

Also see [this](http://buildwindows.wordpress.com/2012/12/13/virtualization-processor-core-logical-processor-virtual-processor-what-does-this-mean/), [this](https://kb.iu.edu/d/avfb) and [this](http://linuxconfig.org/getting-know-a-hardware-on-your-linux-box) link.