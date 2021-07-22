# 如何解决`TIME_WAIT`过多的问题

如何解决 `TIME_WAIT` 过多对scalability的影响？在下面的文章中，进行了非常好的论述:

**一、coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)**

**关于TIME_WAIT数量太多**。从上面的描述我们可以知道，`TIME_WAIT`是个很重要的状态，但是如果在大并发的短链接下，`TIME_WAIT` 就会太多，这也会消耗很多系统资源。只要搜一下，你就会发现，十有八九的处理方式都是教你设置两个参数，一个叫**tcp_tw_reuse**，另一个叫**tcp_tw_recycle**的参数，这两个参数默认值都是被关闭的，后者recyle比前者resue更为激进，resue要温柔一些。另外，如果使用`tcp_tw_reuse`，必需设置`tcp_timestamps=1`，否则无效。这里，你一定要注意，**打开这两个参数会有比较大的坑——可能会让TCP连接出一些诡异的问题**（因为如上述一样，如果不等待超时重用连接的话，新的连接可能会建不上。正如[官方文档](https://www.kernel.org/doc/Documentation/networking/ip-sysctl.txt)上说的一样“**It should not be changed without advice/request of technical experts**”）。

> NOTE: 
>
> 1、"tw"是time wait的缩写

1、**关于tcp_tw_reuse**。官方文档上说tcp_tw_reuse 加上tcp_timestamps（又叫PAWS, for Protection Against Wrapped Sequence Numbers）可以保证协议的角度上的安全，但是你需要tcp_timestamps在两边都被打开（你可以读一下[tcp_twsk_unique](http://lxr.free-electrons.com/ident?i=tcp_twsk_unique)的源码 ）。我个人估计还是有一些场景会有问题。

2、**关于tcp_tw_recycle**。如果是tcp_tw_recycle被打开了话，会假设对端开启了tcp_timestamps，然后会去比较时间戳，如果时间戳变大了，就可以重用。但是，如果对端是一个NAT网络的话（如：一个公司只用一个IP出公网）或是对端的IP被另一台重用了，这个事就复杂了。建链接的SYN可能就被直接丢掉了（你可能会看到connection time out的错误）（如果你想观摩一下Linux的内核代码，请参看源码[ tcp_timewait_state_process](http://lxr.free-electrons.com/ident?i=tcp_timewait_state_process)）。

3、**关于tcp_max_tw_buckets**。这个是控制并发的TIME_WAIT的数量，默认值是180000，如果超限，那么，系统会把多的给destory掉，然后在日志里打一个警告（如：time wait bucket table overflow），官网文档说这个参数是用来对抗DDoS攻击的。也说的默认值180000并不小。这个还是需要根据实际情况考虑。

**Again，使用tcp_tw_reuse和tcp_tw_recycle来解决TIME_WAIT的问题是非常非常危险的，因为这两个参数违反了TCP协议（[RFC 1122](http://tools.ietf.org/html/rfc1122)）** 

其实，TIME_WAIT表示的是你主动断连接，所以，这就是所谓的“不作死不会死”。试想，如果让对端断连接，那么这个破问题就是对方的了，呵呵。另外，如果你的服务器是于HTTP服务器，那么设置一个[HTTP的KeepAlive](http://en.wikipedia.org/wiki/HTTP_persistent_connection)有多重要（浏览器会重用一个TCP连接来处理多个HTTP请求），然后让客户端去断链接（你要小心，浏览器可能会非常贪婪，他们不到万不得已不会主动断连接）。

> NOTE: 
>
> 简而言之:
>
> 1、`tcp_tw_reuse`
>
> 2、`tcp_tw_recycle`
>
> 3、`tcp_max_tw_buckets`
>
> 4、client side active close

**二、serverframework [`TIME_WAIT` and its design implications for protocols and scalable client server systems](http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html)**

> NOTE: 
>
> 已经收录了



**三、stackoverflow [When is TCP option SO_LINGER (0) required?](https://stackoverflow.com/questions/3757289/when-is-tcp-option-so-linger-0-required) # [A](https://stackoverflow.com/a/13088864)**

> NOTE: 
>
> 简而言之:
>
> 1、不要使用"set the `SO_LINGER` socket option with timeout 0 before calling `close()`"
>
> 2、使用"client side active close"

However, it can be a problem with lots of sockets in `TIME_WAIT` state on a server as it could eventually prevent new connections from being accepted.

To work around this problem, I have seen many suggesting to set the `SO_LINGER` socket option with timeout 0 before calling `close()`. However, this is a bad solution as it causes the TCP connection to be terminated with an error.

Instead, design your application protocol so the connection termination is always initiated from the client side. If the client always knows when it has read all remaining data it can initiate the termination sequence. As an example, a browser knows from the `Content-Length` HTTP header when it has read all data and can initiate the close. (I know that in HTTP 1.1 it will keep it open for a while for a possible reuse, and then close it.)

If the server needs to close the connection, design the application protocol so the server asks the client to call `close()`.





**四、cnblogs [解决TIME_WAIT过多造成的问题](https://www.cnblogs.com/dadonggg/p/8778318.html)**

> 这篇文章介绍的方法:
>
> 1、加服
>
> > 如果尽量处理了，还是解决不了问题，仍然拒绝服务部分请求，那我会采取负载均衡来抗这些高并发的短请求。持续十万并发的短连接请求，两台机器，每台5万个，应该够用了吧。一般的业务量以及国内大部分网站其实并不需要关注这个问题，一句话，达不到时才需要关注这个问题的访问量。
>
> 2、调整TCP参数



五、csdn [tcp短连接TIME_WAIT问题解决方法大全](https://blog.csdn.net/yunhua_lee/article/details/8146830)

1、csdn [tcp短连接TIME_WAIT问题解决方法大全（1）——高屋建瓴](https://blog.csdn.net/yunhua_lee/article/details/8146830)

可以通过如下方式来解决这个问题：
1）可以改为长连接，但代价较大，长连接太多会导致服务器性能问题，而且PHP等脚本语言，需要通过proxy之类的软件才能实现长连接；

2）修改ipv4.ip_local_port_range，增大可用端口范围，但只能缓解问题，不能根本解决问题；

3）客户端程序中设置socket的SO_LINGER选项；

4）客户端机器打开tcp_tw_recycle和tcp_timestamps选项；

5）客户端机器打开tcp_tw_reuse和tcp_timestamps选项；

6）客户端机器设置tcp_max_tw_buckets为一个很小的值；

2、csdn [tcp短连接TIME_WAIT问题解决方法大全（2）——SO_LINGER](https://blog.csdn.net/yunhua_lee/article/details/8146837)

> NOTE: 
>
> 这种方式是不推荐的



## serverfault [How to forcibly close a socket in TIME_WAIT?](https://serverfault.com/questions/329845/how-to-forcibly-close-a-socket-in-time-wait)

