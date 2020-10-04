# TCP connection termination



## TCP的connection termination方式

总的来说，有两种termination方式:

- Connection finish
- Connection reset（**half-duplex" TCP close sequence**）

在下面这两篇文章中，都对此进行了详细说明: 

### miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html)



#### Connection finish

Connections are full duplex, that is, two distinct channels from server to client and from client to server. Either side independently closes its channel. A close is signaled by the `FIN` flag. The FIN packet is ACK'ed with a sequence number one higher (FIN takes a **sequence number**).

To close both channels takes four messages, a FIN, its ACK, then the other side's FIN, and its ACK. Here are four scenarios:

1. *Half close:* Client (or server) sends FIN, and Server ACK's the FIN. Server continues to send data. Eventually the server sends a FIN.
2. *Full close:* Client (or server) sends FIN, and Server immediately ACK's and informs application of client close. Server requests a close so the next packet is a FIN to the client. Client ACK's Server's FIN.
3. *Simultaneous close:* Both sides simultaneously send FIN packets. Both sides will respond with ACK's and the connection is fully closed.

After full closure, a TCP connection is required to wait for twice the **maximum segment lifetime**, called the **2MSL wait**. This prevents old packets confusing new connections, if a new connection is immediately created using old port and IP numbers. It also aids in completing the close. The sender of the last ACK does not know if the ACK was recieved. The last ACK is not ACK'ed, by definition of being last. If a re-FIN is not received in 2MSL, it can be assumed that the last ACK was heard and accepted.

> NOTE: 上面解释了执行 **2MSL wait** 的原因，简而言之有两点:
>
> - prevents old packets confusing new connections
> - aids in completing the close

#### Connection reset

A packet with RST flag set aborts (resets) the connection. A SYN to a non-listening port will be ack'ed, but the ACK packet will have the RST flag set. The initiating party will immediately abort. A packet with RST set can be sent during a communication, for example, if an invalid sequence number is received. The connection is immediately aborted by both parties. A RST is not ACK'ed.

> NOTE: “A RST is not ACK'ed”其实就是在freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)中所说的“the connection state is immediately discarded”。





### freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)

A TCP connection may terminate in two ways:

(1) the normal TCP close sequence using a FIN handshake

(2) an "abort" in which one or more RST segments are sent and the connection state is immediately discarded. 

If a TCP connection is closed by the remote site, the local application MUST be informed whether it **closed normally** or was **aborted**.

The normal TCP close sequence delivers **buffered data** reliably in both directions. Since the two directions of a TCP connection are closed independently, it is possible for a connection to be "**half closed**," i.e., closed in only one direction, and a host is permitted to continue sending data in the open direction on a **half-closed connection**.

A host MAY implement a **"half-duplex" TCP close sequence**, so that an application that has called(调用) CLOSE cannot continue to read data from the connection. If such a host issues a CLOSE call while received data is still pending in TCP, or if new data is received after CLOSE is called, its TCP SHOULD send a RST to show that data was lost.

> NOTE: 也就是说，如果一个endpoint调用了CLOSE 后，如果还收到了data，则TCP会发送一个RST。这个RST是不需要ACK的，这就是**"half-duplex" TCP close**的含义。这个例子，在wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)的4.2 Connection termination中也应用了。

When a connection is closed actively, it MUST linger（徘徊） in **TIME-WAIT** state for a time 2xMSL (Maximum Segment Lifetime). However, it MAY accept a new SYN from the remote TCP to reopen the connection directly from TIME-WAIT state, if it:

1. assigns its initial sequence number for the new connection to be larger than the largest sequence number it used on the previous connection incarnation, and
2. returns to TIME-WAIT state if the SYN turns out to be an old duplicate.



DISCUSSION:

TCP's full-duplex data-preserving close is a feature that is not included in the analogous ISO transport protocol TP4.

Some systems have not implemented half-closed connections, presumably（大概） because they do not fit into the I/O model of their particular operating system. On these systems, once an application has called CLOSE, it can no longer read input data from the connection; this is referred to as a **"half-duplex" TCP close sequence**.

The graceful close algorithm of TCP requires that the connection state remain defined on (at least) one end of the connection, for a timeout period of 2xMSL, i.e., 4 minutes. During this period, the (remote socket, local socket) pair that defines the connection is busy and cannot be reused. To shorten the time that a given port pair is tied up, some TCPs allow a new SYN to be accepted in TIME-WAIT state.



## 2MSL wait

在下面文章中，都对此进行了深入说明:

- miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html)
- freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)

### wikipedia [Maximum segment lifetime](https://en.wikipedia.org/wiki/Maximum_segment_lifetime)

**Maximum segment lifetime** is the time a [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) [segment](https://en.wikipedia.org/wiki/Protocol_data_unit) can exist in the [internetwork](https://en.wikipedia.org/wiki/Internetworking) system. It is arbitrarily defined to be 2 minutes long.[[1\]](https://en.wikipedia.org/wiki/Maximum_segment_lifetime#cite_note-1)

The Maximum Segment Lifetime value is used to determine the TIME_WAIT interval (2*MSL)

## Half open and half close



### superuser [what is TCP Half Open Connection and TCP half closed connection](https://superuser.com/questions/298919/what-is-tcp-half-open-connection-and-tcp-half-closed-connection)



[A](https://superuser.com/a/615971)

This post expands on half closed connections. For half open connections see KContreau's correct description.

#### What are Half Closed Connections? Or: It's Not a Bug--it's a Feature!

Every TCP connection consists of two half-connection which are closed independently of each other. So if one end sends a FIN, then the other end is free to just ACK that FIN (instead of FIN+ACK-ing it), which signals the FIN-sending end that it still has data to send. So both ends end up in a stable data transfer state other than `ESTABLISHED`--namely `FIN_WAIT_2` (for the receiving end) and `CLOSE_WAIT` (for the sending end). Such a connection is said to be **half closed** and TCP is actually designed to support those scenarios, so half closed connections is a TCP feature.

#### The History of Half Closed Connection

While RFC 793 only describes the raw mechanism without even mentioning the term "half closed", RFC 1122 elaborates(详细描述) on that matter in section 4.2.2.13. You may wonder who the hell needs that feature. The designers of TCP also implemented the TCP/IP for the Unix system and, like every Unix user, loved **I/O redirection**. According to W. Stevens (TCP/IP illustrated, Section 18.5) the desire to **I/O-redirect TCP streams** was the motivation to introduce the feature. It allows the FIN ack take the role of or be translated as EOF. So it's basically a feature that allows you to casually create impomptu request/response-style interaction on the application layer, where the FIN signals "end of request".



### wikipedia [TCP half-open](https://en.wikipedia.org/wiki/TCP_half-open)