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

本层的**PDU**是由下层的**SDU**大小决定的，所以一直往下走就到了**数据链路层**，那么上次传递过来的单个PDU不能超过链路层的SDU，而链路层的PDU叫做帧，在以太网中它的**MTU**是1500，所以上层传递过来的单个PDU不能超过1500字节，IP首部站20个字节，TCP首部占20个字节，那由此得出TCP层的SDU为1460字节（也叫做MSS，最大消息长度），PDU为1480字节；IP层SDU为1480而PDU为1500.

> NOTE: 
>
> 一、MTU 和 SDU 貌似是相同的概念
>
> 二、上面这段话中的MSS和下面的MSS是不同的

### TCP MSS

TCP的MSS不是固定的它受对端影响，在TCP传输中MSS是通信双方协商而来的。下面看一下不同链路的MTU大小

| 数据链路   | MTU bytes | 总长度 bytes |
| ---------- | --------- | ------------ |
| IPv4       | 65535     |              |
| IPv6       | 65575     |              |
| 以太网     | 1500      | 1518         |
| FDDI       | 4352      | 4500         |
| IEEE 802.3 | 1492      | 1581         |
| PPPoE      | 1492      |              |

> NOTE: 
>
> 一、上述MTU bytes是指最大的值

**传输层**本身是没有长度限制的，但是在TCP首部的**MSS选项**中是一个16位字段最大值为65535字节，IP层也是是65535字节，所以它俩很合适，只是受到链路层影响才会导致传输层消息要分段以及IP报文要分片。因为以太网默认MTU1500，如果真有一个65535的IP报文的话那么它显然无法封装到单个帧里，所以就需要进行切割。这种切割可以在发送端完成也可以在传送过程中完成（路由器），但是重组肯定是在接收端。所以TCP/IP为了提高效率尽量避免IP分片和重组，所以TCP就根据MSS和MTU限定每个传输层的PDU大小，这样每一个PDU就是一个完整的PDU在传送过程中不会再被切割，接收端的传输层收到这些段之后进行数据重组，实际上MSS的目的也就是为了告诉对端我的重组缓冲区大小是多少。所以这也就是为什么在传输层有一个MSS的东西存在了，一句话就是向对端TCP告知对端在每个分段中能发送的最大TCP数据量，这个MSS是在双方建立TCP连接时协商出来的。MSS经常设置成MTU减去IP和TCP首部的固定长度，在以太网中是1460字节。

总结来看，MTU是死的由具体链路决定，而MSS是不固定的通过协商而来。但两个通信双方协商出来的MSS不会大于路径MTU(通信双发路径中最小的MTU，因为通信双方走的路可能不同，也就是A到B的路径与B到A的路径不一定相同)。

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

