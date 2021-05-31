# Share file descriptor between process

在阅读"wikipedia [File descriptor](https://en.wikipedia.org/wiki/File_descriptor) # File descriptors as capabilities"时，其中提及了passing file descriptor，我觉得有必要对这个topic进行总结。

## cnblogs [高级进程间通信之传送文件描述符](https://www.cnblogs.com/nufangrensheng/p/3571370.html)

> NOTE: 
> 1、这篇文章非常好



### 1、经由基于STREAMS的管道传送文件描述符

文件描述符用两个ioctl命令经由STREAMS管道交换，这两个命令是：`I_SENDFD`和`I_RECVFD`。为了发送一个描述符，将ioctl的第三个参数设置为实际描述符。

**程序清单17-12 STREAMS管道的`send_fd`函数**

```C++
#include "apue.h"
#include <stropts.h>

/*
* Pass a file descriptor to another process.
* If fd < 0, then -fd is sent back instead as the error status.
*/
int 
send_fd(int fd, int fd_to_send)
{
    char     buf[2];        /* send_fd()/recv_fd() 2-byte protocol */

    buf[0] = 0;        /* null bytes flag to recv_fd() */
    if(fd_to_send < 0)
    {
        buf[1] = -fd_to_send;    /* nonzero status means error */
        if(buf[1] == 0)
            buf[1] = 1;    /* -256, etc. would screw up protocol */ 
    }
    else
    {
        buf[1] = 0;    /* zero status means OK */
    }
    
    if(write(fd, buf, 2) != 2)
        return(-1);

    if(fd_to_send >= 0)
        if(ioctl(fd, I_SENDFD, fd_to_send) < 0)
            return(-1);
    return(0);
}
```

当接收一个描述符时，ioctl的第三个参数是一指向strrecvfd结构的指针。

```C
struct strrecvfd {
    int      fd;     /* new descriptor */
    uid_t    uid;    /* effective user ID of sender */
    gid_t    gid;    /* effective group ID of sender */
    char     fill[8];
};
```

`recv_fd`读STREAMS管道直到接收到双字节协议的第一个字节（null字节）。当发出`I_RECVFD` `ioctl`命令时，位于流首读队列中的下一条消息应当是一个描述符，它是由`I_SENDFD`发来的，或者是一条出错消息。

**程序清单17-13 STREAMS管道的recv_fd函数**

```C++
#include "apue.h"
#include <stropts.h>

/*
* Receive a file descirpor from another process ( a server ).
* In addition, any data received from the server is passed
* to (*userfunc)(STDERR_FILENO, buf, nbytes). We have a 
* 2-byte protocol for receiving the fd from send_fd(). 
*/
int
recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t))
{
    itn                  newfd,    nread, flag, status;
    char                *ptr;
    char                 buf[MAXLINE];
    struct strbuf        dat;
    struct strrecvfd     recvfd;
    
    status = -1;
    for(;;)
    {
        dat.buf = buf;
        dat.maxlen = MAXLINE;
        flag = 0;
        if(getmsg(fd, NULL, &dat, &flag) < 0)
            err_sys("getmsg error");
        nread = dat.len;
        if(nread == 0)
        {
            err_ret("connection closed by server");
            return(-1);
        }
        /*
        * See if this is the final data with null & status.
        * Null must be next to last byte of buffer, status
        * byte is last byte. Zero status means there must 
        * be a file descriptor to receive.
        */
        for(ptr = buf; ptr < &buf[nread]; )
        {
            if(*ptr++ == 0)
            {
                if(ptr != &buf[nread - 1])
                    err_dump("message format error");
                status = *ptr & 0xFF;    /* prevent sign extension */
                if(status == 0)
                {
                    if(ioctl(fd, I_RECVFD, &recvfd) < 0)
                        return(-1);
                    newfd = recvfd.fd; /* new descriptor */
                }
                else
                {
                    newfd = -status;
                }
                nread -= 2;
            }
        }
        if(nread > 0)
            if((*userfunc(STDERR_FILENO, buf, nread) != nread))
                return(-1);

        if(status >= 0)    /* final data has arrived */
            return(newfd);    /* descriptor, or -status */
    }
        
}
```

### 2、经由UNIX域套接字传送文件描述符

为了用UNIX域套接字交换文件描述符，调用`sendmsg`（2）和`recvmsg`（2）函数（http://www.cnblogs.com/nufangrensheng/p/3567376.html）。这两个函数的参数中都有一个指向msghdr结构的指针，该结构包含了所有有关收发内容的信息。该结构的定义大致如下：



## TODO

stackoverflow [Portable way to pass file descriptor between different processes](https://stackoverflow.com/questions/909064/portable-way-to-pass-file-descriptor-between-different-processes)

stackoverflow [Can I share a file descriptor to another process on linux or are they local to the process?](https://stackoverflow.com/questions/2358684/can-i-share-a-file-descriptor-to-another-process-on-linux-or-are-they-local-to-t)

gist.github [linux file descriptors passing between processes](https://gist.github.com/2396992)



stackexchange [Sharing file descriptors](https://unix.stackexchange.com/questions/429009/sharing-file-descriptors)



stackexchange [How can same fd in different processes point to the same file?](https://unix.stackexchange.com/questions/28384/how-can-same-fd-in-different-processes-point-to-the-same-file)



stackoverflow [Sending file descriptor by Linux socket](https://stackoverflow.com/questions/28003921/sending-file-descriptor-by-linux-socket)



csdn [如何在进程之间传递文件描述符（file discriptor）](https://blog.csdn.net/win_lin/article/details/7760951)

