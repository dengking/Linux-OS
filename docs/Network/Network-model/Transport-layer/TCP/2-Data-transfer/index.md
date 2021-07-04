# TCP data transfer

本章讨论TCP数据发送相关内容。



## wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) # [4.4 Data transfer](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Data_transfer)



## Implementation综述

参考:

1) csdn [TCP如何保证消息顺序以及可靠性到达](https://blog.csdn.net/dccmxj/article/details/52103800)

2) csdn [【网络】TCP连接的顺序问题、丢包问题、流量控制、拥塞控制问题](https://blog.csdn.net/vict_wang/article/details/88696699)

## Ordered data transfer

TCP data transfer的一个非常重要的feature是: ordered，需要注意的是，TCP只能够保证在同一个连接内的ordered，两个连接之间，TCP无法保证。

### Implementation

我们需要考虑 TCP data transfer的ordered特性的实现。

#### csdn [TCP协议如何来保证传输的可靠性和数据的顺序性](https://blog.csdn.net/wang664626482/article/details/52091248): 

**保证数据的顺序性**：
既然TCP报文段作为IP数据报来传输，而IP数据报的到达可能会失序，因此TCP报文段的到达也可能会失序。如果必要，TCP将对收到的数据进行**重新排序**，将收到的数据以正确的顺序交给应用层。 (**对失序数据进行重新排序，然后才交给应用层**)

#### See also

csdn [关于同一条TCP链接数据包到达顺序的问题](https://blog.csdn.net/LSKCGH/article/details/105007013)

我刚开始也犯了和这篇文章的作者相同的错误。



## Reliable data transfer

### csdn [TCP协议如何来保证传输的可靠性和数据的顺序性](https://blog.csdn.net/wang664626482/article/details/52091248): 

TCP提供一种面向连接的、可靠的字节流服务。

面向连接：意味着两个使用TCP的应用（通常是一个客户和一个服务器）在彼此交换数据之前必须先建立一个TCP连接。在一个TCP连接中，仅有两方进行彼此通信。广播和多播不能用于TCP。 应用数据被分割成TCP认为最适合发送的分组，A为发送方，B为接收方。**可靠传输原理**是以下两个协议：

1、**停止等待协议**：每发送完一个分组，就停止发送，等待对方的确认，收到确认后再发送下一个分组。

(1)**出现差错**，采用**超时重传**功能，若B检测到收到的分组有错，就丢弃此分组，什么也不做(TCP将保持它首部和数据的检验和。这是一个端到端的检验和，目的是检测数据在传输过程中的任何变化)，A在发送后就设置一个超时定时器，若超过定时器时间还没有收到确认，就重新发送此分组（注意：A发送完一个分组后必须保留副本，为超时重传使用；分组和确认分组都要进行编号；超时重传时间必须大于一个往返时间）；

(2)**确认丢失和确认迟到**：B发送的确认丢失或迟到后，A过了超时定时器的时间，就重新发送分组，B丢弃这个分组，同时向A发送确认；

上述的确认和重传机制，称为自动重传请求ARQ协议；

2、**连续ARQ协议**：利用发送窗口，位于发送窗口内的所有分组都可以连续发送出去，而不需要等待对方的确认。A每收到一个确认，就把发送窗口向前滑动一个分组的位置。B采用累积确认方式，**对按序到达的最后一个分组发送确认**，就表示到这个分组之前的所有分组都收到了。



## Flow control

流量控制



## Congestion control

拥塞控制



## Stream oriented and TCP data transfer

TODO: 需要添加对stream的说明:  stream是一种非常强大的抽象。

Stream-oriented是TCP的核心特性，它决定了TCP的通信是无**消息保护边界**的(面向流的通信是无**消息保护边界**的)，这样，**接收端**必须提供科学的拆包机制。

> NOTE: 上述"面向流的通信是无**消息保护边界**的"是我在阅读csdn [Socket TCP粘包、多包和少包, 断包](https://blog.csdn.net/pi9nc/article/details/17165171)时，其中的论述。
>
> 关于**消息边界**，参见`Network\Theory\Message-boundary`。



### zhidao [tcp每一次send动作，其发送的字节都是按顺序到达receive端的吗?](https://zhidao.baidu.com/question/542313216.html): 

因为TCP连接为可靠、有序的流式通道，bai故传输的数据不会丢失或乱序。

但是，如果发送比较大的数据块（例如65535字节），接收端可能分几次收到数据，即每次recv()收到一部分数据。产生这一特性的原因是：TCP协议栈通常使用收发窗口协商机制高效传递数据，每次实际发送的数据量受窗口大小控制（窗口大小与网络状况、协议栈接收空间等因素有关）。

同样，如果连续多次发送几组小数据（比如每次几个字节），接收端可能一次性收到所有数据。这是TCP协议栈另外一个特性，即对上层数据进行拼接（**粘包**）以减少网络交换数据报文的频率，以减少双方交互等待次数，提高网络吞吐效率。虽然这个特性可通过socket选项控制，但在比较复杂的网络环境下，发送方分多次送出的小报文仍可能被中间路由设备拼接后一次性发出。

鉴于以上特性，成熟的TCP通讯设计通常还要引入另外的数据封装机制，在应用层给数据增加包头，接收端根据**包头**对数据进行组装（可使用环形队列等算法），以保证通讯数据的逻辑连贯性。

其实除了TCP协议，还有其他的可靠通讯协议。这些协议有些基于数据流（类似TCP），也有的基于数据包式（类似UDP）。这类协议有时作为系统级组件提供，但更多是以应用层扩展库形式存在，通常是在UDP协议或裸IP层面进行封装，有需要的话可自行搜索这方面资源。





### stackoverflow [can one call of recv() receive data from 2 consecutive send() calls?](https://stackoverflow.com/questions/6089855/can-one-call-of-recv-receive-data-from-2-consecutive-send-calls)



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



