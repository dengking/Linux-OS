# [SHUTDOWN(2)](http://man7.org/linux/man-pages/man2/shutdown.2.html)

## NAME

shutdown - shut down part of a **full-duplex** connection

## SYNOPSIS

```C
       #include <sys/socket.h>

       int shutdown(int sockfd, int how);
```

## DESCRIPTION

The `shutdown()` call causes all or part of a full-duplex connection on the socket associated with `sockfd` to be shut down.  If `how` is `SHUT_RD`, further receptions will be disallowed.  If how is `SHUT_WR`, further transmissions will be disallowed.  If how is `SHUT_RDWR`, further receptions and transmissions will be disallowed.

## RETURN VALUE

On success, zero is returned.  On error, -1 is returned, and `errno` is set appropriately.

## ERRORS

`EBADF`  `sockfd` is not a valid file descriptor.

`EINVAL` An invalid value was specified in `how` (but see BUGS).

`ENOTCONN` The specified socket is not connected.

`ENOTSOCK` The file descriptor `sockfd` does not refer to a socket.

