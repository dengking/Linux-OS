# [close(2) - Linux man page](https://linux.die.net/man/2/close)

## Name

`close` - close a file descriptor



## Synopsis

```c
#include <unistd.h>
int close(int fd);
```

## Description

`close()` closes a **file descriptor**, so that it no longer refers to any file and may be reused. Any **record locks** (see [**fcntl**(2)](https://linux.die.net/man/2/fcntl) ) held on the file it was associated with, and owned by the process, are removed (regardless of the **file descriptor** that was used to obtain the lock).

> NOTE: file descriptor的scope是process，而不是OS；

If *fd* is the last file descriptor referring to **the underlying open file description** (see [**open**(2)](https://linux.die.net/man/2/open) ), the resources associated with the **open file description** are freed; if the descriptor was the last reference to a file which has been removed using [**unlink**(2)](https://linux.die.net/man/2/unlink) the file is deleted.

> NOTE: 这段话非常重要，它描述了OS何时release掉file table entry，显然OS管理file table entry的方式类似于引用计数的方式；



## Return Value

`close()` returns zero on success. On error, -1 is returned, and `errno`  is set appropriately.

## Errors

1、**EBADF**

*fd* isn't a valid open file descriptor.

2、**EINTR**

The **close**() call was interrupted by a signal; see [**signal**(7).](https://linux.die.net/man/7/signal)

3、**EIO**

An I/O error occurred.