# Thread Termination





## Join



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



## `pthread_join`

### man 3 [`pthread_join`](https://www.man7.org/linux/man-pages/man3/pthread_join.3.html)



### APUE 

```C++
#include <pthread.h>
void pthread_exit(void *rval_ptr);
```

The `rval_ptr` argument is a typeless pointer, similar to the single argument passed to the start routine. This pointer is available to other threads in the process by calling the `pthread_join` function.

```C++
#include <pthread.h>
int pthread_join(pthread_t thread, void **rval_ptr); // Returns: 0 if OK, error number on failure
```

> NOTE: 上述`pthread_exit`的入参`rval_ptr`与`pthread_join`的入参`rval_ptr`名称相同，它所表达的含义是：通过调用`pthread_join`来取得return value；
>
> `pthread_exit`和`pthread_join`让我想起来promise-future模型：`pthread_exit`返回future，`pthread_join`取得future

The calling thread will **block** until the specified thread calls `pthread_exit`, returns from its start routine, or is canceled. If the thread simply returned from its start routine, `rval_ptr` will contain the **return code**. If the thread was canceled, the memory location specified by `rval_ptr` is set to `PTHREAD_CANCELED`.

By calling `pthread_join`, we automatically place the thread with which we’re joining in the **detached state** (discussed shortly) so that its resources can be recovered. If the thread was already in the **detached state**, `pthread_join` can fail, returning `EINVAL`, although this behavior is implementation-specific.

If we’re not interested in a thread’s **return value**, we can set `rval_ptr` to NULL. In this case, calling `pthread_join` allows us to wait for the specified thread, but does not retrieve the thread’s **termination status**.







线程模型：根据数据结构来设计并发单位