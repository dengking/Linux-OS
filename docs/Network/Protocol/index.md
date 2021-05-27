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

本章内容主要是基于 [Internet protocol suite](https://en.wanweibaike.com/wiki-Internet_protocol_suite) 来组织的，我们需要学习目前network中，被广泛采用的、标准化的protocol(比如TCP/IP协议族)；除此之外，我们还需要学习如何来设计application protocol(应用层协议)，这将在`./Application-protocol`章节中讨论。

