# 关于本章



## wikipedia [Processor affinity](https://en.wikipedia.org/wiki/Processor_affinity)





## `sched_setaffinity`

### [man 2 sched_setaffinity](https://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)



### Example1

来源：

- [如何指定进程运行的CPU(命令行 taskset)](https://blog.csdn.net/xluren/article/details/43202201)
- [More information on pthread_setaffinity_np and sched_setaffinity](http://www.thinkingparallel.com/2006/08/18/more-information-on-pthread_setaffinity_np-and-sched_setaffinity/)

原文中的程序是无法编译通过的，下面是对其更正后，可以编译通过的版本：

```c++
/* Short test program to test sched_setaffinity
 * (which sets the affinity of processes to processors).
 * Compile: gcc sched_setaffinity_test.c
 *              -o sched_setaffinity_test -lm
 * Usage: ./sched_setaffinity_test
 *
 * Open a "top"-window at the same time and see all the work
 * being done on CPU 0 first and after a short wait on CPU 1.
 * Repeat with different numbers to make sure, it is not a
 * coincidence.
 */

#include <stdio.h>
#include <math.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

double waste_time(long n)
{
	double res = 0;
	long i = 0;
	while (i < n * 200000)
	{
		i++;
		res += sqrt(i);
	}
	return res;
}

int main(int argc, char **argv)
{
	unsigned long mask = 1; /* processor 0 */
	cpu_set_t set;
	CPU_SET(mask, &set);

	/* bind process to processor 0 */
	if (sched_setaffinity(getpid(), sizeof(set), &set) < 0)
	{
		perror("sched_setaffinity");
	}

	/* waste some time so the work is visible with "top" */
	printf("result: %f\n", waste_time(2000));

	mask = 2; /* process switches to processor 1 now */
	CPU_SET(mask, &set);
	if (sched_setaffinity(getpid(), sizeof(set), &set) < 0)
	{
		perror("sched_setaffinity");
	}

	/* waste some more time to see the processor switch */
	printf("result: %f\n", waste_time(2000));
}


```

编译指令：`gcc test.cpp -lm`



### Example 2

来源：[sched_setaffinity(2) — Linux manual page](https://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)

```C++
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)

int
main(int argc, char *argv[])
{
	cpu_set_t set;
	int parentCPU, childCPU;
	int nloops, j;

	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s parent-cpu child-cpu num-loops\n",
				argv[0]);
		exit(EXIT_FAILURE);
	}

	parentCPU = atoi(argv[1]);
	childCPU = atoi(argv[2]);
	nloops = atoi(argv[3]);

	CPU_ZERO(&set);

	switch (fork())
	{
		case -1: /* Error */
			errExit("fork");

		case 0: /* Child */
			CPU_SET(childCPU, &set);

			if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
				errExit("sched_setaffinity");

			for (j = 0; j < nloops; j++)
				getppid();

			exit(EXIT_SUCCESS);

		default: /* Parent */
			CPU_SET(parentCPU, &set);

			if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
				errExit("sched_setaffinity");

			for (j = 0; j < nloops; j++)
				getppid();

			wait(NULL); /* Wait for child to terminate */
			exit(EXIT_SUCCESS);
	}
}

```





## `pthread_setaffinity_np`



### man 3 [pthread_setaffinity_np](https://www.man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html)

