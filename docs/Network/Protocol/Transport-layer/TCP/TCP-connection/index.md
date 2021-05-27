# 关于本章

本章讨论TCP connection相关的内容。



## What is TCP connection?

首先搞清楚TCP connection的本质。

在 wikipedia [Transmission Control Protocol#Network_function](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Network_function) 中已经描述了TCP connection的本质:

> At the transport layer, TCP handles all handshaking and transmission details and presents an abstraction of the network connection to the application typically through a [network socket](https://en.wikipedia.org/wiki/Network_socket) interface.

它描述了TCP connecting的本质，可以认为TCP network connection is an abstraction、

在 zhihu [TCP连接是什么?](https://www.zhihu.com/question/288930802) # [ 陶辉的回答](https://www.zhihu.com/question/288930802/answer/463957653) 中描述的更加明确: 

> 两台PC机器上有两个进程，通过2个端口逻辑上建立了通道。由于网络上消息是可以丢失的，可以无序的，可以多次重传的，所以这个通道的必要性就出现了：它确保消息是有序的、不会丢失的。而且TCP含有流量控制，防止瞬间网络风暴引发恶性循环。
>
> 而TCP连接纯粹是**虚拟**的，它只存在于两台**主机**间，网络中的路由器、交换机并不知情。