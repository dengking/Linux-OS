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

