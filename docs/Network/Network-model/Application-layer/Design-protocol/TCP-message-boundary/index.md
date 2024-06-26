# TCP message boundary

一、当application layer protocol使用TCP的时候，就需要考虑如何界定message boundary

二、与TCP message boundary经常一起出现的是"粘包"的说法

## zhihu [怎么解决TCP网络传输「粘包」问题？](https://www.zhihu.com/question/20210025)

### [李晓峰的回答](https://www.zhihu.com/question/20210025/answer/1096399109)

这个词很形象啊哈哈哈。我猜最开始发明这个词的人也是很懵逼吧：我客户端调用了两次`send`，怎么服务器端一个`recv`就都读出来了？！怎么回事我辛辛苦苦打包的数据都连在一起了？！啊一定是万恶的TCP偷偷的把我的数据都地粘在一起了（想象中电脑里TCP小人坏笑着拿胶水把数据粘在一起）

现象是这样个现象，但TCP本来就是基于**字节流**而不是**消息包**的协议，它自己说的清清楚楚：我会把你的数据变成字节流发到对面去，而且保证顺序不会乱，但是你要自己搞定字节流解析。

所以这个问题其实就是“如何设计应用层协议的问题”。

> NOTE: 
>
> 当application layer protocol使用TCP的时候，就需要考虑如何界定message boundary



### [欲三更的回答](https://www.zhihu.com/question/20210025/answer/1744906223)

tcp作为面向流的协议，不存在“粘包问题”，这个大家已经说清楚了，我补充一下国内开发人员说“粘包问题”的时候，到底想说什么？

**首先，什么叫“包”？**

在基于tcp开发应用的语境下，其实有两种“包”:

其一是tcp在传输的时候封装的报文，分为包头和负载，

其二是应用开发者在应用层封装的报文结构。

**第二，什么叫“粘”？这里同样有两种含义。**

其一是指，由于tcp是面向流的协议，不会按照应用开发者的期望保持send输入数据的边界，导致接收侧有可能一下子收到多个应用层报文，需要应用开发者自己分开，有些人觉得这样不合理（那你为啥不用udp），起了个名叫“粘包”。

其二是指，用户数据被tcp发出去的时候，存在多个小尺寸数据被封装在一个tcp报文中发出去的可能性。这种“粘”不是接收侧的效果，而是由于Nagle算法（或者`TCP_CORK`）的存在，在发送的时候，就把应用开发者多次send的数据，“粘”在一个tcp报文里面发出去了，于是，先被send的数据可能需要等待一段时间，才能跟后面被send的数据一起组成报文发出去。

日常生活中说“粘包”的人，指的可能是第一种情况，也可能是第二种，不继续追问的话，很难知道他们到底在说什么。

**第三，这两个其实都不是“问题”。**

第一个是tcp的应有之义，人家本身就是个面向流的协议，如果你要用它传输数据报（datagram），必然要自己实现stream2datagram的过程。这不叫解决问题，这叫实现功能。

第二个是tcp在实现的时候，为了解决大量小报文场景下包头比负载大，导致传输性价比太低的问题，专门设计的。其实在99%的情况下，Nagle算法根本就不会导致可感知的传输延迟，只是在某些场景下，Nagle算法和延迟ACK机制碰到一起，才会导致可感知的延迟。

有些应用开发者病急乱投医，看到Nagle算法可能导致发送等待，并且可以禁止掉，于是以讹传讹说禁止Nagle算法可以让发送更快。其实99%的情况下禁不禁止都一样，延迟根本不是Nagle算法导致的；就算真有问题，最优解决方案也不是屏蔽Nagle算法。

最后，粘包是个“土话”，容易引起歧义，不建议沿用。stream2datagram就是stream2datagram，`TCP_NODELAY`就是`TCP_NODELAY`，不要说什么“粘包”。

ps：

说了半天忘了说怎么解决“问题”。

第一种“粘包”，靠设计一个带**包头**的应用层报文结构就能解决。**包头**定长，以特定标志开头，里带着**负载长度**，这样接收侧只要以定长尝试读取包头，再按照包头里的负载长度读取负载就行了，多出来的数据都留在缓冲区里即可。

其实**ip报文**和**tcp报文**都是这么干的。

第二种“粘包”，设置`TCP_NODELAY`就能屏蔽Nagle算法，但你最好确定自己知道自己在干什么。

### [邱昊宇的回答](https://www.zhihu.com/question/20210025/answer/1095382740) 

> NOTE: 
>
> 原文总结的两种方法:
>
> 1、约定特殊标记表示结束(Redis就是这样做的)
>
> 2、包头带上长度



## leetbook [TCP 粘包问题](https://leetcode-cn.com/leetbook/read/networks-interview-highlights/esq5em/)

为什么会发生TCP粘包和拆包?

① 发送方写入的数据大于套接字缓冲区的大小，此时将发生拆包。

② 发送方写入的数据小于套接字缓冲区大小，由于 TCP 默认使用 Nagle 算法，只有当收到一个确认后，才将分组发送给对端，当发送方收集了多个较小的分组，就会一起发送给对端，这将会发生粘包。

③ 进行 MSS （最大报文长度）大小的 TCP 分段，当 TCP 报文的数据部分大于 MSS 的时候将发生拆包。

④ 发送方发送的数据太快，接收方处理数据的速度赶不上发送端的速度，将发生粘包。

常见解决方法

① 在消息的头部添加消息长度字段，服务端获取消息头的时候解析消息长度，然后向后读取相应长度的内容。

② 固定消息数据的长度，服务端每次读取既定长度的内容作为一条完整消息，当消息不够长时，空位补上固定字符。但是该方法会浪费网络资源。

③ 设置消息边界，也可以理解为分隔符，服务端从数据流中按消息边界分离出消息内容，一般使用换行符。

什么时候需要处理粘包问题？

当接收端同时收到多个分组，并且这些分组之间毫无关系时，需要处理粘包；而当多个分组属于同一数据的不同部分时，并不需要处理粘包问题。





## TODO

csdn [如何解决tcp通信中的粘包问题？](https://blog.csdn.net/m0_37829435/article/details/81747488)



csdn [Socket TCP粘包、多包和少包, 断包](https://blog.csdn.net/pi9nc/article/details/17165171)

提到通信， 我们面临都通信协议，数据协议的选择。 通信协议我们可选择TCP/UDP：

1) TCP（transport control protocol，传输控制协议）是面向连接的，面向流的，提供高可靠性服务。收发两端（客户端和服务器端）都要有一一成对的socket，因此，发送端为了将多个发往接收端的包，更有效的发到对方，使用了优化方法（Nagle算法），将多次间隔较小且数据量小的数据，合并成一个大的数据块，然后进行封包。这样，接收端，就难于分辨出来了，必须提供科学的拆包机制。 即面向流的通信是无消息保护边界的。

UDP（user datagram protocol，用户数据报协议）是无连接的，面向消息的，提供高效率服务。不会使用块的合并优化算法，, 由于UDP支持的是一对多的模式，所以接收端的skbuff(套接字缓冲区）采用了链式结构来记录每一个到达的UDP包，在每个UDP包中就有了消息头（消息来源地址，端口等信息），这样，对于接收端来说，就容易进行区分处理了。 即面向消息的通信是有消息保护边界的。



csdn [socket连接---多线程 线程池---TCP/IP半包、粘包、分包](https://blog.csdn.net/wenbingoon/article/details/8915082)

