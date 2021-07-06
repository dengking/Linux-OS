# `SO_LINGER` 



## stackoverflow [When is TCP option SO_LINGER (0) required?](https://stackoverflow.com/questions/3757289/when-is-tcp-option-so-linger-0-required)



### [A](https://stackoverflow.com/a/13088864)

For my suggestion, please read the last section: **“When to use SO_LINGER with timeout 0”**.

Before we come to that a little lecture about:

1、Normal TCP termination

2、`TIME_WAIT`

3、`FIN`, `ACK` and `RST`

#### Normal TCP termination

The normal TCP termination sequence looks like this (simplified):

We have two peers: A and B

一、A calls `close()`

1、A sends `FIN` to B

2、A goes into `FIN_WAIT_1` state

二、B receives `FIN`

1、B sends `ACK` to A

2、B goes into `CLOSE_WAIT` state

三、A receives `ACK`

1、A goes into `FIN_WAIT_2` state

四、B calls `close()`

1、B sends `FIN` to A

2、B goes into `LAST_ACK` state

五、A receives `FIN`

1、A sends `ACK` to B

2、A goes into `TIME_WAIT` state

六、B receives `ACK`

1、B goes to `CLOSED` state – i.e. is removed from the socket tables

#### TIME_WAIT

So the peer that initiates the termination – i.e. calls `close()` first – will end up in the `TIME_WAIT` state.

To understand why the `TIME_WAIT` state is our friend, please read section 2.7 in "UNIX Network Programming" third edition by Stevens et al (page 43).

However, it can be a problem with lots of sockets in `TIME_WAIT` state on a server as it could eventually prevent new connections from being accepted.

To work around this problem, I have seen many suggesting to set the `SO_LINGER` socket option with timeout 0 before calling `close()`. However, this is a bad solution as it causes the TCP connection to be terminated with an error.

Instead, design your application protocol so the connection termination is always initiated from the client side. If the client always knows when it has read all remaining data it can initiate the termination sequence. As an example, a browser knows from the `Content-Length` HTTP header when it has read all data and can initiate the close. (I know that in HTTP 1.1 it will keep it open for a while for a possible reuse, and then close it.)

If the server needs to close the connection, design the application protocol so the server asks the client to call `close()`.

#### When to use `SO_LINGER` with timeout 0

Again, according to "UNIX Network Programming" third edition page 202-203, setting `SO_LINGER` with timeout 0 prior to calling `close()` will cause the **normal termination sequence** *not* to be initiated.

Instead, the peer setting this option and calling `close()` will send a `RST` (connection reset) which indicates an error condition and this is how it will be perceived(感知) at the other end. You will typically see errors like "Connection reset by peer".

Therefore, in the normal situation it is a really bad idea to set `SO_LINGER` with timeout 0 prior to calling `close()` – from now on called *abortive close* – in a server application.

However, certain situation warrants(授权、允许) doing so anyway:

1、If the a client of your server application misbehaves (times out, returns invalid data, etc.) an abortive close makes sense to avoid being stuck in `CLOSE_WAIT` or ending up in the `TIME_WAIT` state.

2、If you must restart your server application which currently has thousands of client connections you might consider setting this socket option to avoid thousands of server sockets in `TIME_WAIT` (when calling `close()` from the server end) as this might prevent the server from getting available ports for new client connections after being restarted.

3、On page 202 in the aforementioned book it specifically says: "There are certain circumstances which warrant(允许) using this feature to send an abortive close. One example is an RS-232 terminal server, which might hang forever in `CLOSE_WAIT` trying to deliver data to a stuck terminal port, but would properly reset the stuck port if it got an `RST` to discard the pending data."

I would recommend [this](http://www.serverframework.com/asynchronousevents/2011/01/time-wait-and-its-design-implications-for-protocols-and-scalable-servers.html) long article which I believe gives a very good answer to your question.



### [A](https://stackoverflow.com/a/3760186)

The typical reason to set a `SO_LINGER` timeout of zero is to avoid large numbers of connections sitting in the `TIME_WAIT` state, tying up all the available resources on a server.

When a TCP connection is closed cleanly, the end that initiated the close ("active close") ends up with the connection sitting in `TIME_WAIT` for several minutes. So if your protocol is one where the *server* initiates the connection close, and involves very large numbers of short-lived connections, then it might be susceptible to this problem.

This isn't a good idea, though - `TIME_WAIT` exists for a reason (to ensure that stray packets from old connections don't interfere with new connections). It's a better idea to redesign your protocol to one where the client initiates the connection close, if possible.
