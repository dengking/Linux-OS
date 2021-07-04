# network IO event and IO multiplexing

一、需要结合socket的data structure来进行理解



| event    | buffer      | socket option                  | 含义                           | 默认值 |
| -------- | ----------- | ------------------------------ | ------------------------------ | ------ |
| readable | recv buffer | `SO_RCVLOWAT` / **接收低水位** | **接收缓冲区**中所需的数据量   | 1      |
| writable | send buffer | `SO_SNDLOWAT` / **发送低水位** | **发送缓冲区**中所需的可用空间 | 2048   |



## 参考文章

csdn [网络编程学习笔记--1.socket可读可写条件](https://blog.csdn.net/majianfei1023/article/details/45788591)



### 官方说明文档

在下面文章中，对此进行了介绍:

一、[socket(7) Linux Programmer's Manual](http://man7.org/linux/man-pages/man7/socket.7.html)  

其中的内容是以 [poll(2)](https://man7.org/linux/man-pages/man2/poll.2.html)、[select(2)](https://man7.org/linux/man-pages/man2/select.2.html) 为例进行说明的

二、[epoll_ctl(2) — Linux manual page](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)

其中描述了epoll的IO event

## csdn [网络编程学习笔记--1.socket可读可写条件](https://blog.csdn.net/majianfei1023/article/details/45788591)

要了解socket可读可写条件，我们先了解几个概念：

一、**接收缓存区低水位标记**（用于读）和**发送缓存区低水位标记**（用于写）：

每个套接字有一个接收低水位和一个发送低水位。他们由`select`函数使用。

1、接收低水位标记是让select返回"可读"时套接字接收缓冲区中所需的数据量。对于TCP,其默认值为1。

2、发送低水位标记是让select返回"可写"时套接字发送缓冲区中所需的可用空间。对于TCP，其默认值常为2048.（也是面试点之一）

通俗的解释一下，缓存区我们当成一个大小为 n bytes的空间，那么：

**接收区缓存**的作用就是，接收对面的数据放在缓存区，供应用程序读。当然了，只有当缓存区可读的数据量(接收低水位标记)到达一定程度（eg:1）的时候，我们才能读到数据，不然不就读不到数据了吗。

**发送区缓存**的作用就是，发送应用程序的数据到缓存区，然后一起发给对面。当然了，只有当缓存区剩余一定空间(发送低水位标记)（eg:2048）,你才能写数据进去，不然可能导致空间不够。

### socket可读的条件

首先来看看socket可读的条件

**一、下列四个条件中的任何一个满足时,socket准备好读:** 

1、socket的接收缓冲区中的数据字节大于等于该socket的接收缓冲区低水位标记的当前大小。对这样的socket的读操作将不阻塞并返回一个大于0的值(也就是返回准备好读入的数据)。我们可以用`SO_RCVLOWAT` socket选项来设置该socket的低水位标记。对于TCP和UDP socket而言，其缺省值为1.

2、该连接的读这一半关闭(也就是接收了FIN的TCP连接)。对这样的socket的读操作将不阻塞并返回0

> NOTE: 
>
> 一、这段话要如何理解？
>
> 对端调用了`shutdown`，也就是对端关闭了写，这样本端显然就再也读不到数据了

3、socket是一个用于监听的socket,并且已经完成的连接数为非0.这样的soocket处于可读状态,是因为socket收到了对方的connect请求,执行了三次握手的第一步:对方发送SYN请求过来,使监听socket处于可读状态;正常情况下,这样的socket上的accept操作不会阻塞;

4、有一个socket有异常错误条件待处理.对于这样的socket的**读操作**将不会阻塞,并且返回一个错误(-1),errno则设置成明确的错误条件.这些待处理的错误也可通过指定socket选项`SO_ERROR`调用getsockopt来取得并清除;

### socket可写的条件

再来看看socket可写的条件.

**二、下列三个条件中的任何一个满足时,socket准备好写:** 

1、socket的发送缓冲区中的数据字节大于等于该socket的发送缓冲区低水位标记的当前大小。对这样的socket的写操作将不阻塞并返回一个大于0的值(也就是返回准备好写入的数据)。我们可以用`SO_SNDLOWAT` socket选项来设置该socket的低水位标记。对于TCP和UDPsocket而言，其缺省值为2048

2、该连接的写这一半关闭。对这样的socket的写操作将产生`SIGPIPE`信号，该信号的缺省行为是终止进程。

3、有一个socket异常错误条件待处理.对于这样的socket的写操作将不会阻塞并且返回一个错误(-1),errno则设置成明确的错误条件.这些待处理的错误也可以通过指定socket选项SO_ERROR调用getsockopt函数来取得并清除;解释一下连接的读/写这一半关闭：

![img](https://img-blog.csdn.net/20150612205950083)

如图：

终止一个连接需要4个分节，主动关闭的一端（A）调用close发送FIN到另一端（B），B接收到FIN后，知道A已经主动关闭了，也就是，A不会发数据来了，那么这一端调用read必然可读，且返回0(read returns 0).
