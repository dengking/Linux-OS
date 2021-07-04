# 域名根服务器是否只有13台？

一个未分片UDP datagram的最大字节数为512，最多能够包含13条DNS记录。

## zhihu [为什么域名根服务器只能有13台呢？](https://www.zhihu.com/question/22587247)

> NOTE: 
>
> 在阅读 cnblogs [DNS原理及其解析过程](https://www.cnblogs.com/gopark/p/8430916.html) 时，其中给出了这篇文章的链接。
>
> 

### [知乎用户的回答](https://www.zhihu.com/question/22587247/answer/780462511) 

> NOTE: 
>
> 这个回答是比较精简的

其实对于一个小白来说，这个问题核心并不是13台，而是，**域名根服务器**什么，查询的过程是怎么样呢？

DNS 是一种分层结构，在整个互联网中组成一个树状系统，顶层是系统的根域名，下层为 TLD 以及二级域名，叶子就构成了所谓的 FQDN（Fully Qualified Domain Names），根域名通常使用 "." 来表示，其实际上也是由域名组成，全世界目前有 13 组域名根节点，由少数几个国家进行管理，而国内仅有几台根节点镜像。



![img](https://pic1.zhimg.com/80/v2-f5f5595b99be23d0b8d74e38b1e47b31_1440w.jpg?source=1940ef5c)

如查询 `www.im.qq.com`，简略描述 DNS 的过程就是，先查询 `com` 这个域名的`name server`有哪些，然后选一个继续查询`qq`这个子域名的`name servers`有哪些，再选一个继续查询`im`这个子域名的`name servers`有哪些，`www`不是域名，查询结束。这个查询出来的结果就是`google.com`域名。所谓的`name server`，其实就是dns服务器啦，用来解析域名的。

#### 万物起始之风——Root Servers

而上面的查询过程有一个问题就是，程序该去哪里查询`com`，`gov`这些顶级域名的服务器呢？

这个就是 `Root servers（根服务器）` 的作用，用来查询以上的顶级域名的`name server`。

#### 思考

而怎么样获取 `Root servers` 的地址呢，注意这里没有动态域名（`DNS`）可用，获取的地址其实就是要获取`IP`，假如我们来实现 `DNS 服务器`，这一步你会怎么做呢？

其实这种做法很显然易见，写程序直觉就是如此：

1、写一份配置文件放程序里，记录了全部`Root servers`的 IP 地址列表，定时从网上（这个就可以用域名了）更新这份配置文件；

2、又或者程序启动的时候，直接从网上获取这些信息，存下来，也是定时更新；



`DNS`的做法也不外乎如是，而上面说到的这份"配置文件"，就在 [https://www.internic.net/domain/named.root](https://link.zhihu.com/?target=https%3A//www.internic.net/domain/named.root)，里面就是所有`Root Servers`的 信息：



#### Priming Query！

[Initializing a DNS Resolver with Priming Queries](https://link.zhihu.com/?target=https%3A//tools.ietf.org/html/draft-ietf-dnsop-resolver-priming-11) 就是**Internet Engineering Task Force** (**IETF**) 写的一份关于 *[priming query](https://link.zhihu.com/?target=https%3A//tools.ietf.org/html/draft-ietf-dnsop-resolver-priming)*  的BCP(Best Current Practice )文档。

>  This document describes the queries that a DNS resolver should emit    to initialize its cache.  The result is that the resolver gets both a    current NS RRSet for the root zone and the necessary address    information for reaching the root servers.

上面提到的列表信息，可能并不是最新的，所以`DNS解析器`首次启动时，并不去读这份文件，而是直接去查询有哪些服务器（来自下文提及的文章，我对这个说法存疑，因为文件的大小跟查询到的东西差别应该不大，有待验证）。



作者：知乎用户
链接：https://www.zhihu.com/question/22587247/answer/780462511
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



#### 为什么是13，还重要吗？

是不是感觉没那么重要了呢。

是这样的，在DNS设计之初，在龟速的网络下，当然是希望做`Prime Query`查`Root Servers`性价比达到最高啦。

`DNS` 是用 `UDP` 传数据的，而设计的时候规定DNS查询时，一个包的能放的数据最多是 `512 Bytes`，为什么是 512 Bytes，[为什么域名根服务器只能有13台呢？ - 车小胖的回答 - 知乎](https://www.zhihu.com/question/22587247/answer/243856916) 做了完整的回答，摘录一点如下：

>  Internet 大多数网络接口 MTU>512，即使 DNS 报文 + UDP+ IP= 512+8+20=540，这个大小几乎可以在 Internet 上畅通无阻，而无需 IP 分片。
> **为何 IP 分片不好？** 一个 UDP 报文如果因为 size > MTU，则会被 IP 层分成两片多片，但是只有一片有端口号，由于其它分片没有端口号，**能否通过防火墙则完全看防火墙的脸色**，所以对于能否通信成功是一个未知数。
>  如果防火墙网开一面，不检查端口号，分片可以全部通行，到目的地再组装到一起，IP 层提交给 UDP/DNS，一点问题没有。但是防火墙的安全功能大打折扣，如何阻止非法的外来攻击包？
>  如果防火墙严格检查端口号，则没有端口号的分片则统统丢弃，造成通信障碍。
>  所以选择一个合适的 UDP size 至关重要，避免分片。
>  有同学说，对于 MTU <512 物理接口的 DNS 如何处理？这个其实好办，这些只是接入层接口，用于接入终端用户，**用户的 DNS 请求是请求其上一级 DNS 服务器做递归查询（告诉我最终查询结果）**

接着就是`13`这个数字的果了。

为了做`Prime Query`查`Root Servers`性价比达到最高，肯定是一个包能放多少东西就塞多少东西，所以把所有`Root Servers`的结果都塞进去，刚好能塞14个，不全用就塞13个吧，留下一点东西以备后患，留待扩展。

塞的细节嘛，[https://miek.nl/2013/november/10/why-13-dns-root-servers/](https://link.zhihu.com/?target=https%3A//miek.nl/2013/november/10/why-13-dns-root-servers/) 这篇文章有详细的介绍，但是我对此不大感兴趣了~

### [车小胖的回答](https://www.zhihu.com/question/22587247/answer/243856916) 

> NOTE: 
>
> 这个回答说明清楚了DNS选择512的原因

根服务器受限于UDP报文 512字节说的很清楚，但对于为何是512字节却没怎么谈论，这里谈谈我的看法。

有同学说，对于MTU <512物理接口的DNS如何处理？这个其实好办，这些只是接入层接口，用于接入终端用户，**用户的DNS请求是请求其上一级DNS服务器做递归查询（告诉我最终查询结果）**，不会直接去根服务器查询DNS，所以这个问题可以迎刃而解。

> NOTE: 
>
> 这段话没有理解

### [命运之轮的回答](https://www.zhihu.com/question/22587247/answer/1021961852) 

#### 任播网络的出现

> NOTE: 
>
> 其中提及了anycast