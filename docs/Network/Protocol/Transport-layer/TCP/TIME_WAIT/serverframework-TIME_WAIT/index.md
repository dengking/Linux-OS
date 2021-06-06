# serverframework [`TIME_WAIT` and its design implications for protocols and scalable client server systems](http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html)

When building TCP client server systems it's easy to make simple mistakes which can severely limit scalability. One of these mistakes is failing to take into account the `TIME_WAIT` state. In this blog post I'll explain why `TIME_WAIT` exists, the problems that it can cause, how you can work around it, and when you shouldn't.

`TIME_WAIT` is an often misunderstood state in the TCP state transition diagram. It's a state that some sockets can enter and remain in for a relatively long length of time, if you have enough socket's in `TIME_WAIT` then your ability to create new **socket connections** may be affected and this can affect the scalability of your client server system(当系统中处于`TIME_WAIT`状态的socket达到一定量的时候，将会影响到新的socket connection的创建，进而影响到你的client server系统的scalability). There is often some misunderstanding about how and why a socket ends up in `TIME_WAIT` in the first place, there shouldn't be, it's not magical. As can be seen from the TCP state transition diagram below, `TIME_WAIT` is the final state that TCP clients usually end up in.

[![TCP-StateTransitionDiagram-NormalTransitions.png](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/xTCP-StateTransitionDiagram-NormalTransitions-thumb-500x749-271.png.pagespeed.ic.iSf4gnk57X.webp)](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/TCP-StateTransitionDiagram-NormalTransitions-271.html)



Although the state transition diagram shows `TIME_WAIT` as the final state for clients it doesn't have to be the client that ends up in `TIME_WAIT`. In fact, it's the **final state** that **the peer that initiates the "active close"** ends up in and this can be either the **client** or the **server**. So, what does it mean to issue the "active close"?



A TCP peer initiates an "active close" if it is the first peer to call `Close()` on the **connection**. In many protocols and client/server designs this is the client. In HTTP and FTP servers this is often the server. The actual sequence of events that leads to a peer ending up in `TIME_WAIT` is as follows.

[![TCP-StateTransitionDiagram-ClosureTransitions.png](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/xTCP-StateTransitionDiagram-ClosureTransitions-thumb-500x445-274.png.pagespeed.ic.nfz_qWs8Kr.webp)](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/TCP-StateTransitionDiagram-ClosureTransitions-274.html)



Now that we know how a socket ends up in `TIME_WAIT` it's useful to understand why this state exists and why it can be a potential problem.

