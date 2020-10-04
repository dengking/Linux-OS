# TCP segment of a reassembled PDU

在阅读cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html) 时，其中描述了这个问题:

> ![img](https://images2018.cnblogs.com/blog/1117030/201808/1117030-20180816144943928-2101697501.png)
>
> 如图所示，在抓包的时候，经常会看到[TCP segment of a reassembled PDU ] 字样的包，这个代表数据在传输层被分包了。也就是代表包大小大于MTU，此处放一下MTU与MSS区别：
>
> > MTU（Maximum Transmission Unit）最大传输单元，在TCP/IP协议族中，指的是IP数据报能经过一个物理网络的最大报文长度，其中包括了IP首部(从20个字节到60个字节不等)，一般以太网的MTU设为1500字节，加上以太帧首部的长度14字节，也就是一个以太帧不会超过1500+14 = 1514字节。
> >
> > MSS（Maximum Segment Size，最大报文段大小，指的是TCP报文（一种IP协议的上层协议）的最大数据报长度，其中不包括TCP首部长度。MSS由TCP链接的过程中由双方协商得出，其中SYN字段中的选项部分包括了这个信息。如果MSS+TCP首部+IP首部大于MTU，那么IP报文就会存在分片，如果小于，那么就可以不需要分片正常发送。
>
> 因此，出现这种现象的原因就是你调用一次send的时候，send的数据比 MSS 还要打，因此就被协议栈进行了分包。
>
> 顺便说一下，IP数据包的分片是通过flag字段和offset字段共同完成的。
>
> 从图中可以看到，第6个和第5个包是同一个TCP报文被分成了两个包。如果我们点开看的话，可以看到两个报文的ACK序号都一样，并且这些报文的Sequence Number都不一样，并且后一个Sequence Number为前一个Sequence Number加上前一个报文大小再加上1 。这也是判断reassembled 的方式。
>
> 点开第6个包，可以看到它将5和6的数据整合起来了。



下面是我解决这个问题的过程:

## What is PDU?

参见`Network\Theory\Network-protocol-model.md`。



## Disassemble and Reassemble

Disassemble 拆开

Reassemble 重新装配、重新集合

显然两者描述的是相反的过程。