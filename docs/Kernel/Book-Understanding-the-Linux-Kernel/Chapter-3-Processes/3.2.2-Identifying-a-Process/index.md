# 3.2.2. Identifying a Process

> 注意： 本文中的process所指为lightweight process，`pid`所指指为lightweight process的`pid`，并非标准的process和标准的`pid`。在本文中，thread group表示的是标准的process，`tgid`为标准的`pid`。

As a general rule, each **execution context** that can be independently scheduled must have its own **process descriptor**; therefore, even **lightweight processes**, which share a large portion of their kernel data structures, have their own  `task_struct` structures.

The strict one-to-one correspondence between the **process** and **process descriptor** makes the 32-bit address [ ] of the  `task_struct` structure a useful means for the kernel to identify processes. These addresses are referred to as *process descriptor pointers*. Most of the references to processes that the kernel makes are through **process descriptor pointers**.

> [ ] As already noted in the section "Segmentation in Linux" in Chapter 2, although technically these 32 bits are only the offset component of a logical address, they coincide with the **linear address**

On the other hand, Unix-like operating systems allow users to identify processes by means of a number called the *Process ID* (or `PID`), which is stored in the  `pid` field of the **process descriptor**. PIDs are numbered sequentially: the `PID` of a newly created process is normally the `PID` of the previously created process increased by one. Of course, there is an upper limit on the `PID` values; when the kernel reaches such limit, it must start recycling the lower, unused PIDs. By default, the maximum `PID` number is 32,767 ( `PID_MAX_DEFAULT` - 1 ); the system administrator may reduce this limit by writing a smaller value into the `/proc/sys/kernel/pid_max` file `(/proc` is the mount point of a special filesystem, see the section "Special Filesystems" in Chapter 12). In 64-bit architectures, the system administrator can enlarge the maximum PID number up to 4,194,303.

When recycling PID numbers, the kernel must manage a  `pidmap_array` bitmap that denotes which are the PIDs currently assigned and which are the free ones. Because a page frame contains 32,768（`4K`）bits, in 32-bit architectures the  `pidmap_array` bitmap is stored in a single page. In 64-bit architectures, however, additional pages can be added to the bitmap when the kernel assigns a PID number too large for the current bitmap size. These pages are never released.

> NOTE: 关于`pidmap_array`，参见
> - https://elixir.bootlin.com/linux/v2.6.17.7/source/kernel/pid.c#L46
> - https://blog.csdn.net/Jay14/article/details/54863073



Linux associates a different `PID` with each **process** or **lightweight process** in the system. (As we shall see later in this chapter, there is a tiny exception on multiprocessor systems.) This approach allows the maximum flexibility, because every **execution context** in the system can be uniquely identified.

On the other hand, Unix programmers expect threads in the same **group** to have a common `PID`. For instance, it should be possible to a send a signal specifying a `PID` that affects all threads in the group. In fact, the `POSIX 1003.1c` standard states that all threads of a multithreaded application must have the same `PID`.

To comply with this standard, Linux makes use of **thread groups**. The identifier shared by the threads is the `PID` of the **thread group leader** , that is, the `PID` of the first **lightweight process** in the group; it is stored in the  `tgid` field of the **process descriptors**. The  `getpid( )` system call returns the value of  `tgid` relative to the current process instead of the value of  `pid` , so all the threads of a multithreaded application share the same identifier. Most processes belong to a **thread group** consisting of a single member; as thread group leaders, they have the  `tgid` field equal to the  `pid` field, thus the  `getpid( )` system call works as usual for this kind of process.

Later, we'll show you how it is possible to derive a true process descriptor pointer efficiently from its respective `PID`. Efficiency is important because many system calls such as  `kill( )` use the `PID` to denote the affected process.







