# `close` VS `shutdown`

## stackoverflow [close vs shutdown socket?](https://stackoverflow.com/questions/4160347/close-vs-shutdown-socket)

[A](https://stackoverflow.com/a/4160356)

This is [explained](https://beej.us/guide/bgnet/html/#close-and-shutdownget-outta-my-face) in Beej's networking guide. `shutdown` is a flexible way to block communication in one or both directions. When the second parameter is `SHUT_RDWR`, it will block both sending and receiving (like `close`). However, `close` is the way to actually destroy a socket.

With `shutdown`, you will still be able to receive pending data the peer already sent (thanks to Joey Adams for noting this).


## see also
http://beej.us/guide/bgnet/html/single/bgnet.html#closedown

