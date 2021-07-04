# TCP 粘包



## csdn [如何解决tcp通信中的粘包问题？](https://blog.csdn.net/m0_37829435/article/details/81747488)



## csdn [Socket TCP粘包、多包和少包, 断包](https://blog.csdn.net/pi9nc/article/details/17165171)

提到通信， 我们面临都通信协议，数据协议的选择。 通信协议我们可选择TCP/UDP：

1) TCP（transport control protocol，传输控制协议）是面向连接的，面向流的，提供高可靠性服务。收发两端（客户端和服务器端）都要有一一成对的socket，因此，发送端为了将多个发往接收端的包，更有效的发到对方，使用了优化方法（Nagle算法），将多次间隔较小且数据量小的数据，合并成一个大的数据块，然后进行封包。这样，接收端，就难于分辨出来了，必须提供科学的拆包机制。 即面向流的通信是无消息保护边界的。

UDP（user datagram protocol，用户数据报协议）是无连接的，面向消息的，提供高效率服务。不会使用块的合并优化算法，, 由于UDP支持的是一对多的模式，所以接收端的skbuff(套接字缓冲区）采用了链式结构来记录每一个到达的UDP包，在每个UDP包中就有了消息头（消息来源地址，端口等信息），这样，对于接收端来说，就容易进行区分处理了。 即面向消息的通信是有消息保护边界的。



## csdn [socket连接---多线程 线程池---TCP/IP半包、粘包、分包](https://blog.csdn.net/wenbingoon/article/details/8915082)

