# System call



## System call as request to hardware

"tag-Linux kernel design-monolithic kernel集成核-system call as request to hardware"

"tag-Linux kernel design-monolithic kernel集成核-system call l是process和kernel之间的interface"



## System call也相当于interrupt

上面使用的是“相当于”，而不是“是”，这是因为随着技术的更新迭代，实现system call的assembly instruction也在进行更新迭代，可能原来使用的中断指令（`int` assembly instruction）会替换为更加高效的assembly instruction。在10.3. Entering and Exiting a System Call中对此进行了详细的说明，如下：

Applications can invoke a system call in two different ways:

1、By executing the  `int $0x80` assembly language instruction; in older versions of the Linux kernel, this was the only way to switch from User Mode to Kernel Mode.

2、By executing the  `sysenter` assembly language instruction, introduced in the Intel Pentium II microprocessors; this instruction is now supported by the Linux 2.6 kernel.

使用`int $0x80`的方式是interrupt，使用`sysenter` 的方式则不是interrupt，但是它的作用其实和interrupt非常类似，我们可以将它看做是interrupt。

关于`sysenter`，参加：

- https://wiki.osdev.org/Sysenter

上面描述的interrupt主要来自于hardware，其实system call的实现也是依赖于interrupt。

在chapter 4.2. Interrupts and Exceptions的“Programmed exceptions”有这样的描述：

> Such exceptions have two common uses: to implement **system calls** and to notify a debugger of a specific event (see Chapter 10).



## TODO

gitbooks Linux insides [System calls in the Linux kernel. Part 1.](https://0xax.gitbooks.io/linux-insides/content/SysCall/linux-syscall-1.html)
