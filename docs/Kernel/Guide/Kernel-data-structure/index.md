# Kernel data structure



## TODO: 各种各样的table

kernel管理着OS的一切资源，因此，它一般使用table来进行管理，比如：

| table         | 简介                     | 参考                                                         |
| ------------- | ------------------------ | ------------------------------------------------------------ |
| 进程表        | 记录OS中的所有的process  |                                                              |
| 文件表        | 记录OS中所有的打开的文件 | APUE                                                         |
| socket table  | 记录OS中的所有的socket   | - [ss(8) - Linux man page](https://linux.die.net/man/8/ss)<br>- wikipedia TCP#[Resource usage](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Resource_usage) |
| Routing table | 记录路由规则             | wikipedia [Routing table](https://en.wikipedia.org/wiki/Routing_table) |

底层采用何种data structure来进行实现，需要考虑多重因素：

- 查找的时间复杂度
- 空间复杂度



## TODO: Entry of table

前面介绍了table，现在介绍entry of table，一般entry of table被称为:

- `******`control block
- `******`descriptor

比如:

| table        | entry                             | 参见                                                         |
| ------------ | --------------------------------- | ------------------------------------------------------------ |
| socket table | Transmission Control Block or TCB | - wikipedia TCP#[Resource usage](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Resource_usage) |
|              |                                   |                                                              |
|              |                                   |                                                              |



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

