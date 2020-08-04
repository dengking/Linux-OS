# Thread Creation



## APUE 11.4 Thread Creation



### [`pthread_create`](https://man7.org/linux/man-pages/man3/pthread_create.3.html) 

### Example

```c++
#include <stdio.h>	// printf
#include <stdlib.h> // exit
#include <pthread.h> // pthread_create、pthread_t
#include <unistd.h> // getpid、pid_t
#include <errno.h>		/* for definition of errno */
#include <stdarg.h>		/* ISO C variable aruments */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for string */
/*打印错误日志辅助函数*/
#define	MAXLINE	4096			/* max line length */
void err_exit(int, const char *, ...) __attribute__((noreturn));
static void err_doit(int, int, const char *, va_list);

pthread_t ntid;
void
printids(const char *s)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid,
			(unsigned long) tid, (unsigned long) tid);
}
void *
thr_fn(void *arg)
{
	printids("new thread: ");
	return ((void *) 0);
}
int
main(void)
{
	int err;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		err_exit(err, "can’t create thread");
	printids("main thread:");
	sleep(1);
	exit(0);
}

/*
 * Fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and terminate.
 */
void
err_exit(int error, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buf[MAXLINE];

	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	if (errnoflag)
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s",
				strerror(error));
	strcat(buf, "\n");
	fflush(stdout); /* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL); /* flushes all stdio output streams */
}
// gcc test.cpp  -lpthread
```

