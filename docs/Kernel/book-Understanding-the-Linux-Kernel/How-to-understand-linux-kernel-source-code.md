[TOC]



# [How to understand Linux kernel source code for a beginner? ](https://softwareengineering.stackexchange.com/questions/46610/how-to-understand-linux-kernel-source-code-for-a-beginner)

I am a student interested in working on **Memory Management**, particularly the page replacement component of the linux kernel.

What are the different guides that can help me to begin understanding the kernel source?

I have tried to read the book *Understanding the Linux Virtual Memory Manager* by Mel Gorman and *Understanding the Linux Kernel* by Cesati and Bovet, but they do not explain the flow of control through the code. They only end up explaining various data structures used and the work various functions perform. This makes the code more confusing.

My project deals with tweaking the **page replacement algorithm** in a mainstream kernel and **analyse its performance** for a set of workloads. Is there a flavor of the linux kernel that would be easier to understand (if not the linux-2.6.xx kernel)?



## [A](https://softwareengineering.stackexchange.com/a/46640)

**Focus on data structures**. Understanding **data structures** is usually more important than **code**.

If you are only shown **data structures** but no code, you still get the big **picture** of the system.

Vice versa, if shown only code but not data structures, it's very hard to understand the system.

> "I will, in fact, claim that the difference between a bad programmer and a good one is whether he considers his code or his data structures more important. Bad programmers worry about the code. Good programmers worry about data structures and their relationships." -- Linus Torvalds
>
> "Show me your flowcharts and conceal your tables, and I shall continue to be mystified. Show me your tables, and I won't usually need your flowcharts; they'll be obvious." -- Fred Brooks.

