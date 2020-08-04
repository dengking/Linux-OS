# Thread Termination



## APUE 11.5 Thread Termination



### [`pthread_exit`](https://www.man7.org/linux/man-pages/man3/pthread_exit.3.html) 

```C++
#include <pthread.h>
void pthread_exit(void *rval_ptr);
```

The `rval_ptr` argument is a typeless pointer, similar to the single argument passed to the start routine. This pointer is available to other threads in the process by calling the `pthread_join` function.

### [`pthread_join`](https://www.man7.org/linux/man-pages/man3/pthread_join.3.html)  

```C++
#include <pthread.h>
int pthread_join(pthread_t thread, void **rval_ptr); // Returns: 0 if OK, error number on failure
```

> NOTE: 
>
> ### `rval_ptr` is typeless pointer 
>
> 线程执行函数的原型如下:
>
> ```c++
> void *(*start_rtn)(void *)
> ```
>
> `pthread_exit`的原型如下：
>
> ```c++
> void pthread_exit(void *rval_ptr);
> ```
>
> `pthread_join`的原型如下：
>
> ```c++
> int pthread_join(pthread_t thread, void **rval_ptr);
> ```
>
> 可以看到，`rval_ptr`的类型是`void *`，即typeless pointer，这就使得我们在使用它的时候，需要进行cast；



> NOTE:
>
> ### Double pointer
>
> 用户通过调用[`pthread_exit`](https://www.man7.org/linux/man-pages/man3/pthread_exit.3.html)来告知OS 本thread的返回值，即通过将返回值的地址传入到`pthread_exit`函数，所以`pthread_exit`的入参的类型是typeless pointer： `void *retval`，显然声明为`void *`是为了实现generic；显然在实现层，肯定会有一个global variable或者thread local variable来保存入参`retval`的值，这个variable应该是double pointer类型的；
>
> 让`retval`指向返回值；[`pthread_join`](https://www.man7.org/linux/man-pages/man3/pthread_join.3.html) 要去取这个返回值，则需要使用一个pointer指向
>
> 让一个指针指向，则需要传入这个指针的地址，让后向这个地址中写入；
>
> 关于double pointer，参见工程programming-language；



> NOTE:
>
> ### Promise-future模型
>
> 上述`pthread_exit`的入参`rval_ptr`与`pthread_join`的入参`rval_ptr`名称相同，它所表达的含义是：通过调用`pthread_join`来取得return value；
>
> `pthread_exit`和`pthread_join`让我想起来promise-future模型：`pthread_exit`返回future，`pthread_join`取得future；
>
> 关于Promise-future模型，参见工程Parallel-computing。
>
> Promise-future模型和后面会介绍的“Fork-join model”密切相关；



The calling thread will **block** until the specified thread calls `pthread_exit`, returns from its start routine, or is canceled. If the thread simply returned from its start routine, `rval_ptr` will contain the **return code**. If the thread was canceled, the memory location specified by `rval_ptr` is set to `PTHREAD_CANCELED`.

By calling `pthread_join`, we automatically place the thread with which we’re joining in the **detached state** (discussed shortly) so that its resources can be recovered. If the thread was already in the **detached state**, `pthread_join` can fail, returning `EINVAL`, although this behavior is implementation-specific.

> NOTE: 
>
> ### Joinable state and detached state
>
> `pthread_join`会将一个thread从joinalbe state转换为detached state。
>
> 上面这段话的最后一句告诉我们，`pthread_join`的用法应该如下：
>
> ```c++
> if(is_joinable(thread_id))
> {
> 	pthread_join(thread_id);
> }
> ```
>
> c++ thread library就是使用的这种模式，我们将这种模式成为：Fork-join model，在下面的“Fork-join model”中对它进行了详细说明。
>
> 如下三种方式可以使一个thread处于detached state：
>
> - `pthread_join`
> - [`pthread_detach`](https://man7.org/linux/man-pages/man3/pthread_detach.3.html) 
> - create a thread that is already in the **detached state** by modifying the **thread attributes** we pass to `pthread_create`.
>
> 关于detached state，在本章最后一段也进行了说明。

If we’re not interested in a thread’s **return value**, we can set `rval_ptr` to NULL. In this case, calling `pthread_join` allows us to wait for the specified thread, but does not retrieve the thread’s **termination status**.

### Example 11.3 

Figure 11.3 shows how to fetch the exit code from a thread that has terminated.

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

void *
thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return ((void *) 1); // 直接通过线程执行函数返回
}
void *
thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *) 2); // 直接通过线程执行函数返回
}
int
main(void)
{
	int err;
	pthread_t tid1, tid2;
	void *tret; // 线程的返回值
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 1");
	}
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 2");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0)
	{
		err_exit(err, "can’t join with thread 1");
	}
	printf("thread 1 exit code %ld\n", (long) tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
	{
		err_exit(err, "can’t join with thread 2");
	}
	printf("thread 2 exit code %ld\n", (long) tret);
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

> NOTE: 运行结果如下：
>
> ```c++
> thread 1 returning
> thread 1 exit code 1
> thread 2 exiting
> thread 2 exit code 2
> 
> ```
>
> 

As we can see, when a thread exits by calling `pthread_exit` or by simply returning from the start routine, the exit status can be obtained by another thread by calling `pthread_join`.

The **typeless pointer** passed to `pthread_create` and `pthread_exit` can be used to pass more than a single value. The pointer can be used to pass the address of a structure containing more complex information. Be careful that the memory used for the structure is still valid when the **caller** has completed. If the structure was allocated on the **caller**’s stack, for example, the memory contents might have changed by the time the structure is used. If a thread allocates a structure on its **stack** and passes a pointer to this structure to `pthread_exit`, then the **stack** might be destroyed and its memory reused for something else by the time the caller of `pthread_join` tries to use it.

> NOTE: 上面所描述的问题就是dangling pointer问题，关于dangling pointer，参见`Programming\Computer-errors\Memory-access-error\Dangling-and-wild-pointer`

### Example 11.4: using an automatic variable (allocated on the stack) as the argument to `pthread_exit`

The program in Figure 11.4 shows the problem with using an automatic variable (allocated on the stack) as the argument to `pthread_exit`.

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

struct foo
{
	int a, b, c, d;
};
void
printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf(" structure at 0x%lx\n", (unsigned long) fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}
void *
thr_fn1(void *arg)
{
	struct foo foo = { 1, 2, 3, 4 };
	printfoo("thread 1:\n", &foo);
	pthread_exit((void *) &foo);
}
void *
thr_fn2(void *arg)
{
	printf("thread 2: ID is %lu\n", (unsigned long) pthread_self());
	pthread_exit((void *) 0);
}
int
main(void)
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 1");
	}
	err = pthread_join(tid1, (void **) &fp);
	if (err != 0)
	{
		err_exit(err, "can’t join with thread 1");
	}
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 2");
	}
	sleep(1);
	printfoo("parent:\n", fp);
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

