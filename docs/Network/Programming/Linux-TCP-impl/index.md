# Linux TCP implementation

## socket

socket是Linux network programming的核心。

1、TCP connection socket相当于一个TCP connection的一端、

2、listen socket

## TCP connection、socket、file descriptor、process

一、一个TCP connection由两个socket组成

```shell
[dk@localhost ~]$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:55490         127.0.0.1:3459          CLOSE_WAIT 
tcp        0      0 127.0.0.1:3459          127.0.0.1:55490         FIN_WAIT2
```

上面就展示了一个TCP connection由两个socket组成。

二、当`close`、process exit后，kernel中的TCP connection不会立即被销毁，而是会存在一段时间，这样做是因为:

1、对端可能还没有关闭连接

2、`TIME_WAIT`

所有，此时socket还存在于kernel中，并不会被销毁；

### 测试程序

下面是测试程序，源自 zhihu [网络编程：SO_REUSEADDR的使用](https://zhuanlan.zhihu.com/p/79999012) 

```C
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lfd == -1)
	{
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

	if (bind(lfd, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) == -1)
	{
		perror("bind: ");
		return -1;
	}

	if (listen(lfd, 128) == -1)
	{
		perror("listen: ");
		return -1;
	}

	struct sockaddr_storage claddr;
	socklen_t addrlen = sizeof(struct sockaddr_storage);
	int cfd = accept(lfd, (struct sockaddr*) &claddr, &addrlen);
	if (cfd == -1)
	{
		perror("accept: ");
		return -1;
	}
	printf("client connected: %d\n", cfd);

	close(cfd);
	close(lfd);
	return 0;
}
// gcc test.c

```

然后用`nc`模拟客户端连接：

```shell
nc 127.0.0.1 3459
```

连接后可以正常和服务器通常，用`netstat`看看连接的状态：

```shell
$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:36463         127.0.0.1:3459          ESTABLISHED
tcp        0      0 127.0.0.1:3459          127.0.0.1:36463         ESTABLISHED
```

第1条是监听套接字，第2条客户端的连接，第3条是服务器和客户端的连接；

### 测试一

#### 第一步: 关闭server，不关闭client

```C++
[dk@localhost ~]$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          127.0.0.1:55486         FIN_WAIT2  
tcp        0      0 127.0.0.1:55486         127.0.0.1:3459          CLOSE_WAIT
```

此时server process已经退出，但是TCP connection还是存在的，可以看到: 

1、listening socket已经被销毁了

2、TCP connection 的server socket处于 `FIN_WAIT2` 状态，即它已经收到了client的FIN ACK

3、TCP connection 的client socket处于 `CLOSE_WAIT` 状态

#### 第二步: 关闭client

将client关闭，再查看socket

```c++
[dk@localhost ~]$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          127.0.0.1:55488         TIME_WAIT
```

可以看到，TCP connection 的server socket处于 `TIME_WAIT` 状态；client socket已经被销毁了；

#### 第三步: 重启server

第1条是监听套接字，第2条客户端的连接，第3条是服务器和客户端的连接；我们强制中止服务器(Ctrl+C)，再看看`netstat`:

```shell
$ netstat -tna | grep 3459
tcp        0      0 127.0.0.1:3459          127.0.0.1:36463         TIME_WAIT
```

此时只有服务器建立的连接，处于是`TIME_WAIT`状态，再次启动服务器，会报下面错误：

```shell
$ ./treuseaddr 
bind: : Address already in use
```

如果把上面两行注释的去掉，就能解决这个问题，可以自己动手试试看。



### 测试二

测试超时，在关闭server后，一直不关闭client，此时server connection socket一直处于处于`FIN_WAIT2`状态，但是，server connection socket并不会一直处于处于`FIN_WAIT2`状态，经过一段时间后，kernel会将它清理掉。



## listen socket VS connection socket

listen socket是比较特殊的，由于它并不参与TCP connection，因此它和connection socket是有明显差异的:

1、connection socket会参与TCP FSM，但是listen socket并不参与