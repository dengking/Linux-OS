#include <pthread.h>
#include <stdlib.h> /*qsort header*/
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#include <errno.h>		/* for definition of errno */
#include <stdarg.h>		/* ISO C variable aruments */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */

/**
 * 这是源自于APUE的11.6.8节的例子。
 *编译指令：
 * gcc -std=gnu99 barrier.c -lpthread
 *
 * 需要注意的是，如果使用如下编译指令：
 * gcc -std=c99 barrier.c -lpthread
 * 则会报如下错误：
 * 未知的类型名‘pthread_barrier_t’
 */



/*打印错误日志辅助函数*/
#define	MAXLINE	4096			/* max line length */
void err_exit(int, const char *, ...) __attribute__((noreturn));
static void err_doit(int, int, const char *, va_list);

#define NTHR   8				/* number of threads */
#define NUMNUM 8000000L			/* number of numbers to sort */
#define TNUM   (NUMNUM/NTHR)	/* number to sort per thread */

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

//#ifdef SOLARIS
//#define heapsort qsort
//#else
//extern int heapsort(void *, size_t, size_t,
//                    int (*)(const void *, const void *));
//#endif

/*
 * Compare two long integers (helper function for heapsort)
 */
int complong(const void *arg1, const void *arg2) {
	long l1 = *(long *) arg1;
	long l2 = *(long *) arg2;

	if (l1 == l2)
		return 0;
	else if (l1 < l2)
		return -1;
	else
		return 1;
}

/*
 * Worker thread to sort a portion of the set of numbers.
 */
void *
thr_fn(void *arg) {
	long idx = (long) arg;

	qsort(&nums[idx], TNUM, sizeof(long), complong);
	pthread_barrier_wait(&b);

	/*
	 * Go off and perform more work ...
	 */
	return ((void *) 0);
}

/*
 * Merge the results of the individual sorted ranges.
 */
void merge() {
	long idx[NTHR];
	long i, minidx, sidx, num;

	for (i = 0; i < NTHR; i++)
		idx[i] = i * TNUM;
	for (sidx = 0; sidx < NUMNUM; sidx++) {
		num = LONG_MAX;
		for (i = 0; i < NTHR; i++) {
			if ((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < num)) {
				num = nums[idx[i]];
				minidx = i;
			}
		}
		snums[sidx] = nums[idx[minidx]];
		idx[minidx]++;
	}
}

int main() {
	unsigned long i;
	struct timeval start, end;
	long long startusec, endusec;
	double elapsed;
	int err;
	pthread_t tid;

	/*
	 * Create the initial set of numbers to sort.
	 */
	srandom(1);
	for (i = 0; i < NUMNUM; i++)
		nums[i] = random();

	/*
	 * Create 8 threads to sort the numbers.
	 */
	gettimeofday(&start, NULL);
	pthread_barrier_init(&b, NULL, NTHR + 1);
	for (i = 0; i < NTHR; i++) {
		err = pthread_create(&tid, NULL, thr_fn, (void *) (i * TNUM));
		if (err != 0)
			err_exit(err, "can't create thread");
	}
	pthread_barrier_wait(&b);
	merge();
	gettimeofday(&end, NULL);

	/*
	 * Print the sorted list.
	 */
	startusec = start.tv_sec * 1000000 + start.tv_usec;
	endusec = end.tv_sec * 1000000 + end.tv_usec;
	elapsed = (double) (endusec - startusec) / 1000000.0;
	printf("sort took %.4f seconds\n", elapsed);
	for (i = 0; i < NUMNUM; i++)
		printf("%ld\n", snums[i]);
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
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
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