When we run this program on Linux, we get

```c++
thread 1:
 structure at 0x7f19939edf00
 foo.a = 1
 foo.b = 2
 foo.c = 3
 foo.d = 4
parent starting second thread
thread 2: ID is 139747827574528
parent:
 structure at 0x7f19939edf00
 foo.a = -1818302720
 foo.b = 32537
 foo.c = 1
 foo.d = 0
```

On Mac OS X, we get different results:

```c++
$ ./a.out
thread 1:
structure at 0x1000b6f00
foo.a = 1
foo.b = 2
foo.c = 3
foo.d = 4
parent starting second thread
thread 2: ID is 4295716864
parent:
structure at 0x1000b6f00
Segmentation fault (core dumped)
```

In this case, the memory is no longer valid when the parent tries to access the structure passed to it by the first thread that exited, and the parent is sent the `SIGSEGV` signal.

As we can see, the contents of the structure (allocated on the stack of thread `tid1`) have changed by the time the main thread can access the structure. Note how the stack of the second thread (`tid2`) has overwritten the first thread’s stack. To solve this problem, we can either use a **global structure** or allocate the structure using `malloc`.

> NOTE: 关于第二种方法即“allocate the structure using `malloc`”，在下面的“补充:[POSIX : Detached vs Joinable threads | pthread_join() & pthread_detach() examples](https://thispointer.com/posix-detached-vs-joinable-threads-pthread_join-pthread_detach-examples/)”的example中演示了写法；

### [`pthread_cancel`](https://man7.org/linux/man-pages/man3/pthread_cancel.3.html) 

One thread can request that another in the same process be canceled by calling the `pthread_cancel` function.

In the default circumstances, `pthread_cancel` will cause the thread specified by `tid` to behave as if it had called `pthread_exit` with an argument of `PTHREAD_CANCELED`. However, a thread can elect to ignore or otherwise control how it is canceled. We will discuss this in detail in Section 12.7. Note that `pthread_cancel` doesn’t wait for the thread to terminate; it merely makes the request.

### thread cleanup handlers

A thread can arrange for functions to be called when it exits, similar to the way that the [`atexit`](https://www.man7.org/linux/man-pages/man3/atexit.3.html) function (Section 7.3) can be used by a process to arrange that functions are to be called when the process exits. The functions are known as ***thread cleanup handlers***.

More than one **cleanup handler** can be established for a thread. The handlers are recorded in a stack, which means that they are executed in the reverse order from that with which they were registered.

[`void pthread_cleanup_push(void (*rtn)(void *), void *arg);`](https://man7.org/linux/man-pages/man3/pthread_cleanup_push.3.html) 

[void pthread_cleanup_pop(int execute);](https://man7.org/linux/man-pages/man3/pthread_cleanup_pop.3p.html) 

The `pthread_cleanup_push` function schedules the cleanup function, `rtn`, to be called with the single argument, `arg`, when the thread performs one of the following actions:

- Makes a call to `pthread_exit`
- Responds to a cancellation request
- Makes a call to `pthread_cleanup_pop` with a nonzero execute argument

If the `execute` argument is set to zero, the cleanup function is not called. In either case, `pthread_cleanup_pop` removes the **cleanup handler** established by the last call to `pthread_cleanup_push`.

A restriction with these functions is that, because they can be implemented as macros, they must be used in matched pairs within the same scope in a thread. The macro definition of `pthread_cleanup_push` can include a `{` character, in which case the matching `}` character is in the `pthread_cleanup_pop` definition.

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

void
cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *) arg);
}
void *
thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, (void*) "thread 1 first handler");
	pthread_cleanup_push(cleanup, (void*) "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return ((void *) 1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return ((void *) 1);
}
void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, (void*) "thread 2 first handler");
	pthread_cleanup_push(cleanup, (void*) "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *) 2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *) 2);
}
int
main(void)
{
	int err;
	pthread_t tid1, tid2;
	void *tret;
	err = pthread_create(&tid1, NULL, thr_fn1, (void *) 1);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 1");
	}
	err = pthread_create(&tid2, NULL, thr_fn2, (void *) 1);
	if (err != 0)
	{
		err_exit(err, "can’t create thread 2");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0)
	{
		err_exit(err, "can’t join with thread 1");
	}
	printf("thread 1 exit code %ld\n", (long) tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
	{
		err_exit(err, "can’t join with thread 2");
	}
	printf("thread 2 exit code %ld\n", (long) tret);
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
// gcc test.c  -lpthread

```

Running the program in Figure 11.5 on Linux or Solaris gives us

```c++
$ ./a.out
thread 1 start
thread 1 push complete
thread 2 start
thread 2 push complete
cleanup: thread 2 second handler
cleanup: thread 2 first handler
thread 1 exit code 1
thread 2 exit code 2
```

From the output, we can see that both threads start properly and exit, but that only the second thread’s **cleanup handlers** are called. Thus, if the thread terminates by returning from its start routine, its **cleanup handlers** are not called, although this behavior varies among implementations. Also note that the **cleanup handlers** are called in the reverse order from which they were installed.



If we run the same program on FreeBSD or Mac OS X, we see that the program incurs a **segmentation violation** and drops core. This happens because on these systems, `pthread_cleanup_push` is implemented as a macro that stores some context on the stack. When thread 1 returns in between the call to `pthread_cleanup_push` and the call to `pthread_cleanup_pop`, the stack is overwritten and these platforms try to use this (now corrupted) context when they invoke the **cleanup handlers**. In the Single UNIX Specification, returning while in between a matched pair of calls to `pthread_cleanup_push` and `pthread_cleanup_pop` results  in  **undefined behavior**. The only portable way to return in between these two functions is to call `pthread_exit`.

> NOTE: 上面这段话没有理解

### [`pthread_detach`](https://man7.org/linux/man-pages/man3/pthread_detach.3.html) 

By default, a thread’s termination status is retained until we call `pthread_join` for that thread. A thread’s underlying storage can be reclaimed immediately on termination if the thread has been ***detached***. After a thread is **detached**, we can’t use the `pthread_join` function to wait for its termination status, because calling `pthread_join` for a detached thread results in **undefined behavior**. We can detach a thread by calling `pthread_detach`.

As we will see in the next chapter, we can create a thread that is already in the **detached state** by modifying the **thread attributes** we pass to `pthread_create`.

## 补充:thispointer [POSIX : Detached vs Joinable threads | pthread_join() & pthread_detach() examples](https://thispointer.com/posix-detached-vs-joinable-threads-pthread_join-pthread_detach-examples/)

With every thread some resources are associated like **stack** and **thread local storage** etc. 

When a thread exits ideally these resources should be reclaimed by process automatically. But that doesn’t happens always. It depends on which **mode** thread is running. A Thread can run in two modes i.e.

- Joinable Mode
- Detached Mode

### Joinable Thread & `pthread_join()`

By default a thread runs in **joinable mode**. Joinable thread will not release any resource even after the end of thread function, until some other thread calls `pthread_join()` with its ID.

`pthread_join()` is a **blocking** call, it will block the calling thread until the other thread ends.

#### Example

```c++
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void * threadFunc(void * arg)
{
	std::cout << "Thread Function :: Start" << std::endl;
	// Sleep for 2 seconds
	sleep(2);
	std::cout << "Thread Function :: End" << std::endl;
	// Return value from thread
	return new int(6);
}
int main()
{
	// Thread id
	pthread_t threadId;
	// Create a thread that will funtion threadFunc()
	int err = pthread_create(&threadId, NULL, &threadFunc, NULL);
	// Check if thread is created sucessfuly
	if (err)
	{
		std::cout << "Thread creation failed : " << strerror(err);
		return err;
	}
	else
	{
		std::cout << "Thread Created with ID : " << threadId << std::endl;
	}
	// Do some stuff
	void * ptr = NULL;
	std::cout << "Waiting for thread to exit" << std::endl;
	// Wait for thread to exit
	err = pthread_join(threadId, &ptr);
	if (err)
	{
		std::cout << "Failed to join Thread : " << strerror(err) << std::endl;
		return err;
	}
	if (ptr)
	{
		std::cout << " value returned by thread : " << *(int *) ptr << std::endl;
	}
	delete (int *) ptr;
	return 0;
}

// g++ test.cpp -lpthread
```

**Output:**

```c++
Thread Created with ID : 140702080427776

Waiting for thread to exit

Thread Function :: Start

Thread Function :: End

 value returned by thread : 6

```

> NOTE: 上述例子是典型的thread function

### Detached Thread & `pthread_detach()`

A Detached thread automatically releases it allocated resources on exit. No other thread needs to join it. But by default all threads are joinable, so to make a thread detached we need to call **pthread_detach()** with thread id.

Also, as detached thread automatically release the resources on exit, therefore there is no way to determine its return value of detached thread function.

#### Example

```c++
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
void * threadFunc(void * arg)
{
	std::cout << "Thread Function :: Start" << std::endl;
	std::cout << "Thread Function :: End" << std::endl;
	// Return value from thread
	return NULL;
}
int main()
{
	// Thread id
	pthread_t threadId;
	// Create a thread that will funtion threadFunc()
	int err = pthread_create(&threadId, NULL, &threadFunc, NULL);
	// Check if thread is created sucessfuly
	if (err)
	{
		std::cout << "Thread creation failed : " << strerror(err);
		return err;
	}
	else
	{
		std::cout << "Thread Created with ID : " << threadId << std::endl;
	}
	// Do some stuff
	err = pthread_detach(threadId);
	if (err)
	{
		std::cout << "Failed to detach Thread : " << strerror(err) << std::endl;
	}
	// Sleep for 2 seconds because if main function exits, then other threads will
	// be also be killed. Sleep for 2 seconds, so that detached exits by then
	sleep(2);
	std::cout << "Main function ends " << std::endl;
	return 0;
}
// g++ test.cpp -lpthread
```



## 补充:stackoverflow [Detached vs. Joinable POSIX threads](https://stackoverflow.com/questions/3756882/detached-vs-joinable-posix-threads)

## Fork-join model

关于fork-join model，参见工程[parallel-computing](https://dengking.github.io/machine-learning/)的`Model\Fork–join-model.md`。

在[What does this thread join code mean?](https://stackoverflow.com/questions/15956231/what-does-this-thread-join-code-mean)对Java中的写法进行了详细分析：

```Java
Thread t1 = new Thread(new EventThread("e1"));
t1.start();
Thread t2 = new Thread(new EventThread("e2"));
t2.start();
while (true) {
   try {
      t1.join();
      t2.join();
      break;
   } catch (InterruptedException e) {
      e.printStackTrace();
   }
}
```

https://stackoverflow.com/a/15956265

> It is important to understand that the `t1` and `t2` threads have been running **in parallel** but the **main thread** that started them needs to wait for them to finish before it can continue. That's a common **pattern**. Also, `t1` and/or `t2` could have finished *before* the main thread calls `join()` on them. If so then `join()` will not wait but will return immediately.



> The loop is there to ensure that both `t1` and `t2` finish. Ie. if `t1` throws the `InterruptedException`, it will loop back and wait for `t2`. An alternative is to wait for both threads in each their Try-Catch, so the loop can be avoided. Also, depending on `EventThread`, it can make sense to do it this way, as we're running 2 threads, not one. – [Michael Bisbjerg](https://stackoverflow.com/users/1246988/michael-bisbjerg) [Jun 11 '13 at 17:05](https://stackoverflow.com/questions/15956231/what-does-this-thread-join-code-mean#comment24650271_15956265)







