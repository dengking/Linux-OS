# Message Boundaries



## learningnetwork.cisco [TCP / UDP Preserving Message Boundaries](https://learningnetwork.cisco.com/message/514624#514624)

Hello, I have been reading a book which describes the following:

**UDP**  "preserves **message boundaries**" whereas **TCP** does not. What exactly does this mean?

Thank You



### A1

Grant,

I think it means that in UDP, the data is sent in clearly defined (size-wise) packages. In TCP on the other hand the **window size** might vary. So, imagine you need to transmit the following line of data: "`THE QUICK BROWN  FOX JUMPS OVER THE LAZY DOG`". In UDP you'd split that into **fixed size chunks** (depending on what application you use) and end up with the following:

`*THE** QU**iCK** BR**OWN** FO**X J**UMP**S O**VER** TH**E L**AZY** DO**G`**. The asterisks in this exmple delimit the message start and end. So, you end up with clear **boundaries** for each message. Now let's use **TCP** to transmit the same. We start with medium **window size**, but our bandwidth is good, so we start growing the window dynamically and end up with something like this.

`*THE*2* QUICK*3* BROWN FO*4*X JUMPS OVER THE*5*LAZY DOG*`

As you see, we've got different size chunks of data (**segments** in TCP lingo), but all of them have **sequence numbers**, so can be easily re-assembled in the right order.

So, short answer to your question is "this is to do with **payload size** and the way that payload gets split into transportable chunks". I might be wrong 



### A2

hi,dudes:

 

A "message boundary" is the separation between two messages being sent over a protocol. UDP preserves message boundaries. If you send "`FOO`" and then "`BAR`" over **UDP**, the other end will receive two datagrams, one containing "`FOO`" and the other containing "`BAR`".

If you send "`FOO`" and then "`BAR`" over TCP, no message boundary is preserved. The other end might get "`FOO`" and then "`BAR`". Or it might get "`FOOBAR`". Or it might get "`F`" and then "`OOB`" and then "`AR`". TCP does not make any attempt to preserve application message boundaries -- it's just a **stream of bytes** in each direction.



## linux-c-programming [UDP message boundary](https://linux-c-programming.vger.kernel.narkive.com/vXWrtdzD/udp-message-boundary)

  Hi All

When using **TCP socket**, I loop `send()` or `recv()` until ALL the data has been transmitted (or error, disconnect, etc.), because **TCP socket packet** is transmitted in **stream** nature, maybe a byte, bytes or all
bytes in one transfer.

The **UDP socket** preserve **message boundary** which TCP socket doesn't. Does this means single call to `sendto()` will processed by single call `recvfrom()`?, and how about packet that exceeds UDP data MAX size?.

So in code, do I need to loop `sendto()` or `recvfrom()` to transmit the data?.

Example codes is:

```c
char packet[100];
size_t nbytes = 0;
int ret;

while (nbytes < sizeof(packet)) {
	ret = recvfrom(socket, packet + nbytes, addr, 0, sizeof(packet) - nbytes);
    if (ret <= 0) {
        /* deal with recvfrom() error */
    }
    nbytes += ret
}

```




Thanks
\--
To unsubscribe from this list: send the line "unsubscribe linux-c-programming" in
the body of a message to ***@vger.kernel.org
More majordomo info at http://vger.kernel.org/majordomo-info.html  





### [*Post by Randi Botse*](https://linux-c-programming.vger.kernel.narkive.com/vXWrtdzD/udp-message-boundary#post1)

> Hi All
> When using TCP socket, I loop `send()` or `recv()` until ALL the data has been transmitted (or error, disconnect, etc.), because TCP socket packet is transmitted in stream nature, maybe a byte, bytes or all
> bytes in one transfer.

TCP is like a water tap(a character device) that you need to "format" yourself with boundaries/etc.

> [*Post by Randi Botse*](https://linux-c-programming.vger.kernel.narkive.com/vXWrtdzD/udp-message-boundary#post1)
> The UDP socket preserve **message boundary** which **TCP socket** doesn't. Does this means single call to `sendto()` will processed by single call `recvfrom()`?, and how about packet that exceeds UDP data MAX size?.

**UDP** is more like a **block device**, a letter/package sent. It's only the single packet that is sent, and only that same single packet that will be received (or go missing in the post)

I believe the error you might be referring to is this one from a Linux 2.6 based Ubuntu 6.0.5 man page for `recvfrom`:

<quote [man recv(2)](https://linux.die.net/man/2/recv)>

> All three routines return the length of the message on successful completion. If a message is too long to fit in the **supplied buffer**, excess bytes may be discarded depending on the type of socket the message is received from.
>
> **MSG_TRUNC** (since Linux 2.2) For raw (AF_PACKET), Internet datagram (since Linux 2.4.27/2.6.8), netlink (since Linux 2.6.22) and UNIX datagram (since Linux 3.4) sockets: return the real length of the packet or datagram, even when it was longer than the passed buffer. Not implemented for UNIX domain ([unix](https://linux.die.net/man/7/unix)(7)) sockets.
>
> For use with Internet stream sockets, see **tcp**(7).



In other words, you have been sent a 1024 byte long packet with `sentto(2)`, but `recvfrom(2)` only had a 900 bytes **buffer**, then sorry,you've lost 124 bytes.

Looking at the `recv(2)` manual page, I recall that `recv(2)`/`recvfrom(2)` will return the size of the packer received, so if you've provided a 65535 byte buffer, and was only sent 1024 bytes, then `recv(2)`/`recvfrom(2)` will return the 1024 bytes answer.

> [*Post by Randi Botse*](https://linux-c-programming.vger.kernel.narkive.com/vXWrtdzD/udp-message-boundary#post1)
> So in code, do I need to loop `sendto()` or `recvfrom()` to transmit the data?.

It depends on the data being sent, but for every `sendto(2)`, you will need a single `recv(2)`/`recvfrom(2)` with a **correctly sized buffer** to receive that single message.

> [*Post by Randi Botse*](https://linux-c-programming.vger.kernel.narkive.com/vXWrtdzD/udp-message-boundary#post1)
>
> ```c
> char packet[100];
> size_t nbytes =0;
> int ret;
> while (nbytes < sizeof(packet)) {
> 	ret = recvfrom(socket, packet + nbytes, addr, 0, sizeof(packet) - nbytes);
>     
>     if (ret <= 0) {
>     /* deal with recvfrom() error */
>     }
>     nbytes += ret
> }
> ```



That is TCP, for UDP you will have something like:

sender:

```c
char buffer[1024];

int size_of_data = fill_buffer_withdata(buffer,1024);

sendto(socket,buffer,size_of_data,flags);

```



receiver:

```c
chat buffer [1024];
int size_of_data=recv(socket,buffer,1024,flags);
if size_of_data > 1024 then
    throw_error
else
	do_something_with_data(buffer,size_of_data);
end
```



there are another method, using `MSG_PEEK` in the flags before reading the real data and remove that from the queue.

