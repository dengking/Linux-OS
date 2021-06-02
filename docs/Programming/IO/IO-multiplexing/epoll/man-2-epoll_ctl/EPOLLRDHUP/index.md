# [How do I use EPOLLHUP](https://stackoverflow.com/questions/6437879/how-do-i-use-epollhup)



Could you guys provide me a good sample code using `EPOLLHUP` for **dead peer** handling? I know that it is a signal to detect a **user disconnection** but not sure how I can use this in code..Thanks in advance..



## [A](https://stackoverflow.com/a/6438173)

You use `EPOLLRDHUP` to detect **peer shutdown**, not `EPOLLHUP` (which signals an **unexpected close** of the socket, i.e. usually an **internal error**).



Using it is really simple, just "or" the flag with any other flags that you are giving to `epoll_ctl`. So, for example instead of `EPOLLIN` write `EPOLLIN|EPOLLRDHUP`.

After `epoll_wait`, do an `if(my_event.events & EPOLLRDHUP)` followed by whatever you want to do if the other side closed the connection (you'll probably want to close the socket).

Note that getting a "zero bytes read" result when reading from a socket *also* means that the other end has shut down the connection, so you should always check for that too, to avoid nasty surprises (the `FIN` might arrive *after* you have woken up from `EPOLLIN` but *before* you call `read`, if you are in ET mode, you'll not get another notification).





