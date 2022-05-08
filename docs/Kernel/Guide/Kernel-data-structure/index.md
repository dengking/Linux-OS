# kernel data structure

## 如何阅读linux OS kernel源代码

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



## Kernel data structure



### 各种各样的table

kernel管理着OS的一切资源，因此，它一般使用table来进行管理，比如：

| table         | 简介                     | 参考                                                         |
| ------------- | ------------------------ | ------------------------------------------------------------ |
| 进程表        | 记录OS中的所有的process  |                                                              |
| 文件表        | 记录OS中所有的打开的文件 | APUE                                                         |
| socket table  | 记录OS中的所有的socket   | - [ss(8) - Linux man page](https://linux.die.net/man/8/ss)<br>- wikipedia TCP#[Resource usage](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Resource_usage) |
| Routing table | 记录路由规则             | wikipedia [Routing table](https://en.wikipedia.org/wiki/Routing_table) |

底层采用何种data structure来进行实现，需要考虑多重因素：

1、查找的时间复杂度

2、空间复杂度



### Entry of table

前面介绍了table，现在介绍entry of table，一般entry of table被称为:

- `******`control block
- `******`descriptor

比如:

| table        | entry                             | 参见                                                         |
| ------------ | --------------------------------- | ------------------------------------------------------------ |
| socket table | Transmission Control Block or TCB | - wikipedia TCP#[Resource usage](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Resource_usage) |
|              |                                   |                                                              |
|              |                                   |                                                              |



### 各种各样的descriptor

各种各样的descriptor，以及其对应的数据结构

| Descriptor         | Chapter                    | Struct        | Source Code                                                  |
| ------------------ | -------------------------- | ------------- | ------------------------------------------------------------ |
| Process Descriptor | 3.2. Process Descriptor    | `task_struct` | - https://github.com/torvalds/linux/blob/master/include/linux/sched.h <br/>- https://elixir.bootlin.com/linux/latest/ident/task_struct |
| Memory Descriptor  | 9.2. The Memory Descriptor | `mm_struct`   | - https://elixir.bootlin.com/linux/latest/ident/mm_struct <br/>- https://github.com/torvalds/linux/blob/master/include/linux/mm_types.h |
| Page Descriptor    | 8.1.1. Page Descriptors    | `page`        | - https://elixir.bootlin.com/linux/latest/source/include/linux/mm_types.h#L68 |

Task State Segment Descriptor 

3.3. Process Switch

Global Descriptor Table

memory descriptor

signal descriptor 

file descriptors

Interrupt Descriptor Table

