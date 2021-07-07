# Event-driven concurrent server

本章讨论Linux中，实现一个event-driven concurrent server。

涉及到非常多的主题:



## 网络编程

1、如何设计protocol

2、如何解决`TIME_WAIT`过多问题

3、如何解决Thundering-Herd-problem

## 并发模型

在下面文章中，对此进行了讨论:

1、kegel [The C10K problem](http://www.kegel.com/c10k.html)

2、lwn [The SO_REUSEPORT socket option](https://lwn.net/Articles/542629/) 

3、zhihu [如何深刻理解reactor和proactor？](https://www.zhihu.com/question/26943938) # [小林coding的回答](https://www.zhihu.com/question/26943938/answer/1856426252)

非常好的文章，将可能的并发模型总结得非常好。

大多数都是使用:

1、reactor

2、master worker



### multiple thread



### multiple process



## case

### Nginx 

### Memcached

### Redis

### Initd

###  
