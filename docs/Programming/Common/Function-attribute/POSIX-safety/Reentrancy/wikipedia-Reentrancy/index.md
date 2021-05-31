# wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing))

> NOTE: 
>
> 一、"Reentrancy"即"可重入"
>
> 二、"tag-reentrancy is a form of concurrency-race condition"
>
> 参见: 
>
> 1、`Parallel-computing\docs\Concurrent-computing\Multithread\Thread-safety\What-cause-unsafety\Race`
>
> 2、drdobbs [Use Lock Hierarchies to Avoid Deadlock](https://www.drdobbs.com/parallel/use-lock-hierarchies-to-avoid-deadlock/204801163)  

In [computing](https://en.wikipedia.org/wiki/Computing), a [computer program](https://en.wikipedia.org/wiki/Computer_program) or [subroutine](https://en.wikipedia.org/wiki/Subroutine) is called **reentrant** if it can be interrupted in the middle of its execution and then safely be called again ("re-entered") before its previous invocations complete execution. The **interruption** could be caused by an **internal action** such as a jump or call, or by an **external action** such as an [interrupt](https://en.wikipedia.org/wiki/Interrupt) or [signal](https://en.wikipedia.org/wiki/Signal_(computing)). Once the **reentered invocation** completes, the previous invocations will resume correct execution.

This definition originates from single-threaded programming environments where the **flow of control** could be interrupted by an [interrupt](https://en.wikipedia.org/wiki/Interrupt) and transferred to an [interrupt service routine](https://en.wikipedia.org/wiki/Interrupt_service_routine) (ISR). Any subroutine used by the ISR that could potentially have been executing when the interrupt was triggered should be **reentrant**. Often, subroutines accessible via the operating system [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) are not **reentrant**. Hence, **interrupt service routines** are limited in the actions they can perform; for instance, they are usually restricted from accessing the file system and sometimes even from allocating memory.



> NOTE: 意思是:当中断被触发时，ISR使用的任何可能正在执行的subroutine都应该是可重入的。通常，通过操作系统内核访问的子例程是不可重入的。因此，中断服务程序所能执行的操作是有限的; 例如，它们通常不能访问文件系统，有时甚至不能分配内存。
>
> 上面这段话中"subroutines accessible via the operating system [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) are not **reentrant**"是什么意思？
>
> 在"APUE 10.6 Reentrant Functions"章节中介绍了Reentrant Function的内容，上面这段话中描述的思想与APUE中的是一致的。



## Thread-safety and reentrancy

This definition of **reentrancy** differs from that of [thread-safety](https://en.wikipedia.org/wiki/Thread-safety) in multi-threaded environments. A **reentrant subroutine** can achieve **thread-safety**,[[1\]](https://en.wikipedia.org/wiki/Reentrancy_(computing)#cite_note-FOOTNOTEKerrisk2010[httpsbooksgooglecombooksid2SAQAQAAQBAJpgPA657_657]-1) but being **reentrant** alone might not be sufficient to be thread-safe in all situations. Conversely, thread-safe code does not necessarily have to be **reentrant** (see below for examples).

Other terms used for reentrant programs include "pure procedure" or "sharable code".[[2\]](https://en.wikipedia.org/wiki/Reentrancy_(computing)#cite_note-FOOTNOTERalston20001514%E2%80%931515-2)

> NOTE: 上面这段话中的pure  procedure，让我想到了functional programming中的pure function

---



## 从atomicity的角度来分析

**Reentrancy** of a subroutine that operates on **operating-system resources** or **non-local data** depends on the [atomicity](https://en.wikipedia.org/wiki/Atomicity_(programming)) of the respective operations. For example, if the subroutine modifies a 64-bit global variable on a 32-bit machine, the operation may be split into two 32-bit operations, and thus, if the subroutine is interrupted while executing, and called again from the **interrupt handler**, the **global variable** may be in a state where only 32 bits have been updated. The programming language might provide **atomicity** guarantees for interruption caused by an **internal action** such as a jump or call. Then the function `f` in an expression like `(global:=1) + (f())`, where the order of evaluation of the subexpressions might be arbitrary in a programming language, would see the global variable either set to 1 or to its previous value, but not in an intermediate state where only part has been updated. (The latter can happen in [C](https://en.wikipedia.org/wiki/C_programming_language), because the expression has no [sequence point](https://en.wikipedia.org/wiki/Sequence_point).) The operating system might provide **atomicity guarantees** for [signals](https://en.wikipedia.org/wiki/Signal_(computing)), such as a system call interrupted by a signal not having a partial effect. The processor hardware might provide atomicity guarantees for [interrupts](https://en.wikipedia.org/wiki/Interrupt), such as interrupted processor instructions not having **partial effects**.

> NOTE: 上面这段话，从atomicity的角度分析了reentrancy。



## Background



### Reentrancy VS thread-safety

Reentrancy is distinct from, but closely related to, [thread-safety](https://en.wikipedia.org/wiki/Thread-safety). A function can be [thread-safe](https://en.wikipedia.org/wiki/Thread-safe) and still not reentrant. For example, a function could be wrapped all around with a [mutex](https://en.wikipedia.org/wiki/Mutex) (which avoids problems in multithreading environments), but, if that function were used in an interrupt service routine, it could starve waiting for the first execution to release the mutex. The key for avoiding confusion is that reentrant refers to only *one* thread executing. It is a concept from the time when no multitasking operating systems existed.

> NOTE: 最后一段话是从时间发展的角度的总结: 
>
> Reentrancy 是在无 multitasking 时代发展出的概念，因此它只能够由一个thread执行
>
> Thread-safety 是在 multitasking  时代发展出的概念



## Rules for reentrancy

> NOTE: 原文的这一段是不容易理解的，比较晦涩，相比之下，APUE 10.6 Reentrant Functions 容易理解地多，具体可以参考其中的总结

**Reentrant code may not hold any static or global non-constant data.**

> NOTE: 需要注意的是: `static local` 也是不允许的，它同样会触发 many to one

**Reentrant code may not** [modify itself](https://en.wikipedia.org/wiki/Self-modifying_code)**.**

> NOTE: 没有读懂这一段

**Reentrant code may not call non-reentrant** [computer programs](https://en.wikipedia.org/wiki/Computer_program) **or** [routines](https://en.wikipedia.org/wiki/Subroutine)**.**



## Examples

To illustrate reentrancy, this article uses as an example a [C](https://en.wikipedia.org/wiki/C_(programming_language)) utility function, `swap()`, that takes two pointers and transposes their values, and an interrupt-handling routine that also calls the swap function.



### Neither reentrant nor thread-safe

This is an example `swap` function that fails to be **reentrant** or **thread-safe**. As such, it should not have been used in the interrupt service routine `isr()`:

```c
int tmp;

void swap(int* x, int* y)
{
    tmp = *x;
    *x = *y;
    *y = tmp;    /* Hardware interrupt might invoke isr() here. */
}

void isr()
{
    int x = 1, y = 2;
    swap(&x, &y);
}
```

> NOTE: 
>
> 1、`tmp`是**global variable**，如果在32为OS中，则`*y = tmp`就被编译为两条指令，也就是说它这条语句并不是原子的
>
> 2、第一次执行的时候，保存在**global variable** `tmp` 中的值，可能会被第二次执行的时候overwrite



### Thread-safe but not reentrant

The function `swap()` in the preceding example can be made thread-safe by making `tmp` [thread-local](https://en.wikipedia.org/wiki/Thread-local_storage). It still fails to be reentrant, and this will continue to cause problems if `isr()` is called in the same context as a thread already executing `swap()`:

> NOTE: 
>
> 1、reentrancy的function的执行，可能是同一个thread的data，因此 `_Thread_local` 无法保证reentrancy

```c
_Thread_local int tmp;

void swap(int* x, int* y)
{
    tmp = *x;
    *x = *y;
    *y = tmp;    /* Hardware interrupt might invoke isr() here. */
}

void isr()
{
    int x = 1, y = 2;
    swap(&x, &y);
}
```

### Reentrant but not thread-safe

The following (somewhat contrived(人为的)) modification of the `swap` function, which is careful to leave the global data in a consistent state at the time it exits, is reentrant; however, it is not thread-safe, since there are no locks employed, it can be interrupted at any time:

> NOTE: 
>
> 1、这个例子，让我想到了context switch
>
> 2、仔细看了这个例子，发现它能够保证Reentrant:
>
> a、第一个 invokation 执行到 `s = tmp;` 的时候，它可能是partial read
>
> b、第二个 Invokation 执行了之后，它是会恢复`tmp`的，因此第一个invokation能够接着上次的地方继续运行

```C++
int tmp;

void swap(int* x, int* y)
{
    /* Save global variable. */
    int s;
    s = tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;     /* Hardware interrupt might invoke isr() here. */

    /* Restore global variable. */
    tmp = s;
}

void isr()
{
    int x = 1, y = 2;
    swap(&x, &y);
}
```

### Reentrant and thread-safe

An implementation of `swap()` that allocates `tmp` on the [stack](https://en.wikipedia.org/wiki/Call_stack) instead of globally and that is called only with unshared variables as parameters is both thread-safe and reentrant. Thread-safe because the stack is local to a thread and a function acting just on local data will always produce the expected result. There is no access to shared data therefore no data race.

```c
void swap(int* x, int* y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;    /* Hardware interrupt might invoke isr() here. */
}

void isr()
{
    int x = 1, y = 2;
    swap(&x, &y);
}
```

## Further examples

In the following code, neither `f` nor `g` functions are reentrant.

```c
int v = 1;

int f()
{
    v += 2;
    return v;
}

int g()
{
    return f() + 2;
}
```

In the above, `f()` depends on a non-constant global variable `v`; thus, if `f()` is interrupted during execution by an ISR which modifies `v`, then reentry into `f()` will return the wrong value of `v`. The value of `v` and, therefore, the return value of `f`, cannot be predicted with confidence: they will vary depending on whether an interrupt modified `v` during `f`'s execution. Hence, `f` is not reentrant. Neither is `g`, because it calls `f`, which is not reentrant.

These slightly altered versions *are* reentrant:

```c
int f(int i)
{
    return i + 2;
}

int g(int i)
{
    return f(i) + 2;
}
```

### Thread-safe, but not reentrant: mutex

In the following, the function is thread-safe, but not reentrant:

```c
int function()
{
    mutex_lock();

    // ...
    // function body
    // ...

    mutex_unlock();
}
```

In the above, `function()` can be called by different threads without any problem. But, if the function is used in a reentrant interrupt handler and a second interrupt arises inside the function, the second routine will hang forever. As interrupt servicing can disable other interrupts, the whole system could suffer.

