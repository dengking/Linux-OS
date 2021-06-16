# TCP SEQ number and ACK number

本文对TCP的SEQ number、ACK number进行说明。

## What is  SEQ number and ACK number?

### Purpose

在`wikipedia-Transmission-Control-Protocol`的“Row3”节，有这样的说明: 

> Sequence number 和 Acknowledgment number是TCP实现在”4.4 Data transfer“中介绍的“Reliable transmission” 特性的关键。

在`wikipedia-Transmission-Control-Protocol`的Guide中，我们已经知道TCP协议要求所有的通信都是request-response的，即

> 每个request，都会收到一个response，这个response是用于acknowledge的，即对方告诉发送方: 收到了request，我们往往将其称之为ACK response，这样才算是完成了这个请求；


一个完整的请求才会导致SEQ number的增长，也就是说**发送方**是在收到ACK response的时候，才会更新它的SEQ number，或者说SEQ number的计算是基于完整的请求的，而不是基于它所发送的TCP segment( 其中也包括了ACK response)，这就是说TCP ACK segment是不会导致SEQ number的变动的，下面是简单的规则: 

1、对于SYN、FIN 请求，SEQ number增长1（这是比较特殊的，后面会解释这样做的原因）

2、对于其他请求，SEQ number增长playload长度



那该协议是如何实现response A是request A的response而不是request B的response呢？是使用sequence number和received sequence number吗？对一个endpoint而言，它的sequence number是单调递增的吗？

### 简介

miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html)的**Sequence Numbers**段有着非常好的介绍:

All bytes in a TCP connection are numbered, beginning at a randomly chosen **initial sequence number** (**ISN**). The SYN packets consume one **sequence number**, so actual data will begin at **ISN+1**. The sequence number is the byte number of the first byte of data in the TCP packet sent (also called a TCP segment). The acknowledgement number is the **sequence number** of the next byte the receiver expects to receive. The receiver ack'ing sequence number `x` acknowledges receipt of all data bytes less than (but not including) byte number `x`.

The sequence number is always valid. The acknowledgement number is only valid when the ACK flag is one. The only time the ACK flag is not set, that is, the only time there is not a valid acknowledgement number in the TCP header, is during the first packet of connection set-up.



## 思考: 为什么SYN和FIN会消耗一个序列号?

在cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html)中对这个问题进行了回答:

> 细心的同学可能会发现，为什么在建立连接的时候，发送的 SYN 包大小（payload）明明是0字节，但是接收端却返回 ACK = 1 ，还有断开连接的时候 FIN 包也被视为含有1字节的数据。
>
> 原因是 SYN 和 FIN 信号都是需要 acknowledgement 的，也就是你必须回复这个信号，如果它不占有一个字节的话，要如何判断你是回复这个信号还是回复这个信号之前的包呢？
>
> 例如：如果 FIN 信号不占用一个字节，回复 FIN 的 ack 包就可能被误认为是回复之前的数据包被重新发送了一次，第二次挥手无法完成，连接也就无法正常关闭了。

## 思考: 为什么SYN sequence number的初始值（ISN initialization sequence number）是一个随机值?

在cnblogs [TCP 中的Sequence Number](https://www.cnblogs.com/JenningsMao/p/9487252.html)中对这个问题进行了回答:

> 参考[TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)
>
> ISN是不能hard code的，不然会出问题的——比如：如果连接建好后始终用1来做ISN，如果client发了30个segment过去，但是网络断了，于是 client重连，又用了1做ISN，但是之前连接的那些包到了，于是就被当成了新连接的包，此时，client的Sequence Number 可能是3，而Server端认为client端的这个号是30了。全乱了。[RFC793](http://tools.ietf.org/html/rfc793)中说，ISN会和一个假的时钟绑在一起，这个时钟会在每4微秒对ISN做加一操作，直到超过2^32，又从0开始。这样，一个ISN的周期大约是4.55个小时。因为，我们假设我们的TCP Segment在网络上的存活时间不会超过Maximum Segment Lifetime（缩写为MSL – [Wikipedia语条](http://en.wikipedia.org/wiki/Maximum_Segment_Lifetime)），所以，只要MSL的值小于4.55小时，那么，我们就不会重用到ISN。

## TODO: 思考: SEQ number overflow？

voidcn [TCP序列号的最大值](http://www.voidcn.com/article/p-gccvxxfz-byo.html)





## See also

stackoverflow [TCP: How are the seq / ack numbers generated?](https://stackoverflow.com/questions/692880/tcp-how-are-the-seq-ack-numbers-generated)

stackoverflow [TCP Sequence Number](https://stackoverflow.com/questions/10452855/tcp-sequence-number)

firewall [TCP Sequence & Acknowledgement Numbers - Section 2](http://www.firewall.cx/networking-topics/protocols/tcp/134-tcp-seq-ack-numbers.html)