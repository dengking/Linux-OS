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



## Implementation

我们需要考虑 TCP data transfer的核心特性的实现。

