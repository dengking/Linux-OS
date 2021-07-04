# TCP connection termination



## TCP的connection termination方式

总的来说，有两种termination方式:

- Connection finish
- Connection reset（**half-duplex" TCP close sequence**）

在下面两篇文章中，都对此进行了详细说明: 



### serverfault [Use of TCP FIN and TCP RST](https://serverfault.com/questions/242302/use-of-tcp-fin-and-tcp-rst)



[A](https://serverfault.com/a/991633)

TCP is a reliable protocol. So in any case the message should not be lost in any direction, during the full life-cycle of a TCP connection. Connection termination is the last part. So TCP should make sure that all packets were delivered before closing the connection. `FIN` is used to close TCP connections gracefully in each direction, while TCP `RST` is used in a scenario where TCP connections cannot recover from errors and the connection needs to reset forcibly. As per this [tcp connection termination article](https://www.cspsprotocol.com/tcp-connection-termination/), `RSET` is used in abnormal conditions.



### TODO

stackoverflow [FIN vs RST in TCP connections](https://stackoverflow.com/questions/13049828/fin-vs-rst-in-tcp-connections)

stackoverflow [What causes a TCP/IP reset (RST) flag to be sent?](https://stackoverflow.com/questions/251243/what-causes-a-tcp-ip-reset-rst-flag-to-be-sent)

github moby [half-duplex TCP FIN not working with published ports #27539](https://github.com/moby/moby/issues/27539)

cspsprotocol [Tcp Connection Termination](https://www.cspsprotocol.com/tcp-connection-termination/)



## 2MSL wait

在下面文章中，都对此进行了深入说明:

1、miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html)

2、freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)



## Half open and half close



### superuser [what is TCP Half Open Connection and TCP half closed connection](https://superuser.com/questions/298919/what-is-tcp-half-open-connection-and-tcp-half-closed-connection)



[A](https://superuser.com/a/615971)

This post expands on half closed connections. For half open connections see KContreau's correct description.

#### What are Half Closed Connections? Or: It's Not a Bug--it's a Feature!

Every TCP connection consists of two half-connection which are closed independently of each other. So if one end sends a FIN, then the other end is free to just ACK that FIN (instead of FIN+ACK-ing it), which signals the FIN-sending end that it still has data to send. So both ends end up in a stable data transfer state other than `ESTABLISHED`--namely `FIN_WAIT_2` (for the receiving end) and `CLOSE_WAIT` (for the sending end). Such a connection is said to be **half closed** and TCP is actually designed to support those scenarios, so half closed connections is a TCP feature.

#### The History of Half Closed Connection

While RFC 793 only describes the raw mechanism without even mentioning the term "half closed", RFC 1122 elaborates(详细描述) on that matter in section 4.2.2.13. You may wonder who the hell needs that feature. The designers of TCP also implemented the TCP/IP for the Unix system and, like every Unix user, loved **I/O redirection**. According to W. Stevens (TCP/IP illustrated, Section 18.5) the desire to **I/O-redirect TCP streams** was the motivation to introduce the feature. It allows the FIN ack take the role of or be translated as EOF. So it's basically a feature that allows you to casually create impomptu request/response-style interaction on the application layer, where the FIN signals "end of request".



### wikipedia [TCP half-open](https://en.wikipedia.org/wiki/TCP_half-open)