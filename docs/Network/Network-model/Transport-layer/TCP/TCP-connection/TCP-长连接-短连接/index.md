# TCP长连接和短连接

在阅读 cnblogs [解决TIME_WAIT过多造成的问题](https://www.cnblogs.com/dadonggg/p/8778318.html) 时，其中提及了长连接、短连接的概念:

> 为什么我们要关注这个高并发短连接呢？有两个方面需要注意：
>
> \1. **高并发可以让服务器在短时间范围内同时占用大量端口**，而端口有个0~65535的范围，并不是很多，刨除系统和其他服务要用的，剩下的就更少了。
>
> \2. 在这个场景中，**短连接表示“业务处理+传输数据的时间 远远小于 TIMEWAIT超时的时间”的连接**。
>
> 这里有个相对长短的概念，比如取一个web页面，1秒钟的http短连接处理完业务，在关闭连接之后，这个业务用过的端口会停留在TIMEWAIT状态几分钟，而这几分钟，其他HTTP请求来临的时候是无法占用此端口的

上述关于短连接的介绍是非常好的。

## cnblogs [tcp长连接和短连接](https://www.cnblogs.com/georgexu/p/10909814.html)



## stackoverflow [choose between tcp “long” connection and “short” connection for internal service](https://stackoverflow.com/questions/11406405/choose-between-tcp-long-connection-and-short-connection-for-internal-service)

