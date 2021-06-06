# Relationship between process and port

应该从**关系代数**的角度来看待这个问题：

process 和 port，两者之间参与关系的可能方式有：

1、一个process可以有bind多个port

2、一个port可以被多个process bind

这就好比在数据库系统设计中经常出现的：人和爱好的关系：

1、一个人可以有多个爱好

2、一个爱好可以被多个人拥有，或者说多个人同时拥有同一个爱好

这种关系在数据库设计中我们常常会使用一张表来存储这种关系，所以我想，在OS kernel中，也应该有一个专门的data structure来存储这个结构。

## csdn [单个进程监听多个端口及多个进程监听同一个端口](https://blog.csdn.net/qq_43718131/article/details/86213097)

### 单个进程监听多个端口

> NOTE: 
>
> 这种是非常常见的，比如IO multiplexing

单个进程创建多个 socket 绑定不同的端口，TCP, UDP 都行



### 多个进程监听同一个端口(multiple processes listen on same port)

#### 方式1

方式1：通过 fork 创建子进程的方式可以实现，其他情况下不行。

当连接到来时，子进程、父进程都可以 `accept`, 这就是著名的“惊群”问题(thundering herd problem)。

NGINX 的 master/work 处理方法：

[Flow of an NGINX worker process](http://zimbra.imladris.sk/download/src/GNR-601/ThirdParty/nginx/docs/IMPLEMENTATION)

可以设置 ffd 的 close-on-exec flag 避免子进程继承 fd.

#### 方式2

方式2：我们都知道socket是网络上两个进程之间的双向通信链路， 即

socket = 《A进程的IP地址：端口号，B进程的IP地址：端口号》

那么有个问题就很有意思了，不同的进程可以监听在同一个IP地址:端口号么？

根据Unix网络编程中的知识可知，服务端监听一个端口会经历：

1、根据套接字类型(Ipv4,Ipv6等)创建套接字socket

2、将套接字bind绑定到具体的网络地址和端口号

3、调用listen开始在这个套接字上进行监听。

Unix提供了一个接口`setsockopt()`可以在bind之前设置套接字选项，其中就包括`REUSEADDR`这个选项，表明可以多个进程复用bind函数中指定的地址和端口号。

由此可知多个应用(进程)，包括同一个应用多次，都是可以绑定到同一个端口进行监听的。对应地C++、NET等高级语言也都提供了对应的接口。



从一些例子也可以看出，比如有时候你在服务器上执行netstat -ano可能会发现同一个应用程序在同一个端口上有多个监听，这是因为一些服务端应用程序可能会异常退出或者没有完全释放套接字，但是需要在重新启动时还能够再次监听同一个端口，所以需要能够具备重复监听同一个端口的能力，因此也出现上述情形。

## Bind one process to multiple port

### stackexchange [Bind one process to multiple ports?](https://unix.stackexchange.com/questions/128677/bind-one-process-to-multiple-ports)



### stackoverflow [Listen to multiple ports from one server](https://stackoverflow.com/questions/15560336/listen-to-multiple-ports-from-one-server)

## Binding multiple times to the same port

### stackoverflow [Binding multiple times to the same port](https://stackoverflow.com/questions/3695978/binding-multiple-times-to-the-same-port)





## Multiple processes listening on the same port

### superuser [Multiple processes listening on the same port; how is it possible?](https://superuser.com/questions/1267192/multiple-processes-listening-on-the-same-port-how-is-it-possible)





### stackoverflow [Can two applications listen to the same port?](https://stackoverflow.com/questions/1694144/can-two-applications-listen-to-the-same-port)