# 14.2 Nonblocking I/O



## 一些想法

阻塞的函数往往是和进程的阻塞状态有关的，一旦阻塞，则表示进程将暂停执行。

这一节最后一段引起了我的思考:前面它说，执行低速的系统调用是可能会使进程永远阻塞的一类系统调用。对于这段话我的想法是当进程被阻塞的时候，此时进程的状态是blocking。

在最后一段中，作者又介绍，可以使用多线程，让其中一个线程来执行低速的io操作，其他线程则无需阻塞，可以继续执行。

显然，此时进程的一个线程被阻塞了，但是进程中的其他线程仍然继续运行，那么此时进程的状态是什么呢？
