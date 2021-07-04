# Domain Name System

1、"domain name"即"域名"

## wanweibaike [Domain Name System](https://en.wanweibaike.com/wiki-DNS%20resolver)

The **Domain Name System** (**DNS**) is a [hierarchical](https://en.wanweibaike.com/wiki-Hierarchy) and [decentralized](https://en.wanweibaike.com/wiki-Decentralised_system) naming system for computers, services, or other resources connected to the [Internet](https://en.wanweibaike.com/wiki-Internet) or a private network. It associates various information with [domain names](https://en.wanweibaike.com/wiki-Domain_name) assigned to each of the participating entities. Most prominently(显著的), it translates more readily memorized domain names to the numerical [IP addresses](https://en.wanweibaike.com/wiki-IP_address) needed for locating and identifying computer services and devices with the underlying [network protocols](https://en.wanweibaike.com/wiki-Communication_protocol). By providing a worldwide, [distributed](https://en.wanweibaike.com/wiki-Distributed_computing) [directory service](https://en.wanweibaike.com/wiki-Directory_service), the Domain Name System has been an essential component of the functionality of the Internet since 1985.

> NOTE: 
>
> 一、hierarchy structure
>
> 二、 [decentralized](https://en.wanweibaike.com/wiki-Decentralised_system) naming system
>
> 去中心化的
>
> 三、建立 domain name 和 numerical [IP addresses](https://en.wanweibaike.com/wiki-IP_address) 之间的映射关系，它本质上是一个 " [distributed](https://en.wanweibaike.com/wiki-Distributed_computing) [directory service](https://en.wanweibaike.com/wiki-Directory_service) "
>
> distributed hash table、distributed database

## wanweibaike [DNS root zone](https://en.wanweibaike.com/wiki-DNS%20root%20zone)

A combination of limits in the DNS definition and in certain protocols, namely the practical size of unfragmented [User Datagram Protocol](https://en.wanweibaike.com/wiki-User_Datagram_Protocol) (UDP) packets, resulted in a practical maximum of 13 [root name server](https://en.wanweibaike.com/wiki-Root_name_server) addresses that can be accommodated in DNS name query responses. However the root zone is serviced by several hundred servers at over 130 locations in many countries.[[3\]](https://en.wanweibaike.com/wiki-DNS root zone#cite_note-3)[[4\]](https://en.wanweibaike.com/wiki-DNS root zone#cite_note-4)

> NOTE: 
>
> 解释了13的原因

## cnblogs [DNS原理及其解析过程](https://www.cnblogs.com/gopark/p/8430916.html)

### 为什么需要DNS解析域名为IP地址？

网络通讯大部分是基于TCP/IP的，而TCP/IP是基于IP地址的，所以计算机在网络上进行通讯时只能识别如“202.96.134.133”之类的IP地址，而不能认识域名。我们无法记住10个以上IP地址的网站，所以我们访问网站时，更多的是在浏览器地址栏中输入域名，就能看到所需要的页面，这是因为有一个叫“DNS服务器”的计算机自动把我们的域名“翻译”成了相应的IP地址，然后调出IP地址所对应的网页。

### 具体什么是DNS？

DNS( Domain Name System)是“域名系统”的英文缩写，是一种组织成域层次结构的计算机和网络服务命名系统，它用于TCP/IP网络，它所提供的服务是用来将主机名和域名转换为IP地址的工作。DNS就是这样的一位“翻译官”，它的基本工作原理可用下图来表示。

![img](https://pic1.zhimg.com/80/e5143bc08d4ec9d7f210522c7e540f4d_hd.jpg)

### DNS 的过程？

关于DNS的获取流程：

DNS是应用层协议，事实上他是为其他应用层协议工作的，包括不限于HTTP和SMTP以及FTP，用于将用户提供的主机名解析为ip地址。

具体过程如下：

①用户主机上运行着DNS的客户端，就是我们的PC机或者手机客户端运行着DNS客户端了

②浏览器将接收到的url中抽取出域名字段，就是访问的主机名，比如

```shell
http://www.baidu.com/
```

, 并将这个主机名传送给DNS应用的客户端

③DNS客户机端向DNS服务器端发送一份查询报文，报文中包含着要访问的主机名字段（中间包括一些列缓存查询以及分布式DNS集群的工作）

④该DNS客户机最终会收到一份回答报文，其中包含有该主机名对应的IP地址

⑤一旦该浏览器收到来自DNS的IP地址，就可以向该IP地址定位的HTTP服务器发起TCP连接



### DNS服务的体系架构是怎样的？

DNS domain name system 主要作用就是将主机域名转换为ip地址

假设运行在用户主机上的某些应用程序（如Webl浏览器或者邮件阅读器）需要将主机名转换为IP地址。这些应用程序将调用DNS的客户机端，并指明需要被转换的主机名。（在很多基于UNIX的机器上，应用程序为了执行这种转换需要调用函数`gethostbyname`）。用户主机的DNS客户端接收到后，向网络中发送一个DNS查询报文。所有DNS请求和回答报文使用的UDP数据报经过端口`53`发送（**至于为什么使用UDP，请参看**[为什么域名根服务器只能有13台呢？ - 郭无心的回答](http://www.zhihu.com/question/22587247/answer/66417484)）经过若干ms到若干s的延时后，用户主机上的DNS客户端接收到一个提供所希望映射的DNS回答报文。这个查询结果则被传递到调用DNS的应用程序。因此，从用户主机上调用应用程序的角度看，DNS是一个提供简单、直接的转换服务的黑盒子。**但事实上，实现这个服务的黑盒子非常复杂，它由分布于全球的大量DNS服务器以及定义了DNS服务器与查询主机通信方式的应用层协议组成。**



#### DNS为什么不采用单点的集中式的设计方式，而是使用分布式集群的工作方式？

DNS的一种简单的设计模式就是在因特网上只使用一个DNS服务器，该服务器包含所有的映射，在这种集中式的设计中，客户机直接将所有查询请求发往单一的DNS服务器，同时该DNS服务器直接对所有查询客户机做出响应，尽管这种设计方式非常诱人，但他不适用当前的互联网，因为当今的因特网有着数量巨大并且在持续增长的主机，这种集中式设计会有**单点故障**（嗝屁一个，全球着急），**通信容量**（上亿台主机发送的查询DNS报文请求，包括但不限于所有的HTTP请求，电子邮件报文服务器，TCP长连接服务），**远距离的时间延迟**（澳大利亚到纽约的举例），**维护开销大**（因为所有的主机名-ip映射都要在一个服务站点更新）等问题

DNS服务器一般分三种，根DNS服务器，顶级DNS服务器，权威DNS服务器。


![img](https://pic2.zhimg.com/80/607e9d15fd6d5f9d02f6f4b0adb261b9_hd.jpg)

使用分布式的层次数据库模式以及缓存方法来解决单点集中式的问题。



#### DNS域名称

域名系统作为一个层次结构和分布式数据库，包含各种类型的数据，包括主机名和域名。DNS数据库中的名称形成一个分层树状结构称为域命名空间。域名包含单个标签分隔点，例如：

```text
im.qq.com
```

完全限定的域名 (FQDN) 唯一地标识在 DNS 分层树中的主机的位置，通过指定的路径中点分隔从根引用的主机的名称列表。 下图显示与主机称为 im 内

> NOTE: 
>
> fully qualified name lookup

```text
qq.com
```

DNS 树的示例。 主机的 FQDN 是

```text
 im.qq.com
```

DNS 域的名称层次结构

![img](https://pic2.zhimg.com/80/0c7565c6c0543b554ee02e163a820b25_hd.jpg)

 

DNS域名称空间的组织方式
按其功能命名空间中用来描述 DNS 域名称的五个类别的介绍详见下表中，以及与每个名称类型的示例。

例如：

```text
www.uestc.edu.cn
```


![img](https://pic2.zhimg.com/80/79b9fd2666e989ab24024966632ae63f_hd.jpg)

DNS 和 Internet 域
互联网域名系统由名称注册机构负责维护分配由组织和国家/地区的顶级域在 Internet 上进行管理。 这些域名按照国际标准 3166。 一些很多现有缩写，保留以供组织中，以及两个字母和三个字母的国家/地区使用的缩写使用下表所示。一些常见的DNS域名称如下图：

![img](https://pic1.zhimg.com/80/bd29822632ad712b1944bb41d7d3e0ba_hd.jpg)

 

