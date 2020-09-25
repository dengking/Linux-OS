# High Load



## linuxjournal [Hack and / - Linux Troubleshooting, Part I: High Load](https://www.linuxjournal.com/article/10688)

Although it's true that there are about as many different reasons for **downtime** as there are Linux text editors, and just as many approaches to troubleshooting, over the years, I've found I perform the same sorts of steps to isolate a problem. Because my column is generally aimed more at **tips and tricks** and less on **philosophy and design**, I'm not going to talk much about overall approaches to problem solving. Instead, in this series I describe some general classes of problems you might find on a Linux system, and then I discuss how to use common tools, most of which probably are already on your system, to isolate and resolve each class of problem.

> NOTE: 作者对知识的划分：
>
> - **tips and tricks**
> - **philosophy and design**
>
> 是非常值得工程师借鉴的

For this first column, I start with one of the most common problems you will run into on a Linux system. No, it's not getting printing to work. I'm talking about a sluggish（迟钝的） server that might have **high load**. Before I explain how to diagnose and fix high load though, let's take a step back and discuss **what load means** on a Linux machine and how to know when it's **high**.

### Uptime and Load

When administrators mention high load, generally they are talking about the *load average*. When I diagnose why a server is slow, the **first** command I run when I log in to the system is `uptime`:

```
$ uptime
 18:30:35 up 365 days, 5:29, 2 users, load average: 1.37, 10.15, 8.10
```

> NOTE: 关于`uptime`，参见 `Shell-and-tools\Tools\uptime.md` 



### How High Is High?

> NOTE: 多高才能算是高？

After you understand what load average means, the next logical question is “What load average is good and what is bad?” The answer to that is “It depends.” You see, a lot of different things can cause load to be high, each of which affects performance differently. One server might have a load of 50 and still be pretty responsive, while another server might have a load of 10 and take forever to log in to.

What really matters when you troubleshoot a system with high load is *why* the load is high. When you start to diagnose high load, you find that most load seems to fall into three categories: CPU-bound load, load caused by out of memory issues and I/O-bound load. I explain each of these categories in detail below and how to use tools like top and iostat to isolate the root cause.