# [UNIX(7)](http://man7.org/linux/man-pages/man7/unix.7.html)

unix - sockets for local interprocess communication

```c++
#include <sys/socket.h>
#include <sys/un.h>

unix_socket = socket(AF_UNIX, type, 0);
error = socketpair(AF_UNIX, type, 0, int *sv);
```



## EXAMPLES

