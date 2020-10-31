# TCP segment of a reassembled PDU

在阅读cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html) 时，其中描述了这个问题:

> ![img](https://images2018.cnblogs.com/blog/1117030/201808/1117030-20180816144943928-2101697501.png)
>
> 如图所示，在抓包的时候，经常会看到[TCP segment of a reassembled PDU ] 字样的包，这个代表数据在传输层被分包了。也就是代表包大小大于MTU，此处放一下MTU与MSS区别：
>
> > MTU（[Maximum Transmission Unit](https://en.wikipedia.org/wiki/Maximum_transmission_unit)）最大传输单元，在TCP/IP协议族中，指的是IP数据报能经过一个物理网络的最大报文长度，其中包括了IP首部(从20个字节到60个字节不等)，一般以太网的MTU设为1500字节，加上以太帧首部的长度14字节，也就是一个以太帧不会超过1500+14 = 1514字节。
> >
> > MSS（[Maximum Segment Size](https://en.wikipedia.org/wiki/Maximum_segment_size)，最大报文段大小，指的是TCP报文（一种IP协议的上层协议）的最大数据报长度，其中不包括TCP首部长度。MSS由TCP链接的过程中由双方协商得出，其中SYN字段中的选项部分包括了这个信息。如果**MSS+TCP首部+IP首部大于MTU**，那么IP报文就会存在分片，如果小于，那么就可以不需要分片正常发送。
>
> 因此，出现这种现象的原因就是你调用一次send的时候，send的数据比 MSS 还要打，因此就被协议栈进行了分包。
>
> 顺便说一下，IP数据包的分片是通过flag字段和offset字段共同完成的。
>
> 从图中可以看到，第6个和第5个包是同一个TCP报文被分成了两个包。如果我们点开看的话，可以看到两个报文的ACK序号都一样，并且这些报文的Sequence Number都不一样，并且后一个Sequence Number为前一个Sequence Number加上前一个报文大小再加上1 。这也是判断reassembled 的方式。
>
> 点开第6个包，可以看到它将5和6的数据整合起来了。

关于IP报文的分片，参见[IP fragmentation](https://en.wikipedia.org/wiki/IP_fragmentation)。

在下面文章中，也对这个问题进行了探讨:

superuser [TCP segment of a reassembled PDU](https://superuser.com/questions/255157/tcp-segment-of-a-reassembled-pdu) # [A](https://superuser.com/a/255160)

> A "PDU" is a "Protocol Data Unit." One unit of information being transferred in accordance with a given protocol (e.g., "login USERNAME very-long-base64-encoded-authentication-data" then wait for server to respond) will be disassembled into many packets (smaller pieces) if it's too large to fit in one packet (or segment in this case).

This is normal and is just TCP/IP working as designed.

osqa-ask.wireshark [TCP segment of a reassembled PDU ?](https://osqa-ask.wireshark.org/questions/58186/tcp-segment-of-a-reassembled-pdu) # [A](https://osqa-ask.wireshark.org/questions/58186/tcp-segment-of-a-reassembled-pdu/58197)

> It means that
>
> - Wireshark/TShark thinks it knows what protocol is running atop TCP in that TCP segment;
> - that TCP segment doesn't contain all of a "protocol data unit" (PDU) for that higher-level protocol, i.e. a packet or protocol message for that higher-level protocol, and doesn't contain the last part of that PDU, so it's trying to reassemble the multiple TCP segments containing that higher-level PDU.
>
> For example, an HTTP response with a lot of data in it won't fit in a single TCP segment on most networks, so it'll be split over multiple TCP segments; all but the last TCP segment will be marked as "TCP segment of a

## What is PDU?

参见`Network\Theory\Network-protocol-model.md`。









