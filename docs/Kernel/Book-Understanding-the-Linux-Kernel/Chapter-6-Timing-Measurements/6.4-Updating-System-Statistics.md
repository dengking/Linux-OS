# 6.4. Updating System Statistics

The kernel, among the other time-related duties, must periodically collect various data used for:

- Checking the CPU resource limit of the running processes
- Updating statistics about the local CPU workload
- Computing the average system load
- Profiling the kernel code

> NOTE: 在`Shell-and-tools\Tools\Performance`章节中，介绍了很多用于监控Linux OS的工具，显然这些工具的实现是依赖于本章介绍的kernel的这个特性的。

## 6.4.1. Updating Local CPU Statistics

We have mentioned that the  update_process_times( ) function is invoked either by the **global timer interrupt handler** on uniprocessor systems or by the **local timer interrupt handler** in multiprocessor systems to update some kernel statistics. This function performs the following steps:

1 

Checks how long the current process has been running. Depending on whether the current process was running in User Mode or in Kernel Mode when the **timer interrupt** occurred, invokes either  `account_user_time( )` or  `account_system_time( )` . Each of these functions performs essentially the following steps:

a. 

Updates either the  `utime` field (ticks spent in **User Mode**) or the  `stime` field (ticks spent in **Kernel Mode**) of the **current process descriptor**. Two additional fields called  `cutime` and `cstime` are provided in the **process descriptor** to count the number of CPU ticks spent by the **process children** in User Mode and Kernel Mode, respectively. For reasons of efficiency, these fields are not updated by  `update_process_times( ) ,` but rather when the parent process queries the state of one of its children (see the section "Destroying Processes" in Chapter 3).

b. 

Checks whether the total CPU time limit has been reached; if so, sends  `SIGXCPU` and `SIGKILL` signals to  current . The section "Process Resource Limits" in Chapter 3 describes how the limit is controlled by the  `signal->rlim[RLIMIT_CPU].rlim_cur` field of each process descriptor.

c.

Invokes  `account_it_virt( )` and  `account_it_prof( )` to check the process timers (see the section "The `setitimer( )` and `alarm( )` System Calls" later in this chapter).

d. 

Updates some kernel statistics stored in the  `kstat` per-CPU variable. 

2

Invokes  `raise_softirq( )` to activate the  `TIMER_SOFTIRQ` tasklet on the local CPU (see the section "Software Timers and Delay Functions" later in this chapter).

> NOTE: tasklet在4.7. Softirqs and Tasklets中有介绍，另外参见：
>
> - [Deferrable functions, kernel tasklets, and work queues](https://developer.ibm.com/tutorials/l-tasklets/) 
> - [Multitasking in the Linux Kernel. Interrupts and Tasklets](https://kukuruku.co/post/multitasking-in-the-linux-kernel-interrupts-and-tasklets/)



3 

If some old version of an RCU-protected data structure has to be reclaimed, checks whether the local CPU has gone through a quiescent state and invokes  `tasklet_schedule( )` to activate the  `rcu_tasklet` tasklet of the local CPU (see the section "Read-Copy Update (RCU)" in Chapter 5).

4 

Invokes the  `scheduler_tick( )` function, which decreases the time slice counter of the current process, and checks whether its **quantum** is exhausted. We'll discuss in depth these operations in the section "The `scheduler_tick( )` Function" in Chapter 7.

> NOTE: **quantum**在7.1. Scheduling Policy中定义；



## 6.4.2. Keeping Track of System Load

Every Unix kernel keeps track of how much CPU activity is being carried on by the system. These statistics are used by various administration utilities such as  `top` . A user who enters the  `uptime` command sees the statistics as the "load average" relative to the last minute, the last 5 minutes, and the last 15 minutes. On a uniprocessor system, a value of 0 means that there are no active processes (besides **the swapper process 0**) to run, while a value of 1 means that the CPU is 100 percent busy with a single process, and values greater than 1 mean that the CPU is shared among several active processes. [`*`]

> [`*`] Linux includes in the load average all processes that are in the  `TASK_RUNNING` and  `TASK_UNINTERRUPTIBLE` states. However, under normal conditions, there are few  `TASK_UNINTERRUPTIBLE` processes, so a high load usually means that the CPU is busy.

At every tick,  `update_times( )` invokes the  `calc_load( )` function, which counts the number of
processes in the  `TASK_RUNNING` or  `TASK_UNINTERRUPTIBLE` state and uses this number to update the average system load.

## 6.4.3. Profiling the Kernel Code

Linux includes a minimalist（简单的） code profiler called `readprofile` used by Linux developers to discover where the kernel spends its time in **Kernel Mode**. The profiler identifies the *hot* spots of the kernel
the most frequently executed fragments of kernel code. Identifying the **kernel hot spots** is very important, because they may point out kernel functions that should be further optimized.

The **profiler** is based on a simple [Monte Carlo algorithm](https://en.wikipedia.org/wiki/Monte_Carlo_algorithm): at every timer interrupt occurrence, the
kernel determines whether the interrupt occurred in Kernel Mode; if so, the kernel fetches the value
of the  `eip` register before the interruption from the stack and uses it to discover what the kernel was
doing before the interrupt. In the long run, the samples accumulate on the hot spots.

> NOTE : 关于为什么使用`eip` register，可以参见：
>
> - [4. EIP Instruction Pointer Register](http://www.c-jump.com/CIS77/ASM/Instructions/I77_0040_instruction_pointer.htm)
>
> - [What does EIP stand for?](https://security.stackexchange.com/questions/129499/what-does-eip-stand-for)



The  `profile_tick( )` function collects the data for the code profiler. It is invoked either by the `do_timer_interrupt( )` function in uniprocessor systems (by the global timer interrupt handler) or
by the  `smp_local_timer_interrupt( )` function in multiprocessor systems (by the local timer interrupt handler).

To enable the code profiler, the Linux kernel must be booted by passing as a parameter the string `profile=N` , where $2^N$ denotes the size of the code fragments to be profiled. The collected data can be read from the `/proc/profile` file. The counters are reset by writing in the same file; in multiprocessor
systems, writing into the file can also change the sample frequency (see the earlier section "Timekeeping Architecture in Multiprocessor Systems"). However, kernel developers do not usually access `/proc/profile` directly; instead, they use the `readprofile` system command.

The Linux 2.6 kernel includes yet another profiler called `oprofile`. Besides being more flexible and customizable than `readprofile`, `oprofile` can be used to discover hot spots in kernel code, User Mode
applications, and system libraries. When `oprofile` is being used,  `profile_tick( )` invokes the `timer_notify( )` function to collect the data used by this new profiler.

## 6.4.4. Checking the NMI Watchdogs

In multiprocessor systems, Linux offers yet another feature to kernel developers: a watchdog system, which might be quite useful to detect kernel bugs that cause a system freeze. To activate such a watchdog, the kernel must be booted with the  `nmi_watchdog` parameter.

The watchdog is based on a clever hardware feature of local and I/O APICs: they can generate periodic NMI interrupts on every CPU. Because NMI interrupts are not masked by the  cli assembly language instruction, the watchdog can detect deadlocks even when interrupts are disabled.

