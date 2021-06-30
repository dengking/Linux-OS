# `epoll`的实现原理

## 参考文章

1、cnblogs [为什么人们总是认为epoll 效率比select高 # epoll原理概述](https://www.cnblogs.com/codestack/p/13393658.html) 

比较好的概述，但是并不深入，有些地方是比较含糊的，便于掌握大致原理

2、idndx [The Implementation of epoll](https://idndx.com/the-implementation-of-epoll-1/) 系列

源代码级别的解读s

## cnblogs [为什么人们总是认为epoll 效率比select高 # epoll原理概述](https://www.cnblogs.com/codestack/p/13393658.html) 

> NOTE: 
>
> 1、epoll是基于中断回调的

调用**epoll_create**时，做了以下事情：

1、内核帮我们在`epoll`文件系统里建了个file结点；

2、在内核cache里建了个**红黑树**用于存储以后`epoll_ctl`传来的socket；

3、建立一个list链表，用于存储**准备就绪**的事件。

调用**epoll_ctl**时，做了以下事情：

1、把socket放到`epoll`文件系统里file对象对应的红黑树上；

2、给内核中断处理程序注册一个回调函数，告诉内核，如果这个句柄的中断到了，就把它放到准备就绪list链表里。

调用**epoll_wait**时，做了以下事情：

观察list链表里有没有数据。有数据就返回，没有数据就sleep，等到timeout时间到后即使链表没数据也返回。而且，通常情况下即使我们要监控百万计的句柄，大多一次也只返回很少量的准备就绪句柄而已，所以，`epoll_wait`仅需要从内核态copy少量的句柄到用户态而已。

