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



