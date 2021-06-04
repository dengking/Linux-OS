# [cmsg(3) — Linux manual page](https://man7.org/linux/man-pages/man3/cmsg.3.html)



```C
#include <sys/socket.h>

struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *msgh);
struct cmsghdr *CMSG_NXTHDR(struct msghdr *msgh,
                            struct cmsghdr *cmsg);
size_t CMSG_ALIGN(size_t length);
size_t CMSG_SPACE(size_t length);
size_t CMSG_LEN(size_t length);
unsigned char *CMSG_DATA(struct cmsghdr *cmsg);
```

These macros are used to create and access **control messages** (also called **ancillary data**) that are not a part of the socket payload. This control information may include 

1、the interface the packet was received on, 

2、various rarely used header fields, 

3、an extended error description, 

4、a set of file descriptors, or 

5、UNIX credentials.  

For instance, control messages can be used to send additional header fields such as `IP` options. 

Ancillary data is sent by calling [sendmsg(2)](https://man7.org/linux/man-pages/man2/sendmsg.2.html) and received by calling [recvmsg(2)](https://man7.org/linux/man-pages/man2/recvmsg.2.html).  See their manual pages for more information.



Ancillary data is a sequence of `cmsghdr` structures with appended data.  See the specific protocol man pages for the available control message types.  The maximum ancillary buffer size allowed per socket can be set using `/proc/sys/net/core/optmem_max`; see socket(7).