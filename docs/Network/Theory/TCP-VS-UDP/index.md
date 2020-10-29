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



## stackoverflow [can one call of recv() receive data from 2 consecutive send() calls?](https://stackoverflow.com/questions/6089855/can-one-call-of-recv-receive-data-from-2-consecutive-send-calls)



[A](https://stackoverflow.com/a/6089932)

`TCP` is a **stream oriented** protocol. Not message / record / chunk oriented. That is, all that is guaranteed is that if you send a stream, the bytes will get to the other side in the order you sent them. There is no provision(规定) made by RFC 793 or any other document about the number of segments / packets involved.

This is in stark(完全) contrast with `UDP`. As @R.. correctly said, in `UDP` an entire message is sent in one operation (notice the change in terminology: `message`). Try to send a giant message (several times larger than the MTU) with TCP ? It's okay, it will split it for you.

> NOTE: MTU即[Maximum Transmission Unit](http://en.wikipedia.org/wiki/Maximum_transmission_unit)，

When running on local networks or on localhost you will certainly notice that (generally) `one send == one recv`. Don't assume that. There are factors that change it dramatically. Among these

- Nagle
- Underlying MTU
- Memory usage (possibly)
- Timers
- Many others

Of course, not having a correspondence between an a `send` and a `recv` is a nuisance and you can't rely on `UDP`. That is one of the reasons for `SCTP`. `SCTP` is a really really interesting protocol and it is **message-oriented**.

Back to `TCP`, this is a common nuisance. An equally common solution is this:

- Establish that all packets begin with a fixed-length sequence (say 32 bytes)
- These 32 **bytes** contain (possibly among other things) the size of the **message** that follows
- When you read any amount of data from the socket, add the data to a buffer specific for that connection. When 32 **bytes** are reached, read the length you still need to read until you get the message.

It is really important to notice how there are really no messages on the wire, only bytes. Once you understand it you will have made a giant leap towards writing network applications.

