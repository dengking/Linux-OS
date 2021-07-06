# fd is reference

本节标题的含义是: fd是reference to underlying data structure；

关于此，参见: 

1、`Programming\IO\IO-data-structure`

2、[close(2) - Linux man page](https://linux.die.net/man/2/close)

`close(2)` 释放reference。

3、APUE 16.2 Socket Descriptors

> There are several reasons. First, close will deallocate the network endpoint only when the last active reference is closed. If we duplicate the socket (with dup, for example), the socket won’t be deallocated until we close the last file descriptor referring to it.

