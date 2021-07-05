# `SO_REUSEADDR`



## zhihu [网络编程：SO_REUSEADDR的使用](https://zhuanlan.zhihu.com/p/79999012)

`SO_REUSEADDR`是一个很有用的选项，一般服务器的监听socket都应该打开它。它的大意是允许服务器bind一个地址，即使这个地址当前已经存在已建立的连接，比如：

1、服务器启动后，有客户端连接并已建立，如果服务器主动关闭，那么和客户端的连接会处于TIME_WAIT状态，此时再次启动服务器，就会bind不成功，报：Address already in use。

2、服务器父进程监听客户端，当和客户端建立链接后，fork一个子进程专门处理客户端的请求，如果父进程停止，因为子进程还和客户端有连接，所以再次启动父进程，也会报Address already in use。

这次我们直接上代码，看看这两种情况：

先看看服务器程序1：

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    int lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lfd == -1) {
        perror("socket: ");
        return -1;
    }

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(3459);
    inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr);

    // int optval = 1;
    // setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (bind(lfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
        perror("bind: ");
        return -1;
    }

    if (listen(lfd, 128) == -1) {
        perror("listen: ");
        return -1;
    }

    struct sockaddr_storage claddr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int cfd = accept(lfd, (struct sockaddr*)&claddr, &addrlen);
    if (cfd == -1) {
        perror("accept: ");
        return -1;
    }
    printf("client connected: %d\n", cfd);

    char buff[100];
    for (;;) {
        ssize_t num = read(cfd, buff, 100);
        if (num == 0) {
            printf("client close: %d\n", cfd);
            close(cfd);
            break;
        } else if (num == -1) {
            int no = errno;
            if (no != EINTR && no != EAGAIN && no != EWOULDBLOCK) {
                printf("client error: %d\n", cfd);
                close(cfd);
            }
        } else {
            if (write(cfd, buff, num) != num) {
                printf("client error: %d\n", cfd);
                close(cfd);
            }
        }
    }
    return 0;
}
```

注意中间注释掉的两行，编译程序并执行它：

```text
gcc -o treuseaddr treuseaddr.c
./treuseaddr
```

然后用nc模拟客户端连接：

```text
nc 127.0.0.1 3459
```

连接后可以正常和服务器通常，用netstat看看连接的状态：

```text
$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:36463         127.0.0.1:3459          ESTABLISHED
tcp        0      0 127.0.0.1:3459          127.0.0.1:36463         ESTABLISHED
```

第1条是监听套接字，第2条客户端的连接，第3条是服务器和客户端的连接；我们强制中止服务器(Ctrl+C)，再看看netstat:

```text
$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          127.0.0.1:36463         TIME_WAIT
```

此时只有服务器建立的连接，处于是TIME_WAIT状态，再次启动服务器，会报下面错误：

```text
$ ./treuseaddr 
bind: : Address already in use
```

如果把上面两行注释的去掉，就能解决这个问题，可以自己动手试试看。

再来看另外一个例子；

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    int lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lfd == -1) {
        perror("socket: ");
        return -1;
    }

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(struct sockaddr_in));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(3459);
    inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr);

    // int optval = 1;
    // setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (bind(lfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
        perror("bind: ");
        return -1;
    }

    if (listen(lfd, 128) == -1) {
        perror("listen: ");
        return -1;
    }

    struct sockaddr_storage claddr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int cfd = accept(lfd, (struct sockaddr*)&claddr, &addrlen);
    if (cfd == -1) {
        perror("accept: ");
        return -1;
    }
    printf("[PARENT] client connected: %d\n", cfd);

    int pid = fork();
    if (pid == -1) {
        perror("fork: ");
        return -1;
    } else if (pid == 0) {      // child
        char buff[100];
        for (;;) {
            ssize_t num = read(cfd, buff, 100);
            if (num == 0) {
                printf("[CHILD] client close: %d\n", cfd);
                close(cfd);
                break;
            } else if (num == -1) {
                int no = errno;
                if (no != EINTR && no != EAGAIN && no != EWOULDBLOCK) {
                    printf("[CHILD] client error: %d\n", cfd);
                    close(cfd);
                }
            } else {
                if (write(cfd, buff, num) != num) {
                    printf("[CHILD] client error: %d\n", cfd);
                    close(cfd);
                }
            }
        }
    } else {    // parent
        close(cfd);
        printf("[PARENT] parent exit\n");
    }
    return 0;
}
```

逻辑和第1个差不多，只是和客户端的通信放在子进程中了。当我们执行`nc 127.0.0.1 3459`时，服务器有如下输出：

```text
[PARENT] client connected: 4
[PARENT] parent exit
```

说明父进程退出了，但是子进程在，而且与客户端能正常通讯，此时我们再启动父进程：

```text
$ ./treuseaddr2
bind: : Address already in use
```

没法绑定地址了，如果同样把注释的行去掉，就可以正常启动。

通过上面两个例子， 是不是对SO_REUSEADDR有更直接的认识呢？关于SO_REUSEADDR其实还有很多细节，在这儿就不抄书了，有兴趣的直接看[UNIX Network Programming](https://link.zhihu.com/?target=https%3A//book.douban.com/subject/1756533/)

## stackoverflow [What are the use cases of SO_REUSEADDR?](https://stackoverflow.com/questions/577885/what-are-the-use-cases-of-so-reuseaddr)

I have used `SO_REUSEADDR` to have my server which got terminated to restart with out complaining that the socket is already is in use. I was wondering if there are other uses of `SO_REUSEADDR`? Have anyone used the **socket option** for other than the said purpose?



### [A](https://stackoverflow.com/a/577905)

For **TCP**, the primary purpose is to restart a closed/killed process on the same address.

The flag is needed because the port goes into a `TIME_WAIT` state to ensure all data is transferred.

If two sockets are bound to the same interface and port, and they are members of the same **multicast group**, data will be delivered to both sockets.

> NOTE: 
>
> 这段话的意思是从client发送过来的data将multicast到所有bind到这个port的socket

I guess an alternative use would be a security attack to try to intercept data.

([Source](http://www.developerweb.net/forum/showthread.php?t=2941))

------

For **UDP**, `SO_REUSEADDR` is used for multicast.

> More than one process may bind to the same `SOCK_DGRAM` UDP port if the `bind()` is preceded by:
>
> ```c
> int one = 1;
> setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
> ```
>
> In this case, every incoming multicast or broadcast UDP datagram destined to the shared port is delivered to all sockets bound to the port.

([Source](http://www.kohala.com/start/mcast.api.txt))



## stackoverflow [What is the purpose of SO_REUSEADDR? [duplicate]](https://stackoverflow.com/questions/40576517/what-is-the-purpose-of-so-reuseaddr)



### [A](https://stackoverflow.com/a/40577134)

For UDP sockets, setting the `SO_REUSEADDR` option allows multiple sockets to be open on the same port.

If those sockets are also joined to a multicast group, any multicast packet coming in to that group and port will be delivered to all sockets open on that port.

