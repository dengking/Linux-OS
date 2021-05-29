# 如何阻塞一个进程？

总的来说，当process

1、一个进程尝试去修改数据库中的一个表的名称，而此时已经有一个进程正在从该表中读取数据，则修改表名称的进程将被阻塞。

2、mutex

3、[epoll](https://linux.die.net/man/7/epoll)

4、阻塞IO，在这篇文章中介绍的[Blocking I/O, Nonblocking I/O, And Epoll](https://eklitzke.org/blocking-io-nonblocking-io-and-epoll)

## Block process VS process relinquish CPU

block 一个 process和一个process主动地relinquish CPU最终都是由OS kernel来进行调度的；

不同的是block一个process是由OS来决定的，即process只能够被动地接收，往往出现在当process执行某个system call，但是它请求的操作暂时无法完成，则OS kernel会将 这个process的执行给中断或者说是挂起这个process的执行；

而process relinquish CPU 则显然是process的主动行为，即它告诉kernel，暂时我不想执行了，你把我挂起吧；OS是提供了这些系统调用的；

