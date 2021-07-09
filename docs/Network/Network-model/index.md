# 关于本章

本章讨论首先讨论communication protocol，它是比network protocol更加宽泛的概念，然后讨论network protocol(网络的主要内容)。



## What is communication protocol?



### Communication protocol is a kind of language

从language的角度来看，[Communication protocol](https://en.wikipedia.org/wiki/Communication_protocol)是一种语言，它是通信多方的约定的沟通的语言。

### Protocol VS format

#### superuser [What are the general differences between a format and a protocol](https://superuser.com/questions/736401/what-are-the-general-differences-between-a-format-and-a-protocol) 

**A**: 

Format - applies to **files**

> NOTE: 参见`Programming\IO\File-IO\File-format\File-format`章节

Protocol - applies to **communications**

In both instances you are talking about the index of various bytes in a stream and what they are supposed to represent.

> NOTE: 这是两者的共同之处，关于stream，参见工程discrete的`Relation-structure-computation\Model\Stream`章节

**Protocol** can get more involved, as many protocols work in a "**request-response**" fashion where the client issues a **well-formed request**, and then a server responds with a **well-formed response**. So there may be different **schema** for request, response. Requests may change client or server "state" and thus the schema may be different again given a particular state.

> NOTE: protocol涉及到多方的参与，因此它比format考虑的问题要多得多

File formats are typically always following the same **schema** unless they are a different version, though they can be complex as well - later bytes in a file format may depend on earlier bytes (the .PST file format or the Windows Registry hive format, for example).

**A**: 

A **format** describes the **structure** of some data, whereas a **protocol** defines a procedure to handle this data. If you take TCP as an example, you have a definition of the ***format*** of a data packet, which tells you at which bit position a specified field like the checksum of a packet starts and ends, and the **protocol** defines that for opening a TCP connection you need three packets, one from client to server with the SYN-bit set, a second one from server to client with ACK- and SYN-bit set and a third one with ACK-bit set from client to server.

> NOTE: format仅仅描述了structure，关于file format，参见`Programming\IO\File-IO`章节。

### 如何评判protocol的好坏？

protocol的优点与缺点，以[Redis Protocol specification](https://redis.io/topics/protocol)为例进行说明。



## Network protocol

Network protocol是一种communication protocol，它将是本章探讨的主要内容。

本章内容主要是基于 [Internet protocol suite](https://en.wanweibaike.com/wiki-Internet_protocol_suite) 来组织的，我们需要学习目前network中，被广泛采用的、标准化的protocol(比如TCP/IP协议族)；除此之外，我们还需要学习如何来设计application protocol(应用层协议)，这将在`Application-protocol`章节中讨论。

### 转换协议: DNS、ARP、NAT

csdn [DNS与ARP区别](https://blog.csdn.net/qq_30242987/article/details/104759566)

相同：**都是将一个给定的输入实体转换为另一个实体，DNS将域名转换为IP，而ARP则是将IP转换为物理地址。**

异同：**两者的输入对象不一致，并且两者在网络层次结构所在的位置不同，DNS工作在应用层，ARP工作在网络层。**

baike [NAT](https://baike.baidu.com/item/nat/320024?fr=aladdin)

这种方法需要在专用网（私网IP）连接到因特网（公网IP）的路由器上安装NAT软件。装有NAT软件的路由器叫做NAT路由器，它至少有一个有效的外部全球IP地址（公网IP地址）。这样，所有使用本地地址（私网IP地址）的主机在和外界通信时，都要在NAT路由器上将其本地地址转换成全球IP地址，才能和因特网连接。

另外，这种通过使用少量的全球IP地址（公网IP地址）代表较多的私有IP地址的方式，将有助于减缓可用的IP地址空间的枯竭。在[RFC](https://baike.baidu.com/item/RFC/10718878) 2663中有对NAT的说明。



## 地址

### MAC 地址和 IP 地址分别有什么作用

**MAC 地址**是数据链路层和物理层使用的地址，是写在网卡上的物理地址。MAC 地址用来定义网络设备的位置。

**IP 地址**是网络层和以上各层使用的地址，是一种逻辑地址。IP 地址用来区别网络上的计算机。

