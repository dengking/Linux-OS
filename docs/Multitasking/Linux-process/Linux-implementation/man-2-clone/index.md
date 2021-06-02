# [clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html)

## The `clone()` wrapper function

When the child process is created with the `clone()` wrapper function, it commences(开始) execution by calling the function pointed to by the argument `fn`.  (This differs from `fork(2)`, where execution continues in the child from the point of the `fork(2)` call.)  The `arg` argument is passed as the argument of the  function `fn`.

> NOTE: 
>
> 和`pthread_create`

## `clone3()`



## The child termination signal



## EXAMPLES     



```C
#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

static int /* Start function for cloned child */
childFunc(void *arg)
{
	struct utsname uts;

	/* Change hostname in UTS namespace of child. */

	if (sethostname(arg, strlen(arg)) == -1)
		errExit("sethostname");

	/* Retrieve and display hostname. */

	if (uname(&uts) == -1)
		errExit("uname");
	printf("uts.nodename in child:  %s\n", uts.nodename);

	/* Keep the namespace open for a while, by sleeping.
	 This allows some experimentation--for example, another
	 process might join the namespace. */

	sleep(200);

	return 0; /* Child terminates now */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

int main(int argc, char *argv[])
{
	char *stack; /* Start of stack buffer */
	char *stackTop; /* End of stack buffer */
	pid_t pid;
	struct utsname uts;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	/* Allocate memory to be used for the stack of the child. */

	stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (stack == MAP_FAILED)
		errExit("mmap");

	stackTop = stack + STACK_SIZE; /* Assume stack grows downward */

	/* Create child that has its own UTS namespace;
	 child commences execution in childFunc(). */

	pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);
	if (pid == -1)
		errExit("clone");
	printf("clone() returned %jd\n", (intmax_t) pid);

	/* Parent falls through to here */

	sleep(1); /* Give child time to change its hostname */

	/* Display hostname in parent's UTS namespace. This will be
	 different from hostname in child's UTS namespace. */

	if (uname(&uts) == -1)
		errExit("uname");
	printf("uts.nodename in parent: %s\n", uts.nodename);

	if (waitpid(pid, NULL, 0) == -1) /* Wait for child */
		errExit("waitpid");
	printf("child has terminated\n");

	exit(EXIT_SUCCESS);
}
// gcc test.c

```





## thegreenplace [Launching Linux threads and processes with clone](https://eli.thegreenplace.net/2018/launching-linux-threads-and-processes-with-clone/)

> NOTE: 非常好的文章，能够帮助我们理解Linux kernel的实现

