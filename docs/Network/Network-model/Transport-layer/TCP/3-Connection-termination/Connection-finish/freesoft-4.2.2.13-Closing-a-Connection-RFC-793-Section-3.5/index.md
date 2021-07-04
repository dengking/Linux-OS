# freesoft [4.2.2.13 Closing a Connection: RFC-793 Section 3.5](https://www.freesoft.org/CIE/RFC/1122/99.htm)

A TCP connection may terminate in two ways:

(1) the normal TCP close sequence using a FIN handshake

(2) an "abort" in which one or more RST segments are sent and the connection state is immediately discarded. 

If a TCP connection is closed by the remote site, the local application MUST be informed whether it **closed normally** or was **aborted**.

The normal TCP close sequence delivers **buffered data** reliably in both directions. Since the two directions of a TCP connection are closed independently, it is possible for a connection to be "**half closed**," i.e., closed in only one direction, and a host is permitted to continue sending data in the open direction on a **half-closed connection**.

A host MAY implement a **"half-duplex" TCP close sequence**, so that an application that has called(调用) CLOSE cannot continue to read data from the connection. If such a host issues a CLOSE call while received data is still pending in TCP, or if new data is received after CLOSE is called, its TCP SHOULD send a RST to show that data was lost.

> NOTE: 也就是说，如果一个endpoint调用了CLOSE 后，如果还收到了data，则TCP会发送一个RST。这个RST是不需要ACK的，这就是**"half-duplex" TCP close**的含义。这个例子，在wikipedia [Transmission Control Protocol](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)的4.2 Connection termination中也应用了。

When a connection is closed actively, it MUST linger（徘徊） in **TIME-WAIT** state for a time 2xMSL (Maximum Segment Lifetime). However, it MAY accept a new SYN from the remote TCP to reopen the connection directly from TIME-WAIT state, if it:

1、assigns its initial sequence number for the new connection to be larger than the largest sequence number it used on the previous connection incarnation, and

2、returns to TIME-WAIT state if the SYN turns out to be an old duplicate.



## DISCUSSION:

TCP's full-duplex data-preserving close is a feature that is not included in the analogous ISO transport protocol TP4.

Some systems have not implemented half-closed connections, presumably（大概） because they do not fit into the I/O model of their particular operating system. On these systems, once an application has called CLOSE, it can no longer read input data from the connection; this is referred to as a **"half-duplex" TCP close sequence**.

The graceful close algorithm of TCP requires that the connection state remain defined on (at least) one end of the connection, for a timeout period of 2xMSL, i.e., 4 minutes. During this period, the (remote socket, local socket) pair that defines the connection is busy and cannot be reused. To shorten the time that a given port pair is tied up, some TCPs allow a new SYN to be accepted in TIME-WAIT state.

