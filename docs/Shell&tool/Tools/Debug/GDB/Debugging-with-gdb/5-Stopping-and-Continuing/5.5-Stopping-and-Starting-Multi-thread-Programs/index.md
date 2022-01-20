# [5.5 Stopping and Starting Multi-thread Programs](https://sourceware.org/gdb/current/onlinedocs/gdb/Thread-Stops.html#Thread-Stops)

> NOTE: 是在阅读 csdn [线程的查看以及利用gdb调试多线程](https://blog.csdn.net/zhangye3017/article/details/80382496) 发现的这个topic。

There are two modes of controlling execution of your program within the debugger.

| Mode     | Explanation                                                  | Is default |
| -------- | ------------------------------------------------------------ | ---------- |
| all-stop | When any thread in your program stops (for example, at a breakpoint or while being stepped), all other threads in the program are also stopped by gdb. | yes        |
| non-stop | Other threads can continue to run freely while you examine the stopped thread in the debugger. |            |



## [5.5.1 All-Stop Mode](https://sourceware.org/gdb/current/onlinedocs/gdb/All_002dStop-Mode.html#All_002dStop-Mode)

> NOTE: 
>
> 在 [How does gdb multi-thread debugging coordinate with Linux thread scheduling?](https://stackoverflow.com/questions/50055181/how-does-gdb-multi-thread-debugging-coordinate-with-linux-thread-scheduling) # [A](https://stackoverflow.com/a/50055234/10173843) 中对all-stop mode有着比较好的描述
>
> > By default, GDB operates in all-stop mode. That means that all threads are *stopped* whenever you see the `(gdb)` prompt. Switching between 2 stopped threads doesn't need any coordination with the kernel, because kernel will not run non-runnable (stopped) threads.
>
> 需要注意的是: gdb 的 all-stop mode的本质含义是: 当一个thread被stop的时候，所有的其他的thread都被stop。
>
> 默认情况下gdb的breakpoint仅仅适用于当前线程，如果不进行显示的说明，其他thread是不会使用这个breakpoint，包括新线程。关于新线程，在 stackoverflow [gdb how to break in new thread when debugging multi threaded daemon program on linux](https://stackoverflow.com/questions/55067510/gdb-how-to-break-in-new-thread-when-debugging-multi-threaded-daemon-program-on-l) 中对此进行了讨论。

Conversely, whenever you restart the program, all threads start executing. This is true even when single-stepping with commands like step or next.

> NOTE: 上面这段话的意思是：一旦开始program，则所有的thread开始执行，即使是你正在单步调试一个thread，其他的thread依旧在正常执行。

In particular, gdb cannot single-step all threads in lockstep. Since thread scheduling is up to your debugging target’s operating system (not controlled by gdb), other threads may execute more than one statement while the current thread completes a single step. Moreover, in general other threads stop in the middle of a statement, rather than at a clean statement boundary, when the program stops.

> NOTE: gdb能够实现所有thread的 同时停止，但是没有办法保证所有的thread的execution进行控制，这是因为“thread scheduling is up to your debugging target’s operating system (not controlled by gdb)”，比如gdb无法实现下面的这些控制:
>
> - 所有的thread都single-step next（可以实现single-step某个指定thread，下面会进行介绍）
>
>   

### Scheduler-locking mode

On some OSes, you can modify gdb’s default behavior by locking the OS scheduler to allow only a single thread to run.

> NOTE: 在某些情况下，我们仅仅希望一个thread运行，其他的thread都stop，gdb也为user提供了这种power。

**`set scheduler-locking mode`** 

Set the scheduler locking mode. It applies to **normal execution**, **record mode**, and **replay mode**. 

If it is off, then there is no **locking** and any thread may run at any time. 

If on, then only the **current thread** may（之所以使用**may**修饰是因为scheduler是由OS来实现的） run when the inferior is resumed. The step mode optimizes for single-stepping; it prevents other threads from preempting the **current thread** while you are stepping, so that the focus of debugging does not change unexpectedly. Other threads never get a chance to run when you step, and they are completely free to run when you use commands like ‘`continue`’, ‘`until`’, or ‘`finish`’. However, unless another thread hits a breakpoint during its timeslice, gdb does not change the **current thread** away from the thread that you are debugging. 

> NOTE: 上面这段话的意思是：当开启`scheduler-locking`的时候，只有current thread能够被执行，在这种情况下，user可以single-step current thread，因此实现了“the focus of debugging does not change unexpectedly”；当执行 ‘`continue`’, ‘`until`’, or ‘`finish`’等指令的后，则其他thread都开始执行了，那这是否相当于关闭了`scheduler-locking`？不是的，在这种情况下执行 ‘`continue`’, ‘`until`’, or ‘`finish`’等指令，表示我们已经完成了current thread的debug，可以debug其他thread了。当另外thread hit breakpoint后，我们可以single-step那个thread了。显然，当开启scheduler-locking mode，则进入了上述执行模式。
>
> 总的来说，通过scheduler-locking，我们可以实现single-step single thread。

The **replay mode** behaves like off in **record mode** and like on in replay mode.

> NOTE: 这段话没有理解

**`show scheduler-locking`** 

Display the current scheduler locking mode.

**Example**

- csdn [线程的查看以及利用gdb调试多线程](https://blog.csdn.net/zhangye3017/article/details/80382496)

### Schedule-multiple mode

By default, when you issue one of the execution commands such as `continue`, `next` or `step`, gdb allows only threads of the **current inferior** to run. 

For example, if gdb is attached to two inferiors, each with two threads, the `continue` command resumes only the two threads of the **current inferior**. This is useful, for example, when you debug a program that forks and you want to hold the parent stopped (so that, for instance, it doesn’t run to exit), while you debug the child. In other situations, you may not be interested in inspecting
the current state of any of the processes gdb is attached to, and you may want to resume them all until some breakpoint is hit. In the latter case, you can instruct gdb to allow all threads of all the inferiors to run with the `set schedule-multiple` command.

**`set schedule-multiple`** 



## [5.5.2 Non-Stop Mode](https://sourceware.org/gdb/onlinedocs/gdb/Non_002dStop-Mode.html#Non_002dStop-Mode)



## [5.5.3 Background Execution](https://sourceware.org/gdb/onlinedocs/gdb/Background-Execution.html#Background-Execution)

> NOTE: 非常类似于shell中的做法

gdb’s execution commands have two variants:

| Mode                      | Explanation                                                  | Is default |
| ------------------------- | ------------------------------------------------------------ | ---------- |
| foreground (synchronous)  | gdb waits for the program to report that some thread has stopped before prompting for another command. | yes        |
| background (asynchronous) | gdb immediately gives a command prompt so that you can issue other commands while your program runs. |            |

To specify background execution, add a `&` to the command.

## [5.5.4 Thread-Specific Breakpoints](https://sourceware.org/gdb/onlinedocs/gdb/Thread_002dSpecific-Breakpoints.html#Thread_002dSpecific-Breakpoints)



```shell
break location thread thread-id
break location thread thread-id if ...
```

**Example**

- [Multithreaded Debugging Techniques](https://www.drdobbs.com/cpp/multithreaded-debugging-techniques/199200938?pgno=6)

