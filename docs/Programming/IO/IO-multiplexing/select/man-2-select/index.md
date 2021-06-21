# [select(2)](https://www.man7.org/linux/man-pages/man2/select.2.html)

`select`, `pselect`, `FD_CLR`, `FD_ISSET`, `FD_SET`, `FD_ZERO` - synchronous I/O multiplexing

## SYNOPSIS         

```C++
#include <sys/select.h>

int select(int nfds, fd_set *restrict readfds,
           fd_set *restrict writefds, fd_set *restrict exceptfds,
           struct timeval *restrict timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

int pselect(int nfds, fd_set *restrict readfds,
            fd_set *restrict writefds, fd_set *restrict exceptfds,
            const struct timespec *restrict timeout,
            const sigset_t *restrict sigmask);
```

