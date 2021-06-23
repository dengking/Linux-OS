# Reliable UDP



## wanweibaike [Reliable User Datagram Protocol](https://en.wanweibaike.com/wiki-Reliable%20User%20Datagram%20Protocol)

In [computer networking](https://en.wanweibaike.com/wiki-Computer_network), the **Reliable User Datagram Protocol** (**RUDP**) is a [transport layer](https://en.wanweibaike.com/wiki-Transport_layer) [protocol](https://en.wanweibaike.com/wiki-Communications_protocol) designed at [Bell Labs](https://en.wanweibaike.com/wiki-Bell_Labs) for the [Plan 9](https://en.wanweibaike.com/wiki-Plan_9_from_Bell_Labs) [operating system](https://en.wanweibaike.com/wiki-Operating_system). It aims to provide a solution where [UDP](https://en.wanweibaike.com/wiki-User_Datagram_Protocol) is too primitive(原始) because guaranteed-order [packet](https://en.wanweibaike.com/wiki-Packet_(information_technology)) delivery is desirable, but [TCP](https://en.wanweibaike.com/wiki-Transmission_Control_Protocol) adds too much complexity/overhead. In order for RUDP to gain higher [quality of service](https://en.wanweibaike.com/wiki-Quality_of_service_requirements), RUDP implements features that are similar to TCP with less overhead.

> NOTE: 
>
> 一、诞生时间是比较早的
>
> 二、"too primitive"的意思是UDP太弱了，不符合需求
>
> 三、显然 RUDP 是介于 UDP 和 TCP 之间的

### Implementations

In order to ensure quality, it extends UDP by means of adding the following features:

1、Acknowledgment of received packets

2、Windowing and [flow control](https://en.wanweibaike.com/wiki-Flow_control_(data))

3、Retransmission of lost packets

4、Over buffering (Faster than real-time streaming)

> NOTE: 
>
> 一、接收了部分TCP的特性

RUDP is not currently a formal standard, however it was described in an [IETF](https://en.wanweibaike.com/wiki-Internet_Engineering_Task_Force) [internet-draft](http://tools.ietf.org/html/draft-ietf-sigtran-reliable-udp) in 1999. It has not been proposed for standardization.

## sfu [Reliable Data Transfer Over UDP](https://coursys.sfu.ca/2017sp-cmpt-471-d1/pages/Prj2/view)



## zhihu [UDP如何实现可靠传输？](https://www.zhihu.com/question/283995548?sort=created)

## zhihu [如何实现可靠UDP传输](https://zhuanlan.zhihu.com/p/129218784)

## zhihu [RUDP传输那些事儿](https://zhuanlan.zhihu.com/p/30770889)

## zhihu [不为人知的网络编程(七)：如何让不可靠的UDP变的可靠？](https://zhuanlan.zhihu.com/p/32469813)

## github [dulalsaurab](https://github.com/dulalsaurab)/**[Reliable-data-transfer-using-UDP](https://github.com/dulalsaurab/Reliable-data-transfer-using-UDP)**



