# Guide to controlling process

本节主要讨论的内容是：对process的运行进行控制，它是gdb的一个非常重要的特性。

## 章节

run and kill，即运行和终止程序，下面是涉及这个主题的章节

- [4 Running Programs Under GDB](https://sourceware.org/gdb/onlinedocs/gdb/Running.html#Running)
- [6 Running programs backward](https://sourceware.org/gdb/onlinedocs/gdb/Reverse-Execution.html#Reverse-Execution)
- [7 Recording Inferior’s Execution and Replaying It](https://sourceware.org/gdb/onlinedocs/gdb/Process-Record-and-Replay.html#Process-Record-and-Replay)

stop and continue，即在process运行过程中，stop、continue，下面是涉及这个主题的章节：

- [5 Stopping and Continuing](https://sourceware.org/gdb/onlinedocs/gdb/Stopping.html#Stopping)

alter

- [17 Altering Execution](https://sourceware.org/gdb/onlinedocs/gdb/Altering.html#Altering)





## Mode

process execution 是非常复杂的，它不仅仅涉及gdb，还涉及OS；对于各种复杂的场景，gdb都有着较好的支持，因此可以看到，在gdb中，有着非常多的mode，本节对gdb中涉及process execution的mode进行汇总：



## Command shortcut

