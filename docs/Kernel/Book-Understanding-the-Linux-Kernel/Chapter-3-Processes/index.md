# Chapter 3. Processes

The concept of a ***process*** is fundamental to any ***multiprogramming*** operating system. A process is usually defined as an instance of a program in execution; thus, if 16 users are running vi at once, there are 16 separate processes (although they can share the same executable code). Processes are often called *tasks* or *threads* in the Linux source code.

> 注意，*tasks* 和 *threads* 都是复数形式，它表示一个process由多个task或者thread来组成；在3.2. Process Descriptor中介绍了`task_struct`，作者将它叫做*process descriptor*，其实这是比较容易对读者造成误解的，我觉得叫他task最最准确，当然它更加接近于thread；以下两篇文章对这个问题进行了非常好的分析：
>
> stackoverflow [Process Control Block , Process Descriptor in Linux and task_struct?](https://stackoverflow.com/questions/47832778/process-control-block-process-descriptor-in-linux-and-task-struct)
>
> Neither of those terms ("Process Control Block" or "Process Descriptor") are considered "terms of art" in Linux kernel development. Of course, there is no official Linux kernel glossary so people are free to call things whatever makes sense to them.
>
> In contrast, however, `task_struct` is a specific C structure that is used by the linux kernel to maintain state about a *task*. A task in Linux corresponds roughly to a thread.
>
> Each user process has at least one thread so each process maps to one or more `task_structs`. More particularly, a process is one or more tasks that happen to share certain resources -- file descriptors, address space / memory map, signal handling, process and process group IDs, etc. Each thread in a process has its own individual version of certain other resources: registers/execution context, scheduling parameters, and so forth.
>
> It's quite common for a process to have only a single thread. In that case, you could consider a process to be represented by a single `task_struct`.
>
> > NOTE: process model-process thread-非常好的总结
>
> stackexchange [How does Linux tell threads apart from child processes?](https://unix.stackexchange.com/questions/434092/how-does-linux-tell-threads-apart-from-child-processes)
>
> From a `task_struct` perspective, a process’s threads have the same **thread group leader** ([`group_leader` in `task_struct`](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/sched.h#n697)), whereas child processes have a different **thread group leader** (each individual child process).
>
> This information is exposed to user space *via* the `/proc` file system. You can trace parents and children by looking at the `ppid` field in `/proc/${pid}/stat` or `.../status` (this gives the parent pid); you can trace threads by looking at the `tgid` field in `.../status` (this gives the thread group id, which is also the group leader’s pid). A process’s threads are made visible in the `/proc/${pid}/task`directory: each thread gets its own subdirectory. (Every process has at least one thread.)
>
> In practice, programs wishing to keep track of *their own threads* would rely on APIs provided by the threading library they’re using, instead of using OS-specific information. Typically on Unix-like systems that means using pthreads.
>
> 上面这段话中所提及的**thread group**在3.1. Processes, Lightweight Processes, and Threads中给出定义， **thread group leader**在3.2.2. Identifying a Process中给出定义。

In this chapter, we discuss static properties of processes and then describe how ***process switching*** is performed by the kernel. The last two sections describe how processes can be created and destroyed. We also describe how Linux supports multithreaded applications as mentioned in Chapter 1, it relies on so-called *lightweight processes (LWP)*.

