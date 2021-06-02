# 前言

`EPOLLRDHUP` 和`EPOLLHUP`名称中的`HUP`的含义是hang up，表示挂断；它们是由`shutdown`系统调用或`close`系统调用所触发的；其实两者之间本质的差异在其名称中就已经体现出来了：`RDHUP`添加了前缀`RD`，表示读挂起，在[EPOLL_CTL(2)](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)中对其的解释是:

> Stream socket peer closed connection, or shut down writing half of connection.  (This flag is especially useful for writing simple code to detect peer shutdown when using Edge Triggered monitoring.)

`EPOLLHUP`的注解如下：

> Hang up happened on the associated file descriptor.`epoll_wait(2)` will always wait for this event; it is not necessary to set it in events.
>
> Note that when reading from a channel such as a pipe or a stream socket, this event merely indicates that the peer closed its end of the channel.  Subsequent reads from the channel will return 0 (end of file) only after all outstanding data in the channel has been consumed.


# [EPOLLRDHUP vs EPOLLHUP](https://blog.csdn.net/zhouguoqionghai/article/details/94591475)

## `EPOLLRDHUP` 表示**读关闭**

不是所有的内核版本都支持，没有查证。有两种场景：

1、对端发送 `FIN` (对端调用`close` 或者 `shutdown(SHUT_WR)`).

2、本端调用 `shutdown(SHUT_RD)`. 当然，关闭 `SHUT_RD` 的场景很少。

***SUMMARY*** : 对端是write， 本端是read

测试环境为  Linux localhost.localdomain 3.10.0-957.el7.x86_64 #1 SMP Thu Nov 8 23:39:32 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux。
————————————————

使用 python 的服务端测试过程，客户端仅仅建立 TCP 连接，不发送任何数据。第 10 条指令 poll 超时，返回一个空的列表。通过关闭本端的读取，再次 poll 可以看到，返回 `hex(8193) = 0x2001` 表示`EPOLLRDHUP` 和 `EPOLLIN` 事件。

```python

In [1]: import socket                                                                                                                                                                                                            

In [2]: serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)                                                                                                                                             

In [3]: serv.bind(("0.0.0.0", 7777))                                                                                                                                                                                             

In [4]: serv.listen(5)                                                                                                                                                                                                           

In [5]: import select                                                                                                                                                                                                            

In [6]: epoll_fd = select.epoll()                                                                                                                                                                                                

In [7]: client,addr = serv.accept()                                                                                                                                                                                              

In [8]: client                                                                                                                                                                                                                   
Out[8]: <socket.socket fd=15, family=AddressFamily.AF_INET, type=SocketKind.SOCK_STREAM, proto=6, laddr=('192.168.1.168', 7777), raddr=('192.168.1.120', 8790)>

In [9]: epoll_fd.register(client, select.EPOLLIN | select.EPOLLRDHUP)                                                                                                                                                            

In [10]: epoll_fd.poll(5)                                                                                                                                                                                                        
Out[10]: []

In [11]: client.shutdown(socket.SHUT_RD)                                                                                                                                                                                         

In [12]: epoll_fd.poll(5)                                                                                                                                                                                                        
Out[12]: [(15, 8193)]

In [13]: for i in dir(select): 
    ...:     if "EPOLL" in i: 
    ...:         print(i, hex(getattr(select, i))) 
    ...:                                                                                                                                                                                                                         
EPOLLERR 0x8
EPOLLET -0x80000000
EPOLLHUP 0x10
EPOLLIN 0x1
EPOLLMSG 0x400
EPOLLONESHOT 0x40000000
EPOLLOUT 0x4
EPOLLPRI 0x2
EPOLLRDBAND 0x80
EPOLLRDHUP 0x2000
EPOLLRDNORM 0x40
EPOLLWRBAND 0x200
EPOLLWRNORM 0x100

```

本端不动，客户端 shutdown(SHUT_WR) 得到一样的结果。 



![img](https://img-blog.csdnimg.cn/2019070323163913.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pob3VndW9xaW9uZ2hhaQ==,size_16,color_FFFFFF,t_70)





## `EPOLLHUP` 表示读写都关闭。






# [How to deal with EPOLLERR and EPOLLHUP?](https://stackoverflow.com/questions/24119072/how-to-deal-with-epollerr-and-epollhup)



