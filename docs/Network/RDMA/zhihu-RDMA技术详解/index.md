# zhihu [RDMA技术详解（一）：RDMA概述](https://zhuanlan.zhihu.com/p/55142557)



## 1. DMA和RDMA概念

### 1.1 DMA

DMA(直接内存访问)是一种能力，允许在计算机主板上的设备直接把数据发送到内存中去，**数据搬运**不需要**CPU**的参与。

1、传统**内存访问**需要通过CPU进行数据copy来移动数据，通过CPU将内存中的Buffer1移动到Buffer2中。

2、DMA模式：可以同DMA Engine之间通过硬件将数据从Buffer1移动到Buffer2,而不需要操作系统CPU的参与，大大降低了**CPU Copy**的开销。



![img](https://pic1.zhimg.com/80/v2-d359453c9269146cd93de5eed43993c8_720w.jpg)

### 1.2 RDMA

RDMA是一种概念，在两个或者多个计算机进行通讯的时候使用DMA， 从一个主机的内存直接访问另一个主机的内存。

![img](https://pic3.zhimg.com/80/v2-f081e8fce13d8b00e5a786399d20ca06_720w.jpg)

RDMA是一种host-offload, host-bypass技术，允许应用程序(包括存储)在它们的内存空间之间直接做数据传输。具有RDMA引擎的以太网卡(RNIC)--而不是host--负责管理源和目标之间的可靠连接。

> NOTE: 
>
> "host-bypass"的意思是"绕过host"

使用RNIC的应用程序之间使用专注的QP和CQ进行通讯：

> NOTE:
>
> 在 csdn [RDMA简介](https://blog.csdn.net/zxpoiu/article/details/111166088) 中，对此有着更好的描述
>
> Queue Pairs（QP）
>
> **每对QP由Send Queue（SQ）和Receive Queue（RQ）构成**
>
> Complete Queue（CQ）
>
> 

1、每一个应用程序可以有很多QP和CQ

2、每一个QP包括一个SQ和RQ

3、每一个CQ可以跟多个SQ或者RQ相关联

![img](https://pic1.zhimg.com/80/v2-2ec811510b13787ec81a3490e4233f60_720w.jpg)



## 2、RDMA的优势

### 传统TCP/IP的劣势

传统的TCP/IP技术在数据包处理过程中，要经过操作系统及其他软件层，需要占用大量的服务器资源和内存总线带宽，数据在系统内存、处理器缓存和网络控制器缓存之间来回进行复制移动，给服务器的CPU和内存造成了沉重负担。尤其是网络带宽、处理器速度与内存带宽三者的严重"不匹配性"，更加剧了网络延迟效应。

### RDMA的优势

RDMA是一种新的直接内存访问技术，RDMA让计算机可以直接存取其他计算机的内存，而不需要经过处理器的处理。RDMA将数据从一个系统快速移动到远程系统的内存中，而不对操作系统造成任何影响。

在实现上，RDMA实际上是一种智能网卡与软件架构充分优化的远端内存直接高速访问技术，通过将RDMA协议固化于硬件(即网卡)上，以及支持Zero-copy和Kernel bypass这两种途径来达到其高性能的远程直接数据存取的目标。 使用RDMA的优势如下：

1、零拷贝(Zero-copy) - 应用程序能够直接执行数据传输，在不涉及到网络软件栈的情况下。数据能够被直接发送到缓冲区或者能够直接从缓冲区里接收，而不需要被复制到网络层。

2、内核旁路(Kernel bypass) - 应用程序可以直接在用户态执行数据传输，不需要在内核态与用户态之间做上下文切换。

> NOTE:
>
> "kernel bypass"的意思是: 绕过kernel，在 csdn [RDMA简介](https://blog.csdn.net/zxpoiu/article/details/111166088) 中，对此有着更好的展示

3、不需要CPU干预(No CPU involvement) - 应用程序可以访问远程主机内存而不消耗远程主机中的任何CPU。远程主机内存能够被读取而不需要远程主机上的进程（或CPU)参与。远程主机的CPU的缓存(cache)不会被访问的内存内容所填充。

4、消息基于事务(Message based transactions) - 数据被处理为离散消息而不是流，消除了应用程序将流切割为不同消息/事务的需求。

5、支持分散/聚合条目(Scatter/gather entries support) - RDMA原生态支持分散/聚合。也就是说，读取多个内存缓冲区然后作为一个流发出去或者接收一个流然后写入到多个内存缓冲区里去。

在具体的远程内存读写中，RDMA操作用于读写操作的远程虚拟内存地址包含在RDMA消息中传送，远程应用程序要做的只是在其本地网卡中注册相应的内存缓冲区。远程节点的CPU除在连接建立、注册调用等之外，在整个RDMA数据传输过程中并不提供服务，因此没有带来任何负载。

## 3、RDMA 三种不同的硬件实现

RDMA作为一种host-offload, host-bypass技术，使低延迟、高带宽的直接的内存到内存的数据通信成为了可能。目前支持RDMA的网络协议有：

1、InfiniBand(IB): 从一开始就支持RDMA的新一代网络协议。由于这是一种新的网络技术，因此需要支持该技术的网卡和交换机。

2、RDMA过融合以太网(RoCE): 即RDMA over Ethernet, 允许通过以太网执行RDMA的网络协议。这允许在标准以太网基础架构(交换机)上使用RDMA，只不过网卡必须是支持RoCE的特殊的NIC。

3、互联网广域RDMA协议(iWARP): 即RDMA over TCP, 允许通过TCP执行RDMA的网络协议。这允许在标准以太网基础架构(交换机)上使用RDMA，只不过网卡要求是支持iWARP(如果使用CPU offload的话)的NIC。否则，所有iWARP栈都可以在软件中实现，但是失去了大部分的RDMA性能优势。