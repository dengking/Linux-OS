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



下面总结了一些structure：

## 各种各样的descriptor

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



