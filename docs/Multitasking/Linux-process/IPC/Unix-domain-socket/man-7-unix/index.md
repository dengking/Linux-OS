# [UNIX(7)](http://man7.org/linux/man-pages/man7/unix.7.html)

unix - sockets for local interprocess communication

```c++
#include <sys/socket.h>
#include <sys/un.h>

unix_socket = socket(AF_UNIX, type, 0);
error = socketpair(AF_UNIX, type, 0, int *sv);
```

## DESCRIPTION     



### Valid socket types in the UNIX domain 

Valid socket types in the UNIX domain are: 

1、`SOCK_STREAM`, for a stream-oriented socket; 

2、`SOCK_DGRAM`, for a datagram-oriented socket that preserves message boundaries (as on most UNIX implementations, UNIX domain datagram sockets are always reliable and don't reorder datagrams); and (since Linux 2.6.4)

3、`SOCK_SEQPACKET`, for a sequenced-packet socket that is connection-oriented, preserves message boundaries, and delivers messages in the order that they were sent.



### Passing file descriptors or process credentials 

UNIX domain sockets support passing file descriptors or process credentials to other processes using ancillary data.

> NOTE: 
>
> 后面会对"ancillary data"进行专门的介绍

## Ancillary messages

Ancillary data is sent and received using [sendmsg(2)](https://man7.org/linux/man-pages/man2/sendmsg.2.html) and [recvmsg(2)](https://man7.org/linux/man-pages/man2/recvmsg.2.html).  

## EXAMPLES



### `server.c`

```C++
/*
 * File connection.h
 */

#define SOCKET_NAME "/tmp/9Lq7BNBnBycd6nxy.socket"
#define BUFFER_SIZE 12

/*
 * File server.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "connection.h"

int main(int argc, char *argv[])
{
	struct sockaddr_un name;
	int down_flag = 0;
	int ret;
	int connection_socket;
	int data_socket;
	int result;
	char buffer[BUFFER_SIZE];

	/* Create local socket. */

	connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (connection_socket == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/*
	 * For portability clear the whole structure, since some
	 * implementations have additional (nonstandard) fields in
	 * the structure.
	 */

	memset(&name, 0, sizeof(name));

	/* Bind socket to socket name. */

	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

	ret = bind(connection_socket, (const struct sockaddr*) &name, sizeof(name));
	if (ret == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	/*
	 * Prepare for accepting connections. The backlog size is set
	 * to 20. So while one request is being processed other requests
	 * can be waiting.
	 */

	ret = listen(connection_socket, 20);
	if (ret == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* This is the main loop for handling connections. */

	for (;;)
	{

		/* Wait for incoming connection. */

		data_socket = accept(connection_socket, NULL, NULL);
		if (data_socket == -1)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		result = 0;
		for (;;)
		{

			/* Wait for next data packet. */

			ret = read(data_socket, buffer, sizeof(buffer));
			if (ret == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}

			/* Ensure buffer is 0-terminated. */

			buffer[sizeof(buffer) - 1] = 0;

			/* Handle commands. */

			if (!strncmp(buffer, "DOWN", sizeof(buffer)))
			{
				down_flag = 1;
				break;
			}

			if (!strncmp(buffer, "END", sizeof(buffer)))
			{
				break;
			}

			/* Add received summand. */

			result += atoi(buffer);
		}

		/* Send result. */

		sprintf(buffer, "%d", result);
		ret = write(data_socket, buffer, sizeof(buffer));
		if (ret == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		/* Close socket. */

		close(data_socket);

		/* Quit on DOWN command. */

		if (down_flag)
		{
			break;
		}
	}

	close(connection_socket);

	/* Unlink the socket. */

	unlink(SOCKET_NAME);

	exit(EXIT_SUCCESS);
}
// gcc test.c

```



### `client.c`

```C
/*
 * File client.c
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "connection.h"

int main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int ret;
	int data_socket;
	char buffer[BUFFER_SIZE];

	/* Create local socket. */

	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (data_socket == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/*
	 * For portability clear the whole structure, since some
	 * implementations have additional (nonstandard) fields in
	 * the structure.
	 */

	memset(&addr, 0, sizeof(addr));

	/* Connect socket to socket address. */

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

	ret = connect(data_socket, (const struct sockaddr*) &addr, sizeof(addr));
	if (ret == -1)
	{
		fprintf(stderr, "The server is down.\n");
		exit(EXIT_FAILURE);
	}

	/* Send arguments. */

	for (int i = 1; i < argc; ++i)
	{
		ret = write(data_socket, argv[i], strlen(argv[i]) + 1);
		if (ret == -1)
		{
			perror("write");
			break;
		}
	}

	/* Request result. */

	strcpy(buffer, "END");
	ret = write(data_socket, buffer, strlen(buffer) + 1);
	if (ret == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	/* Receive result. */

	ret = read(data_socket, buffer, sizeof(buffer));
	if (ret == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	/* Ensure buffer is 0-terminated. */

	buffer[sizeof(buffer) - 1] = 0;

	printf("Result = %s\n", buffer);

	/* Close socket. */

	close(data_socket);

	exit(EXIT_SUCCESS);
}

// gcc test.c

```

