# 如何阅读linux OS kernel源代码

如何阅读linux kernel的source code？在拿起本书的时候我思考了这个问题，下面是我检索到的我觉得有道理的[观点](https://softwareengineering.stackexchange.com/a/46640)：

**Focus on data structures**. Understanding **data structures** is usually more important than **code**.

If you are only shown **data structures** but no code, you still get the big **picture** of the system.

Vice versa, if shown only code but not data structures, it's very hard to understand the system.

> "I will, in fact, claim that the difference between a bad programmer and a good one is whether he considers his code or his data structures more important. Bad programmers worry about the code. Good programmers worry about data structures and their relationships." -- Linus Torvalds
>
> "Show me your flowcharts and conceal your tables, and I shall continue to be mystified. Show me your tables, and I won't usually need your flowcharts; they'll be obvious." -- Fred Brooks.

[How to understand Linux kernel source code for a beginner? ](https://softwareengineering.stackexchange.com/questions/46610/how-to-understand-linux-kernel-source-code-for-a-beginner)



从structure入手，本书也是如此。

本章会给出阅读Linux OS kernel源码的指导，并对Linux OS kernel源码中的一些重要的data structure进行总结。





