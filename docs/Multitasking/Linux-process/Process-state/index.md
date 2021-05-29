# 关于本章

本章讨论process state，即“进程状态”，在下面章节中，也对它进行了说明:

| 章节                                                         | 说明                                       |
| ------------------------------------------------------------ | ------------------------------------------ |
| `Kernel\Book-Understanding-the-Linux-Kernel\Chapter-3-Processes\3.2.1-Process-State.md` | 介绍了一些process state                    |
| `Programming\Process\Tools\procps\ps`                        | 介绍了如何查看process state、process state |
| `Shell-and-tools\Tools\Debug\Application\Stuck-process.md`   |                                            |



## TODO

process的state不止上面所枚举的那些；

[How to suspend/resume a process in Windows?](https://stackoverflow.com/questions/11010165/how-to-suspend-resume-a-process-in-windows)



[How can I freeze the execution of a program?](https://stackoverflow.com/questions/4062665/how-can-i-freeze-the-execution-of-a-program)



[The TTY demystified](http://www.linusakesson.net/programming/tty/index.php) 中统计process可能被暂停



SIGSTOP

## 20190512

要想知道OS中所有的process state，查看`ps`命令的doc是可以知道的，其中的[PROCESS STATE CODES](http://man7.org/linux/man-pages/man1/ps.1.html#PROCESS_STATE_CODES) 章节对此进行了非常详细的介绍；



## 在process中补充stopped状态

在[The TTY demystified](http://www.linusakesson.net/programming/tty/index.php)中有这样的一段话：

> T	Stopped, either by a job control signal or because it is being traced by a debugger.

这让我想起了debugger中，我们是可以设置断点的，即让process执行到某处就暂停下来；并且在debugger中，我们可以指定process开始运行，显然这些都是停止一个process和恢复一个process的运行有关的：

[How to suspend and resume processes](https://unix.stackexchange.com/questions/2107/how-to-suspend-and-resume-processes)

