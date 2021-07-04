# Nagle's algorithm

在csdn [Socket TCP粘包、多包和少包, 断包#为什么TCP 会粘包](https://blog.csdn.net/pi9nc/article/details/17165171) 中提及了Nagle's algorithm:

TCP（transport control protocol，传输控制协议）是面向连接的，面向流的，提供高可靠性服务。收发两端（客户端和服务器端）都要有一一成对的socket，因此，发送端为了将多个发往接收端的包，更有效的发到对方，使用了优化方法（**Nagle算法**），将多次间隔较小且数据量小的数据，合并成一个大的数据块，然后进行封包。这样，接收端，就难于分辨出来了，必须提供科学的拆包机制。 即**面向流的通信是无消息保护边界的**。



## wikipedia [Nagle's algorithm](https://en.wikipedia.org/wiki/Nagle's_algorithm)



