# Multiplex on file descriptor

一、Unix philosophy-everything is a file descriptor-is a good abstraction

Linux-OS支持:

1、signal to file descriptor / self-pipe trick

2、eventfd

3、time to fd

4、network IO

5、file IO

二、Linux-OS的IO multiplexing其实是一种监控机制，用于监控event

1、利用"支持设置timeout(system call with timeout)"的特性，可以同时实现Multiplex on file event and time event

2、同时实现Multiplex on file and time event的实现往往只需要single thread即可

关于此，在把voidcn [redis源码的linux网络库提取出来，自己封装成通用库使用（★firecat推荐★）](http://www.voidcn.com/article/p-agorceqr-brv.html) 中有这样的介绍

> Redis网络库是一个单线程EPOLL模型，也就是说接收连接和处理读写请求包括**定时器任务**都被这一个线程包揽，真的是又当爹又当妈，但是效率一定比多线程差吗？不见得。
>
> 单线程的好处有： 
>
> 1：避免线程切换带来的上下文切换开销。 
>
> 2：单线程避免了锁的争用。 
>
> 3：对于一个内存型数据库，如果不考虑数据持久化，也就是读写物理磁盘，不会有阻塞操作，内存操作是非常快的。

三、上述策略是当今大多数Linux-OS event-driven concurrent server的event/main loop的实现方式

下面是使用了这个特性的library:

## [libevent](https://libevent.org/) 

> The *libevent* API provides a mechanism to execute a callback function when a specific event occurs on a file descriptor or after a timeout has been reached. Furthermore, *libevent* also support callbacks due to **signals** or regular **timeouts**.

## Redis ae

参见工程"decompose-redis"的`Event-library`章节

## [libuv](https://libuv.org/) 

下面是 [libuv](https://libuv.org/) Design overview[¶](http://docs.libuv.org/en/v1.x/design.html#design-overview) # The I/O loop[¶](http://docs.libuv.org/en/v1.x/design.html#the-i-o-loop) 总结的: 

> The I/O (or event) loop is the central part of libuv. It establishes the content for all I/O operations, and it’s meant to be tied to a single thread. One can run multiple event loops as long as each runs in a different thread. The libuv event loop (or any other API involving the loop or handles, for that matter) **is not thread-safe** except where stated otherwise.
>
> In order to better understand how the event loop operates, the following diagram illustrates all stages of a loop iteration:
>
> [![_images/loop_iteration.png](http://docs.libuv.org/en/v1.x/_images/loop_iteration.png)](http://docs.libuv.org/en/v1.x/_images/loop_iteration.png)



