# TCP data transfer

本章讨论TCP数据发送相关内容。



## wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) # [4.4 Data transfer](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Data_transfer)



> NOTE: TCP数据传输的核心特性

The Transmission Control Protocol differs in several key features from the [User Datagram Protocol](https://en.wikipedia.org/wiki/User_Datagram_Protocol):

| features                       | 注解                                          |
| ------------------------------ | --------------------------------------------- |
| Ordered data transfer          | 在下面的“Reliable transmission”会进行详细介绍 |
| Retransmission of lost packets | 简单来说就是“补漏”                            |
| Error-free data transfer       | 无错传输                                      |
| Flow control                   | 流控                                          |
| Congestion control             | 拥塞控制                                      |

> NOTE: 下面将上述Ordered data transfer、Retransmission of lost packets、Error-free data transfer统称为Reliable transmission。



### [Reliable transmission](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Reliable_transmission)

> NOTE: TCP是否会等收到ACK后，才传下一个segment？



**Reliability** is achieved by the **sender** detecting lost data and retransmitting it. TCP uses two primary techniques to identify loss:

- Retransmission timeout (abbreviated as RTO) 
- Duplicate cumulative acknowledgements (DupAcks).



#### Dupack-based retransmission

> NOTE: 

#### Timeout-based retransmission

### [Error detection](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Error_detection)



## Stream oriented

TODO: 需要添加对stream的说明:  stream是一种非常强大的抽象。





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

#### csdn [TCP协议如何来保证传输的可靠性和数据的顺序性](https://blog.csdn.net/wang664626482/article/details/52091248): 

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



