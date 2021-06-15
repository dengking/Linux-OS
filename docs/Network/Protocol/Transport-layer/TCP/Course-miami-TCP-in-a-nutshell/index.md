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

The sequence number is always valid. The acknowledgement number is only valid when the ACK flag is one. The only time the ACK flag is not set, that is, the only time there is not a valid acknowledgement number in the TCP header, is during the first packet of connection set-up.

## Connection synchronization

Connection set-up uses the **SYN flags**. They are not used except for connection set-up. The establish a connection the initiator (active open) selects an initial sequence number `X` and sends a packet with sequence number `X` and **SYN flag 1**. The other machine (server, passive open) will select its own initial sequence number `Y` and will send a packet with sequence number `Y`, **SYN flag 1**, acknowledgement number Y+1 and **ACK flag 1**. The initiator will complete the three way handshake by sending a packet with **ACK flag 1** and acknowledgement number Y+1. The connection is now established.

> NOTE: 
>
> 原文"The other machine (server, passive open) will select its own initial sequence number `Y` and will send a packet with sequence number `Y`, **SYN flag 1**, acknowledgement number Y+1 and **ACK flag 1**. "
>
> 其中的"acknowledgement number Y+1"应该是 "acknowledgement number X+1"