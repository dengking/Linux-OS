# miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html)

## Segments

Packets in TCP are called **segments**.

## Ports, connections

Endpoints of TCP connections are identified by host IP and port number. Ports 0 through 1023 are privleged. Only root can open them. This doesn't mean much anymore, since anyone and everyone can be root, and in fact, they are not privleged on Window machines.

Some port numbers are *well-known*, meaning that a particular service can be found listening at the port, if the host offers that service. Examples are the mail server listening on well-known port number 25, POP3 server at port 110.

### *ephemeral ports*

Clients generally do not request specific ports but get *ephemeral ports* assigned by the networking software automatically when a connection is made.  A connection is the four values: source IP, source port, destination IP, destination port. By using **ephemeral ports** many applications on the court machine can connect to the same service on a server machine (the same well-known port number) and each connection will be logically separate, distinguished by the automatically chosen ephemeral source port.

## Active and passive opens

The server does a passive open. This creates a listening port. It does not initiate any protcol on the wire. The client does an active open to a listening port on the server. This does start the TCP protocol. If the client open's against a non-listening port, there will either be no response, or there will be an error response. An error response is preferable because the client will not have to timeout.

## Sequence Numbers

All bytes in a TCP connection are numbered, beginning at a randomly chosen **initial sequence number (ISN)**. The **SYN packets** consume one sequence number, so actual data will begin at ISN+1. The sequence number is the byte number of the first byte of data in the TCP packet sent (also called a TCP segment). The acknowledgement number is the sequence number of the next byte the receiver expects to receive. The receiver ack'ing sequence number x acknowledges receipt of all data bytes less than (but not including) byte number x.

> NOTE: 
>
> 需要注意: ACK response packet是不消耗sequence number的

The sequence number is always valid. The acknowledgement number is only valid when the ACK flag is one. The only time the ACK flag is not set, that is, the only time there is not a valid acknowledgement number in the TCP header, is during the first packet of connection set-up.

## Connection synchronization

Connection set-up uses the **SYN flags**. They are not used except for connection set-up. The establish a connection the initiator (active open) selects an initial sequence number `X` and sends a packet with sequence number `X` and **SYN flag 1**. The other machine (server, passive open) will select its own initial sequence number `Y` and will send a packet with sequence number `Y`, **SYN flag 1**, acknowledgement number Y+1 and **ACK flag 1**. The initiator will complete the three way handshake by sending a packet with **ACK flag 1** and acknowledgement number Y+1. The connection is now established.

> NOTE: 
>
> 原文"The other machine (server, passive open) will select its own initial sequence number `Y` and will send a packet with sequence number `Y`, **SYN flag 1**, acknowledgement number Y+1 and **ACK flag 1**. "
>
> 其中的"acknowledgement number Y+1"应该是 "acknowledgement number X+1"

## Connection finish

Connections are full duplex, that is, two distinct channels from server to client and from client to server. Either side independently closes its channel. A close is signaled by the **FIN flag**. The FIN packet is ACK'ed with a sequence number one higher (FIN takes a sequence number).

To close both channels takes four messages, a FIN, its ACK, then the other side's FIN, and its ACK. Here are four scenarios:

1、*Half close:* Client (or server) sends FIN, and Server ACK's the FIN. Server continues to send data. Eventually the server sends a FIN.

2、*Full close:* Client (or server) sends FIN, and Server immediately ACK's and informs application of client close. Server requests a close so the next packet is a FIN to the client. Client ACK's Server's FIN.

3、*Simultaneous close:* Both sides simultaneously send FIN packets. Both sides will respond with ACK's and the connection is fully closed.

After full closure, a TCP connection is required to wait for twice the maximum segment lifetime, called the 2MSL wait. This prevents old packets confusing new connections, if a new connection is immediately created using old port and IP numbers. It also aids in completing the close. The sender of the last ACK does not know if the ACK was recieved. The last ACK is not ACK'ed, by definition of being last. If a re-FIN is not received in 2MSL, it can be assumed that the last ACK was heard and accepted.

> NOTE: 
>
> 上面这段话中的"re-FIN"是指什么？

## Connection reset

A packet with RST flag set aborts (resets) the connection. A SYN to a non-listening port will be ack'ed, but the ACK packet will have the RST flag set. The initiating party will immediately abort. A packet with RST set can be sent during a communication, for example, if an invalid sequence number is received. The connection is immediately aborted by both parties. A RST is not ACK'ed.