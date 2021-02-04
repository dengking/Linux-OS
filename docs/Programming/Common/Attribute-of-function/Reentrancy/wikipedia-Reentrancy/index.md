# wikipedia [Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing))

> NOTE: "Reentrancy"即"可重入"

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

**Reentrancy** of a subroutine that operates on **operating-system resources** or **non-local data** depends on the [atomicity](https://en.wikipedia.org/wiki/Atomicity_(programming)) of the respective operations. For example, if the subroutine modifies a 64-bit global variable on a 32-bit machine, the operation may be split into two 32-bit operations, and thus, if the subroutine is interrupted while executing, and called again from the **interrupt handler**, the **global variable** may be in a state where only 32 bits have been updated. The programming language might provide **atomicity** guarantees for interruption caused by an **internal action** such as a jump or call. Then the function `f` in an expression like `(global:=1) + (f())`, where the order of evaluation of the subexpressions might be arbitrary in a programming language, would see the global variable either set to 1 or to its previous value, but not in an intermediate state where only part has been updated. (The latter can happen in [C](https://en.wikipedia.org/wiki/C_programming_language), because the expression has no [sequence point](https://en.wikipedia.org/wiki/Sequence_point).) The operating system might provide **atomicity guarantees** for [signals](https://en.wikipedia.org/wiki/Signal_(computing)), such as a system call interrupted by a signal not having a partial effect. The processor hardware might provide atomicity guarantees for [interrupts](https://en.wikipedia.org/wiki/Interrupt), such as interrupted processor instructions not having **partial effects**.

> NOTE: 上面这段话，从atomicity的角度分析了reentrancy。

## Examples

To illustrate reentrancy, this article uses as an example a [C](https://en.wikipedia.org/wiki/C_(programming_language)) utility function, `swap()`, that takes two pointers and transposes their values, and an interrupt-handling routine that also calls the swap function.

### Neither reentrant nor thread-safe

This is an example swap function that fails to be reentrant or thread-safe. As such, it should not have been used in the interrupt service routine `isr()`:

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

> NOTE: 这个例子说明的正是介绍中的情况，`tmp`就是**global variable**，如果在32为OS中，则`*y = tmp`就被编译为两条指令，也就是说它这条语句并不是原子的；

### Thread-safe but not reentrant

The function `swap()` in the preceding example can be made thread-safe by making `tmp` [thread-local](https://en.wikipedia.org/wiki/Thread-local_storage). It still fails to be reentrant, and this will continue to cause problems if `isr()` is called in the same context as a thread already executing `swap()`:

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







## Rules for reentrancy

### Reentrant code may not hold any static or global non-constant data.

Reentrant functions can work with global data. For example, a reentrant interrupt service routine could grab a piece of hardware status to work with (e.g., serial port read buffer) which is not only global, but volatile. Still, typical use of static variables and global data is not advised, in the sense that only [atomic](https://en.wikipedia.org/wiki/Atomic_(computer_science)) [read-modify-write](https://en.wikipedia.org/wiki/Read-modify-write) instructions should be used in these variables (it should not be possible for an interrupt or signal to come during the execution of such an instruction). Note that in C, even a read or write is not guaranteed to be atomic; it may be split into several reads or writes.[[3\]](https://en.wikipedia.org/wiki/Reentrancy_(computing)#cite_note-Preshing_(2013)-3) The C standard and SUSv3 provide `sig_atomic_t` for this purpose, although with guarantees only for simple reads and writes, not for incrementing or decrementing.[[4\]](https://en.wikipedia.org/wiki/Reentrancy_(computing)#cite_note-FOOTNOTEKerrisk2010[httpsbooksgooglecombooksid2SAQAQAAQBAJpgPA428_428]-4) More complex atomic operations are available in [C11](https://en.wikipedia.org/wiki/C11_(C_standard_revision)), which provides `stdatomic.h`.



### Reentrant code may not [modify itself](https://en.wikipedia.org/wiki/Self-modifying_code).



The operating system might allow a process to modify its code. There are various reasons for this (e.g., [blitting](https://en.wikipedia.org/wiki/Blitting) graphics quickly) but this would cause a problem with reentrancy, since the code might not be the same next time.

It may, however, modify itself if it resides in its own unique memory. That is, if each new invocation uses a different physical machine code location where a copy of the original code is made, it will not affect other invocations even if it modifies itself during execution of that particular invocation (thread).

### Reentrant code may not call non-reentrant [computer programs](https://en.wikipedia.org/wiki/Computer_program) or [routines](https://en.wikipedia.org/wiki/Subroutine).

Multiple levels of user, object, or process [priority](https://en.wikipedia.org/wiki/Priority_queue) or [multiprocessing](https://en.wikipedia.org/wiki/Multiprocessing) usually complicate the control of reentrant code. It is important to keep track of any access or side effects that are done inside a routine designed to be reentrant.





# [Sharing global variables with multiple Interrupt Service Routines](https://www.microchip.com/forums/m921817.aspx)





