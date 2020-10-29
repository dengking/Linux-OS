# TCP VS UDP



## 综述

|              | TCP             | UDP              |
| ------------ | --------------- | ---------------- |
| **有无连接** | 面向连接        | 非连接           |
| **传输速度** | 慢              | 快               |
| **有序性**   | 保证数据顺序    | 不保证           |
| **可靠性**   | 保证数据正确性  | 可能丢包         |
| **资源占用** | 要求多          | 要求少           |
|              | stream-oriented | message-oriented |

参考:

1) csdn [TCP协议和UDP协议的区别 (有无链接，传输速度，有序无序，可靠性，对资源的占用)](https://blog.csdn.net/zjtzjt108/article/details/51093808)

2) networking-forum [What does stream-oriented and message oriented terms mean?](http://www.networking-forum.com/viewtopic.php?t=29253#p197510)



## csdn [Socket TCP粘包、多包和少包, 断包#为什么TCP 会粘包](https://blog.csdn.net/pi9nc/article/details/17165171) 



- TCP（transport control protocol，传输控制协议）是面向连接的，面向流的，提供高可靠性服务。收发两端（客户端和服务器端）都要有一一成对的socket，因此，发送端为了将多个发往接收端的包，更有效的发到对方，使用了优化方法（Nagle算法），将多次间隔较小且数据量小的数据，合并成一个大的数据块，然后进行封包。这样，接收端，就难于分辨出来了，必须提供科学的拆包机制。 **即面向流的通信是无消息保护边界的。**

- UDP（user datagram protocol，用户数据报协议）是无连接的，面向消息的，提供高效率服务。不会使用块的合并优化算法，, 由于UDP支持的是一对多的模式，所以接收端的skbuff(套接字缓冲区）采用了链式结构来记录每一个到达的UDP包，在每个UDP包中就有了消息头（消息来源地址，端口等信息），这样，对于接收端来说，就容易进行区分处理了。 **即面向消息的通信是有消息保护边界的。**



## TCP stream-oriented VS  UDP message-oriented

### networking-forum. [What does stream-oriented and message oriented terms mean?](http://www.networking-forum.com/viewtopic.php?t=29253#p197510)

Hi,
As we know TCP is a **stream oriented protocol** and UDP is a **message-oriented protocol** I want to know what that really means ? What are the advantages of both ? Someone pls explain these terms.



#### A1

 [http://en.wikipedia.org/wiki/Stream_Con ... -streaming](http://en.wikipedia.org/wiki/Stream_Control_Transmission_Protocol#Message-based_multi-streaming)

explains it all  



#### A2

So, TCP receives the stream of bytes from **application layer protocols** and divide it in to **segments** and pass it to **IP**. But **UDP** receives already divided or grouped bytes of data from **application protocols** and add **UDP headers** which will become **Datagram** and send it to IP Is that correct ?

If it is correct, then **application layers** has the burden of dividing the streams of data in to messages when they run on top of UDP.







## APUE 16.2 Socket Descriptors

在APUE的16.2 Socket Descriptors中，对TCP和UDP之间差异的解释是非常到位的，是非常具有参考价值的；



