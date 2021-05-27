# 3.4.2. Kernel Threads

Traditional Unix systems delegate some critical tasks to intermittently(间歇地) running processes, including
flushing disk caches, swapping out unused pages, servicing network connections, and so on. Indeed, it is not efficient to perform these tasks in strict linear fashion; both their functions and the end user processes get better response if they are scheduled in the **background**. Because some of the **system processes** run only in **Kernel Mode**, modern operating systems delegate their functions to **kernel threads** , which are not encumbered(阻碍) with the unnecessary **User Mode context**. In Linux, **kernel threads** differ from regular processes in the following ways:

1、**Kernel threads** run **only** in **Kernel Mode**, while regular processes run alternatively in Kernel
Mode and in **User Mode**.

2、Because kernel threads run only in Kernel Mode, they use only linear addresses greater than `PAGE_OFFSET` . Regular processes, on the other hand, use all four gigabytes of linear addresses, in either User Mode or Kernel Mode.

> NOTE:  : 需要注意的是，不是所有的system process都运行在kernel mode；

> NOTE:  : 上面这段话中的user mode context所指的是什么？

## 3.4.2.1. Creating a kernel thread

The  `kernel_thread( )` function creates a new kernel thread. It receives as parameters the address of the kernel function to be executed ( `fn` ), the argument to be passed to that function ( `arg` ), and a set of clone flags ( `flags` ). The function essentially invokes  `do_fork( )` as follows:

```c
do_fork(flags|CLONE_VM|CLONE_UNTRACED, 0, pregs, 0, NULL, NULL);
```

The  `CLONE_VM` flag avoids the duplication of the page tables of the calling process: this duplication would be a waste of time and memory, because the new kernel thread will not access the **User Mode address space** anyway. The  `CLONE_UNTRACED` flag ensures that no process will be able to trace the new kernel thread, even if the calling process is being traced.

> NOTE:  ：bootlin [kernel_thread](https://elixir.bootlin.com/linux/v2.6.11/source/arch/m68k/kernel/process.c#L154)

The  `pregs` parameter passed to  `do_fork( )` corresponds to the address in the **Kernel Mode stack** where the  `copy_thread( )` function will find the initial values of the CPU registers for the new thread. The  `kernel_thread( )` function builds up this stack area so that:

1、The  `ebx` and  `edx` registers will be set by  `copy_thread()` to the values of the parameters  `fn` and `arg` , respectively.

2、The  `eip` register will be set to the address of the following assembly language fragment:

```assembly
movl %edx,%eax
pushl %edx
call *%ebx
pushl %eax
call do_exit
```



Therefore, the new kernel thread starts by executing the  `fn(arg)` function. If this function terminates, the kernel thread executes the  `_exit( )` system call passing to it the return value of  `fn()` (see the section "Destroying Processes" later in this chapter).



## 3.4.2.2. Process 0

The ancestor of all processes, called ***process 0***, the ***idle process***, or, for historical reasons, the ***swapper process***, is a **kernel thread** created from scratch during the initialization phase of Linux (see Appendix A). This ancestor process uses the following **statically allocated data structures** (data structures for all other processes are dynamically allocated):



> NOTE:  : **statically allocated data structures** (data structures for all other processes are dynamically allocated)的具体含义是什么？它有什么特别之处呢？

1、A process descriptor stored in the  `init_task` variable, which is initialized by the  `INIT_TASK` macro.

2、A  `thread_info` descriptor and a Kernel Mode stack stored in the  `init_thread_union` variable and initialized by the  `INIT_THREAD_INFO` macro.

3、The following tables, which the process descriptor points to:

- `init_mm`
- `init_fs`
- `init_files`
- `init_signals`
- `init_sighand`

The tables are initialized, respectively, by the following macros:

- `INIT_MM`
- `INIT_FS`
- `INIT_FILES`
- `INIT_SIGNALS`
- `INIT_SIGHAND`

- The master kernel **Page Global Directory** stored in  `swapper_pg_dir` (see the section "Kernel Page Tables" in Chapter 2).



The  `start_kernel( )` function initializes all the data structures needed by the kernel, enables interrupts, and creates another **kernel thread**, named **process 1** (more commonly referred to as the ***init process*** ):

```c
kernel_thread(init, NULL, CLONE_FS|CLONE_SIGHAND);
```

The newly created kernel thread has PID 1 and shares all per-process kernel data structures with **process 0**. When selected by the scheduler, the **init process** starts executing the  `init( )` function.

After having created the **init process**, **process 0** executes the  `cpu_idle( )` function, which essentially consists of repeatedly executing the  `hlt` assembly language instruction with the interrupts enabled (see Chapter 4). **Process 0** is selected by the scheduler only when there are no other processes in the  `TASK_RUNNING` state.

In multiprocessor systems there is a **process 0** for each CPU. Right after the power-on, the BIOS of the computer starts a single CPU while disabling the others. The **swapper process** running on CPU 0 initializes the kernel data structures, then enables the other CPUs and creates the additional **swapper processes** by means of the  `copy_process( )` function passing to it the value 0 as the new `PID`. Moreover, the kernel sets the  `cpu` field of the  `thread_info` descriptor of each forked process to the proper CPU index.

## 3.4.2.3. Process 1

The kernel thread created by process 0 executes the  `init( )` function, which in turn completes the initialization of the kernel. Then  `init( )` invokes the  `execve( )` system call to load the executable program `init`. As a result, the `init` kernel thread becomes a regular process having its own **per-process kernel data structure** (see Chapter 20). The `init` process stays alive until the system is shut down, because it creates and monitors the activity of all processes that implement the outer layers of the operating system.

## 3.4.2.4. Other kernel threads

Linux uses many other **kernel threads**. Some of them are created in the initialization phase and run until shutdown; others are created "on demand," when the **kernel** must execute a task that is better performed in its own **execution context**.

A few examples of kernel threads (besides process 0 and process 1) are:

`keventd` (also called events)

Executes the functions in the  `keventd_wq` workqueue (see Chapter 4).

`kapmd`

Handles the events related to the Advanced Power Management (APM).

`kswapd`

Reclaims memory, as described in the section "Periodic Reclaiming" in Chapter 17.

`pdflush`

Flushes "dirty" buffers to disk to reclaim（回收再利用） memory, as described in the section "The pdflush Kernel Threads" in Chapter 15.

`kblockd`

Executes the functions in the  `kblockd_workqueue` workqueue. Essentially, it periodically activates the block device drivers, as described in the section "Activating the Block Device Driver" in Chapter 14.

`ksoftirqd`

Runs the tasklets (see section "Softirqs and Tasklets" in Chapter 4); there is one of these kernel threads for each CPU in the system.

