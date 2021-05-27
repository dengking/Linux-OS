# Domain Name System

"domain name"即"域名"

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
