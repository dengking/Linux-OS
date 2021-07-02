# IO event and IO multiplexing

1、IO data structure: buffer

当recv buffer中有数据的时候，就是readable；

当send buffer中有发送空间的时候，就是writable；

2、往往是双方进行通信的时候，才会涉及

## 官方说明文档

在下面文章中，对此进行了介绍:

一、[socket(7) Linux Programmer's Manual](http://man7.org/linux/man-pages/man7/socket.7.html)  

其中的内容是以 [poll(2)](https://man7.org/linux/man-pages/man2/poll.2.html)、[select(2)](https://man7.org/linux/man-pages/man2/select.2.html) 为例进行说明的

二、[epoll_ctl(2) — Linux manual page](http://man7.org/linux/man-pages/man2/epoll_ctl.2.html)

其中描述了epoll的IO event



## 相关章节