`TIME_WAIT` is often also known as the 2MSL wait state. This is because the socket that transitions to `TIME_WAIT` stays there for a period that is *2 x Maximum Segment Lifetime* in duration. The MSL is the maximum amount of time that any segment, for all intents and purposes a datagram that forms part of the TCP protocol, can remain valid on the network before being discarded. This time limit is ultimately bounded by the TTL field in the **IP datagram** that is used to transmit the **TCP segment**. Different implementations select different values for MSL and common values are **30 seconds**, 1 minute or 2 minutes. RFC 793 specifies MSL as 2 minutes and Windows systems default to this value but [can be tuned using the **TcpTimedWaitDelay** registry setting](http://technet.microsoft.com/en-us/library/cc938217.aspx).

> NOTE: 参见[Wikipedia Maximum segment lifetime](https://en.wikipedia.org/wiki/Maximum_segment_lifetime)

The reason that `TIME_WAIT` can affect system scalability is that one socket in a TCP connection that is shut down cleanly will stay in the `TIME_WAIT` state for around 4 minutes. If many connections are being opened and closed quickly then socket's in `TIME_WAIT` may begin to accumulate on a system; you can view sockets in `TIME_WAIT` using **netstat**. There are a finite number of socket connections that can be established at one time and one of the things that limits this number is the number of available **local ports**. If too many sockets are in `TIME_WAIT` you will find it difficult to establish new outbound connections due to there being a lack of local ports that can be used for the new connections. But why does `TIME_WAIT` exist at all?

There are two reasons for the `TIME_WAIT` state. The first is to prevent delayed segments from one connection being misinterpreted as being part of a subsequent connection. Any segments that arrive whilst （同时） a connection is in the 2MSL wait state are discarded.



[![TIME_WAIT-why.png](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/xTIME_WAIT-why-thumb-500x711-277.png.pagespeed.ic.mXkxfKOdtZ.webp)](http://www.serverframework.com/asynchronousevents/assets_c/2011/01/TIME_WAIT-why-277.html)



In the diagram above we have two connections from end point 1 to end point 2. The address and port of each end point is the same in each connection. The first connection terminates with the **active close** initiated by end point 2. If end point 2 wasn't kept in `TIME_WAIT` for long enough to ensure that all segments from the previous connection had been **invalidated** then a delayed segment (with appropriate sequence numbers) could be mistaken for part of the second connection...



Note that it is *very* unlikely that **delayed segments** will cause problems like this. Firstly the address and port of each end point needs to be the same; which is normally unlikely as the client's port is usually selected for you by the operating system from the ephemeral port range and thus changes between connections. Secondly, **the sequence numbers** for the delayed segments need to be valid in the new connection which is also unlikely. However, should both of these things occur then `TIME_WAIT` will prevent the new connection's data from being corrupted.



The second reason for the `TIME_WAIT` state is to implement TCP's full-duplex connection termination reliably. If the final `ACK` from end point 2 is dropped then the end point 1 will resend the final `FIN`. If the connection had transitioned to `CLOSED` on end point 2 then the only response possible would be to send an `RST` as the retransmitted `FIN` would be unexpected. This would cause end point 1 to receive an error even though all data was transmitted correctly.



Unfortunately the way some operating systems implement `TIME_WAIT` appears to be slightly naive. Only a connection which exactly matches the socket that's in `TIME_WAIT`need by blocked to give the protection that `TIME_WAIT` affords. This means a connection that is identified by client address, client port, server address and server port. However, some operating systems impose a more stringent restriction and prevent the local port number being reused whilst that port number is included in a connection that is in `TIME_WAIT`. If enough sockets end up in `TIME_WAIT` then new outbound connections cannot be established as there are no local ports left to allocate to the new connection.



Windows does not do this and only prevents outbound connections from being established which *exactly* match the connections in `TIME_WAIT`.



Inbound connections are less affected by `TIME_WAIT`. Whilst the a connection that is actively closed by a server goes into `TIME_WAIT` exactly as a client connection does the local port that the server is listening on is not prevented from being part of a new inbound connection. On Windows the well known port that the server is listening on can form part of subsequently accepted connections and if a new connection is established from a remote address and port that currently form part of a connection that is in `TIME_WAIT` for this local address and port then the connection is allowed as long as the new sequence number is larger than the final sequence number from the connection that is currently in `TIME_WAIT`. However, `TIME_WAIT` accumulation on a server may affect performance and resource usage as the connections that are in `TIME_WAIT` need to be timed out eventually, doing so requires some work and until the `TIME_WAIT` state ends the connection is still taking up (a small amount) of resources on the server.



Given that `TIME_WAIT` affects outbound connection establishment due to the depletion of local port numbers and that these connections usually use local ports that are assigned automatically by the operating system from the ephemeral port range the first thing that you can do to improve the situation is make sure that you're using a decent sized ephemeral port range. On Windows you do this by adjusting the `MaxUserPort` registry setting; see [here](http://technet.microsoft.com/en-us/library/cc938196.aspx) for details. Note that by default many Windows systems have an ephemeral port range of around 4000 which is likely too low for many client server systems.



Whilst it's possible to reduce the length of time that socket's spend in `TIME_WAIT` this often doesn't actually help. Given that `TIME_WAIT` is only a problem when many connections are being established and actively closed, adjusting the 2MSL wait period often simply leads to a situation where more connections can be established and closed in a given time and so you have to continually adjust the 2MSL down until it's so low that you could begin to get problems due to delayed segments appearing to be part of later connections; this would only become likely if you were connecting to the same remote address and port and were using all of the local port range very quickly or if you connecting to the same remote address and port and were binding your local port to a fixed value.



Changing the 2MSL delay is usually a machine wide configuration change. You can instead attempt to work around `TIME_WAIT` at the socket level with the `SO_REUSEADDR`socket option. This allows a socket to be created whilst an existing socket with the same address and port already exists. The new socket essentially hijacks the old socket. You can use `SO_REUSEADDR` to allow sockets to be created whilst a socket with the same port is already in `TIME_WAIT` but this can also cause problems such as denial of service attacks or data theft. On Windows platforms another socket option, `SO_EXCLUSIVEADDRUSE` can help prevent some of the downsides of `SO_REUSEADDR`, see [here](http://msdn.microsoft.com/en-us/library/ms740621(v=vs.85).aspx), but in my opinion it's better to avoid these attempts at working around `TIME_WAIT` and instead design your system so that `TIME_WAIT` isn't a problem.



The TCP state transition diagrams above both show orderly connection termination. There's another way to terminate a TCP connection and that's by aborting the connection and sending an `RST` rather than a `FIN`. This is usually achieved by setting the `SO_LINGER` socket option to 0. This causes pending data to be discarded and the connection to be aborted with an `RST` rather than for the pending data to be transmitted and the connection closed cleanly with a `FIN`. It's important to realise that when a connection is aborted any data that might be in flow between the peers is discarded and the `RST` is delivered straight away; usually as an error which represents the fact that the "connection has been reset by the peer". The remote peer knows that the connection was aborted and neither peer enters `TIME_WAIT`.



Of course a new incarnation of a connection that has been aborted using `RST` could become a victim of the delayed segment problem that `TIME_WAIT` prevents, but the conditions required for this to become a problem are highly unlikely anyway, see above for more details. To prevent a connection that has been aborted from causing the delayed segment problem both peers would have to transition to `TIME_WAIT` as the connection closure could potentially be caused by an intermediary, such as a router. However, this doesn't happen and both ends of the connection are simply closed.



There are several things that you can do to avoid `TIME_WAIT` being a problem for you. Some of these assume that you have the ability to change the protocol that is spoken between your client and server but often, for custom server designs, you do.



For a server that never establishes outbound connections of its own, apart from the resources and performance implication of maintaining connections in `TIME_WAIT`, you need not worry unduly.



For a server that does establish outbound connections as well as accepting inbound connections then the golden rule is to always ensure that if a `TIME_WAIT` needs to occur that it ends up on the other peer and not the server. The best way to do this is to *never* initiate an active close from the server, no matter what the reason. If your peer times out, abort the connection with an `RST` rather than closing it. If your peer sends invalid data, abort the connection, etc. The idea being that if your server never initiates an active close it can never accumulate `TIME_WAIT` sockets and therefore will never suffer from the scalability problems that they cause. Although it's easy to see how you can abort connections when error situations occur what about normal connection termination? Ideally you should design into your protocol a way for the server to tell the client that it should disconnect, rather than simply having the server instigate an active close. So if the server needs to terminate a connection the server sends an application level "we're done" message which the client takes as a reason to close the connection. If the client fails to close the connection in a reasonable time then the server aborts the connection.



On the client things are slightly more complicated, after all, someone has to initiate an active close to terminate a TCP connection cleanly, and if it's the client then that's where the `TIME_WAIT` will end up. However, having the `TIME_WAIT` end up on the client has several advantages. Firstly if, for some reason, the client ends up with connectivity issues due to the accumulation of sockets in `TIME_WAIT` it's just one client. Other clients will not be affected. Secondly, it's inefficient to rapidly open and close TCP connections to the same server so it makes sense beyond the issue of `TIME_WAIT` to try and maintain connections for longer periods of time rather than shorter periods of time. Don't design a protocol whereby a client connects to the server every minute and does so by opening a new connection. Instead use a persistent connection design and only reconnect when the connection fails, if intermediary routers refuse to keep the connection open without data flow then you could either implement an application level ping, use TCP keep alive or just accept that the router is resetting your connection; the good thing being that you're not accumulating `TIME_WAIT`sockets. If the work that you do on a connection is naturally short lived then consider some form of "connection pooling" design whereby the connection is kept open and reused. Finally, if you absolutely must open and close connections rapidly from a client to the same server then perhaps you could design an application level shutdown sequence that you can use and then follow this with an abortive close. Your client could send an "I'm done" message, your server could then send a "goodbye" message and the client could then abort the connection.



`TIME_WAIT` exists for a reason and working around it by shortening the 2MSL period or allowing address reuse using `SO_REUSEADDR` are not always a good idea. If you're able to design your protocol with `TIME_WAIT` avoidance in mind then you can often avoid the problem entirely.



If you want more information about `TIME_WAIT` its implications and ways to work around it then [this article is very informative](http://www.isi.edu/touch/pubs/infocomm99/infocomm99-web/), as is [this one](http://developerweb.net/viewtopic.php?id=2941).



Note that The Server Framework ships with some examples that clearly show the various options that you have for connection termination. See [here](http://www.serverframework.com/ServerFramework/latest/Docs/examples-connectionterminationexamples.html) for more details.



**The initial version of this article was unclear in several places and contained some errors. Thanks to jwoyame for pointing out the potential errors in my reasoning in his comments below and for encouraging me to revisit my research and rework this article to improve the clarity and correctness**

