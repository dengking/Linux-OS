# Transmission Control Protocol 2



## Half open and half close



superuser [what is TCP Half Open Connection and TCP half closed connection](https://superuser.com/questions/298919/what-is-tcp-half-open-connection-and-tcp-half-closed-connection)



[A](https://superuser.com/a/615971)

This post expands on half closed connections. For half open connections see KContreau's correct description.

### What are Half Closed Connections? Or: It's Not a Bug--it's a Feature!

Every TCP connection consists of two half-connection which are closed independently of each other. So if one end sends a FIN, then the other end is free to just ACK that FIN (instead of FIN+ACK-ing it), which signals the FIN-sending end that it still has data to send. So both ends end up in a stable data transfer state other than `ESTABLISHED`--namely `FIN_WAIT_2` (for the receiving end) and `CLOSE_WAIT` (for the sending end). Such a connection is said to be **half closed** and TCP is actually designed to support those scenarios, so half closed connections is a TCP feature.

### The History of Half Closed Connection

While RFC 793 only describes the raw mechanism without even mentioning the term "half closed", RFC 1122 elaborates(详细描述) on that matter in section 4.2.2.13. You may wonder who the hell needs that feature. The designers of TCP also implemented the TCP/IP for the Unix system and, like every Unix user, loved **I/O redirection**. According to W. Stevens (TCP/IP illustrated, Section 18.5) the desire to **I/O-redirect TCP streams** was the motivation to introduce the feature. It allows the FIN ack take the role of or be translated as EOF. So it's basically a feature that allows you to casually create impomptu request/response-style interaction on the application layer, where the FIN signals "end of request".



## Half-duplex close sequence

### freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)

A TCP connection may terminate in two ways:

(1) the normal TCP close sequence using a FIN handshake

(2) an "abort" in which one or more RST segments are sent and the connection state is immediately discarded. 

If a TCP connection is closed by the remote site, the local application MUST be informed whether it **closed normally** or was **aborted**.

The normal TCP close sequence delivers **buffered data** reliably in both directions. Since the two directions of a TCP connection are closed independently, it is possible for a connection to be "**half closed**," i.e., closed in only one direction, and a host is permitted to continue sending data in the open direction on a **half-closed connection**.

A host MAY implement a "half-duplex" TCP close sequence, so that an application that has called(调用) CLOSE cannot continue to read data from the connection. If such a host issues a CLOSE call while received data is still pending in TCP, or if new data is received after CLOSE is called, its TCP SHOULD send a RST to show that data was lost.