# The Self-Pipe Trick

**https://news.ycombinator.com/item?id=27185522**

## yp [The self-pipe trick](http://cr.yp.to/docs/selfpipe.html)

Richard Stevens's 1992 book ``Advanced programming in the UNIX environment'' says that you can't safely mix select() or poll() with SIGCHLD (or other signals). The SIGCHLD might go off while select() is starting, too early to interrupt it, too late to change its timeout.

Solution: the self-pipe trick. Maintain a pipe and select for readability on the pipe input. Inside the SIGCHLD handler, write a byte (non-blocking, just in case) to the pipe output. Done.

> NOTE: 
>
> 在 [select(2)](https://www.man7.org/linux/man-pages/man2/select.2.html) 中，也对此进行了说明



Of course, the Right Thing would be to have fork() return a file descriptor, not a process ID.



## The linux programming interface 63.5.2 The Self-Pipe Trick




```C
static int pfd[2]; /* File descriptors for pipe */
static void handler(int sig)
{
	int savedErrno; /* In case we change 'errno' */
	savedErrno = errno;
	if (write(pfd[1], "x", 1) == -1 && errno != EAGAIN)
		errExit("write");
	errno = savedErrno;
}
int main(int argc, char *argv[])
{
	fd_set readfds;
	int ready, nfds, flags;
	struct timeval timeout;
	struct timeval *pto;
	struct sigaction sa;
	char ch;
	/* ... Initialize 'timeout', 'readfds', and 'nfds' for select() */
	if (pipe(pfd) == -1)
		errExit("pipe");
	FD_SET(pfd[0], &readfds); /* Add read end of pipe to 'readfds' */
	nfds = max(nfds, pfd[0] + 1); /* And adjust 'nfds' if required */
	flags = fcntl(pfd[0], F_GETFL);
	if (flags == -1)
		errExit("fcntl-F_GETFL");
	flags |= O_NONBLOCK; /* Make read end nonblocking */
	if (fcntl(pfd[0], F_SETFL, flags) == -1)
		errExit("fcntl-F_SETFL");
	flags = fcntl(pfd[1], F_GETFL);
	if (flags == -1)
		errExit("fcntl-F_GETFL");
	flags |= O_NONBLOCK; /* Make write end nonblocking */
	if (fcntl(pfd[1], F_SETFL, flags) == -1)
		errExit("fcntl-F_SETFL");
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; /* Restart interrupted read()s */
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		errExit("sigaction");
	while ((ready = select(nfds, &readfds, NULL, NULL, pto)) == -1 && errno == EINTR)
		continue; /* Restart if interrupted by signal */
	if (ready == -1) /* Unexpected error */
		errExit("select");
	if (FD_ISSET(pfd[0], &readfds))
	{ /* Handler was called */
		printf("A signal was caught\n");
		for (;;)
		{ /* Consume bytes from pipe */
			if (read(pfd[0], &ch, 1) == -1)
			{
				if (errno == EAGAIN)
					break; /* No more bytes */
				else
					errExit("read"); /* Some other error */
			}
			/* Perform any actions that should be taken in response to signal */
		}
	}
	/* Examine file descriptor sets returned by select() to see
	 which other file descriptors are ready */
}

```