# PDU、MTU、SDU

## cnblogs [MTU MSS PDU SDU](https://www.cnblogs.com/rexcheny/p/9572811.html)

> NOTE: 
>
> 一、这篇文章把这几个概念总结的非常好

首先要说两个概念：

### PDU

PDU：协议数据单元，计算机网络各层对等实体间交换的单位叫做PDU，不同层的PDU名称不同

| 层     | 名称           |
| ------ | -------------- |
| 应用层 | 数据           |
| 传输层 | 段 segment     |
| 网络层 | 数据包 package |
| 链路层 | 帧 frame       |
| 物理层 | 比特 bit       |



### SDU

SDU：服务数据单元，它是指PDU的实际载荷（payload）

### PDU和SDU有什么关系呢？

在每一层都有PDU和SDU，在本层中SDU加上额外协议信息构成本层的PDU，行话是:

1、同一层内的SDU是本层PDU的静荷载（payload）

2、不同层之间，上层的PDU是下层的SDU。

在上层向下层传输数据的时候，上层使用下层提供的数据接口给下层传递数据，而不同层之间的PDU转换是由下层完成的（这个转换是说对上一层传递过来的PDU进行包装变成本层的PDU也就是变成符合本层协议对数据的格式要求）。如果上层PDU超过下层SDU，那么本层就要把数据 切割成若干适合的片段再给下层（对本层的SDU切割，然后每个切割后的SDU加上本层的协议信息构成一个本层的PDU传递给下层，本层的PDU大小必须不能大于下一层的SDU）。

> NOTE: 
>
> fragmentation分片

![img](./PDU-SDU.png)

本层的**PDU**是由下层的**SDU**大小决定的，所以一直往下走就到了**数据链路层**，那么上次传递过来的单个PDU不能超过链路层的SDU，而链路层的PDU叫做帧，在以太网中它的MTU是1500，所以上层传递过来的单个PDU不能超过1500字节，IP首部站20个字节，TCP首部占20个字节，那由此得出TCP层的SDU为1460字节（也叫做MSS，最大消息长度），PDU为1480字节；IP层SDU为1480而PDU为1500.





## Protocol data unit/PDU

一个非常重要的概念就是protocol data unit，PDU，即“协议数据单元”，它是描述下一节Mechanism的前提。它符合在文章《Unit》中提出的思想的。

### wikipedia [Protocol data unit](https://en.wikipedia.org/wiki/Protocol_data_unit)

#### Example: PDU of layer of OSI model

| layer | name                                                         | PDU                                                          |
| ----- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 4     | [transport layer](https://en.wikipedia.org/wiki/Transport_layer) | TCP [segment](https://en.wikipedia.org/wiki/Packet_segment) or UDP datagram |
| 3     | [network layer](https://en.wikipedia.org/wiki/Network_layer) | [packet](https://en.wikipedia.org/wiki/Network_packet)       |
| 2     | [data link layer](https://en.wikipedia.org/wiki/Data_link_layer) | [frame](https://en.wikipedia.org/wiki/Frame_(networking))    |
| 1     | [physical layer](https://en.wikipedia.org/wiki/Physical_layer) | [bit](https://en.wikipedia.org/wiki/Bit) or, more generally, [symbol](https://en.wikipedia.org/wiki/Symbol_(data)). |



### [RFC 1122](https://tools.ietf.org/html/rfc1122)



下面是[RFC 1122](https://tools.ietf.org/html/rfc1122)中给出的描述

| terminology | explanation                                                  |
| ----------- | ------------------------------------------------------------ |
| Segment     | A **segment** is the unit of end-to-end transmission in the<br/>**TCP protocol**. A segment consists of a **TCP header** followed<br/>by **application data**. A segment is transmitted by<br/>encapsulation inside an **IP datagram**. |
| Message     | In this description of the lower-layer protocols, <br/>a **message** is the unit of transmission in a **transport layer protocol**. <br>In particular, a TCP segment is a message. <br/>A message consists of a **transport protocol header** followed<br/>by application protocol data. To be transmitted end-to-end through the Internet, <br/>a message must be encapsulated inside a **datagram**. |
| IP Datagram | An IP datagram is the unit of end-to-end transmission in<br/>the IP protocol. An IP datagram consists of an IP header<br/>followed by transport layer data, i.e., of an IP header<br/>followed by a message. |
| Packet      | A packet is the unit of data passed across the interface<br/>between the internet layer and the link layer. It<br/>includes an IP header and data. A packet may be a<br/>complete IP datagram or a fragment of an IP datagram. |
| Frame       | A frame is the unit of transmission in a link layer<br/>protocol, and consists of a link-layer header followed by<br/>a packet. |

![](./Unit-of-layer.png)



### Max length of PDU

前面介绍了PDU，与它相关的另外一个问题是：它的最大长度；





## MTU

### Example: PDU of layer of OSI model

| layer | name                                                         | PDU                                                          | max length                                                   |
| ----- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 4     | [transport layer](https://en.wikipedia.org/wiki/Transport_layer) | TCP [segment](https://en.wikipedia.org/wiki/Packet_segment) or UDP datagram | [Maximum segment size](https://en.wikipedia.org/wiki/Maximum_segment_size) |
| 3     | [network layer](https://en.wikipedia.org/wiki/Network_layer) | [packet](https://en.wikipedia.org/wiki/Network_packet)       | [Maximum transmission unit](https://en.wikipedia.org/wiki/Maximum_transmission_unit) |
| 2     | [data link layer](https://en.wikipedia.org/wiki/Data_link_layer) | [frame](https://en.wikipedia.org/wiki/Frame_(networking))    |                                                              |
| 1     | [physical layer](https://en.wikipedia.org/wiki/Physical_layer) | [bit](https://en.wikipedia.org/wiki/Bit) or, more generally, [symbol](https://en.wikipedia.org/wiki/Symbol_(data)). |                                                              |



## microsoft [The default MTU sizes for different network topologies](https://support.microsoft.com/en-us/topic/the-default-mtu-sizes-for-different-network-topologies-b25262c5-d90f-456d-7647-e09192eeeef4)

The maximum transfer unit (MTU) specifies the maximum transmission size of an interface. A different MTU value may be specified for each interface that TCP/IP uses. The MTU is usually determined by negotiating with the lower-level driver. However, this value may be overridden.

### More Information

Each media type has a maximum frame size. The **link layer** is responsible for discovering this MTU and reporting the MTU to the protocols above the **link layer**. The protocol stack may query **Network Driver Interface Specification (NDIS) drivers** for the local MTU. Upper-layer protocols such as TCP use an interface's MTU to optimize packet sizes for each medium.

If a network adapter driver, such as an asynchronous transfer mode (ATM) driver, uses local area network (LAN) emulation mode, the driver may report that its MTU is larger than expected for that media type. For example, the network adapter may emulate Ethernet but report an MTU of 9180 bytes. Windows accepts and uses the MTU size that the adapter reports even when the MTU size exceeds the usual MTU size for a particular media type.


The following table summarizes the default MTU sizes for different network media.



Network MTU (bytes)
\-------------------------------
16 Mbps Token Ring 17914
4 Mbps Token Ring 4464
FDDI 4352
**Ethernet 1500**
IEEE 802.3/802.2 1492
PPPoE (WAN Miniport) 1480
X.25 576

