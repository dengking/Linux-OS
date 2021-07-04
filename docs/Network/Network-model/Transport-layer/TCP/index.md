# TCP

下面是参考的内容:

| 推荐阅读顺序 | 文章                                                         |                                                              |
| ------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1            | miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html) | 非常精简，但是主要内容都涵盖了                               |
| 2            | coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)、[TCP 的那些事儿（下）](https://coolshell.cn/articles/11609.html) | 内容非常详实、全面                                           |
| 3            | wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) |                                                              |
| 4            | nmap [TCP/IP Reference](https://nmap.org/book/tcpip-ref.html) | 提供了非常好的图示，内容不多                                 |
| 5            | book [TCP/IP Guid](http://www.tcpipguide.com/index.htm)      | 可以[在线免费阅读](http://www.tcpipguide.com/free/index.htm) |
|              |                                                              |                                                              |



## Guide

在阅读前，需要建立起如下概念/观念，便于理解: 

1) TCP采用的是: **请求-响应** 模型

> 原文中并没有说明此，这是我自己添加的

每个request，都会收到一个response，这个response是用于acknowledge的，即接收方告诉发送方: 收到了request，我们往往将其称之为**ACK response**，这样才算是完成了这个请求；

对于ACK，是不需要再ACK的，否则就会导致无限的递归下去；

2) TCP是全双工通信模式:

“全双工”意味着一个TCP session有两个部分组成，意味着存在着half的问题（half close、half open）。

3) 构建TCP的**活动图**(活动图是借用的软件工程中的概念): 

可以采用如下收录来进行构建:

TCP的三个阶段: 这是对TCP的lifetime的划分，参见 "4 Protocol operation";

TCP的操作: 每个阶段的会执行相应的操作，参见 "4 Protocol operation";

TCP的状态: TCP是有一定状态的，TCP操作会触发状态的转换，因此我们可以构建状态转换图，参见"4 Protocol operation";

4) TCP的核心特性以及对应的实现方式

## Terminology

endpoint: 一个TCP有两个endpoint

session: 一个TCP session



## 内容概述

TCP是一个复杂的协议，涉及非常多的内容，本章的目录结构是参考 wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) 的目录结构 

首先是介绍TCP非常好的文章:

| 章节                                      | 内容                                                         |
| ----------------------------------------- | ------------------------------------------------------------ |
| `Course-miami-TCP-in-a-nutshell`          | miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html) |
| `coolshell-TCP的那些事儿`                 | coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)、[TCP 的那些事儿（下）](https://coolshell.cn/articles/11609.html) |
| `wikipedia-Transmission-Control-Protocol` | wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) |

然后介绍TCP中的一些概念:

| 章节                           | 内容                         |
| ------------------------------ | ---------------------------- |
| `TCP-connection`               | 解释TCP链接                  |
| `MSL-Maximum-segment-lifetime` | 解释Maximum-segment-lifetime |

如何介绍一个TCP session的lifetime，主要分为三个阶段:

| 章节                         | 内容               |
| ---------------------------- | ------------------ |
| `Connection-synchronization` | 建立TCP connection |
| `Data-transfer`              | 传输数据           |
| `Connection-termination`     | 断开TCP连接        |

其他:

| 章节        | 内容 |
| ----------- | ---- |
| `man-7-TCP` |      |
|             |      |

