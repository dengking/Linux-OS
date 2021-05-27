# 3.4. Creating Processes

Unix operating systems rely heavily on process creation to satisfy user requests. For example, the shell creates a new process that executes another copy of the shell whenever the user enters a command.

Traditional Unix systems treat all processes in the same way: resources owned by the parent process are duplicated in the child process. This approach makes process creation very slow and inefficient, because it requires copying the entire address space of the parent process. The child process rarely needs to read or modify all the resources inherited from the parent; in many cases, it issues an immediate  [execve( )](http://man7.org/linux/man-pages/man2/execve.2.html) and wipes out the address space that was so carefully copied.

Modern Unix kernels solve this problem by introducing three different mechanisms:

1、The [Copy On Write technique](https://en.wikipedia.org/wiki/Copy-on-write) allows both the parent and the child to read the same physical pages. Whenever either one tries to write on a physical page, the kernel copies its contents into a new physical page that is assigned to the writing process. The implementation of this technique in Linux is fully explained in Chapter 9.

2、Lightweight processes allow both the parent and the child to share many **per-process kernel data structures**, such as the **paging tables** (and therefore the entire **User Mode address space**), the open file tables, and the **signal dispositions**.

3、The  [`vfork( )`](http://man7.org/linux/man-pages/man2/vfork.2.html) system call creates a process that shares the memory address space of its parent. To prevent the parent from overwriting data needed by the child, the parent's execution is blocked until the child exits or executes a new program. We'll learn more about the  [`vfork( )`](http://man7.org/linux/man-pages/man2/vfork.2.html) system call in the following section.



## 3.4.1. The `clone( )`, `fork( )`, and `vfork( )` System Calls

**Lightweight processes** are created in Linux by using a function named  [`clone( )`](http://man7.org/linux/man-pages/man2/clone.2.html) , which uses the
following parameters:

> NOTE: 参见该函数的man page获取关于该函数的各种信息。

`fn`

Specifies a function to be executed by the new process; when the function returns, the child terminates. The function returns an integer, which represents the exit code for the child process.

`arg`

Points to data passed to the  `fn( )` function.

`flags`

Miscellaneous information. The low byte specifies the signal number to be sent to the parent process when the child terminates; the  `SIGCHLD` signal is generally selected. The remaining three bytes encode a group of **clone flags**, which are shown in Table 3-8.

`child_stack`

Specifies the **User Mode stack pointer** to be assigned to the  `esp` register of the child process. The invoking process (the parent) should always allocate a new stack for the child.

`tls`

Specifies the address of a data structure that defines a Thread Local Storage segment for the new lightweight process (see the section "The Linux GDT" in Chapter 2). Meaningful only if the `CLONE_SETTLS` flag is set.

`ptid`

Specifies the address of a **User Mode variable** of the parent process that will hold the `PID` of the new lightweight process. Meaningful only if the  `CLONE_PARENT_SETTID` flag is set.

`ctid`

Specifies the address of a User Mode variable of the new lightweight process that will hold the `PID` of such process. Meaningful only if the  `CLONE_CHILD_SETTID` flag is set.



Table 3-8. Clone flags

|Flag name |Description|
|---|---|
|`CLONE_VM` |Shares the memory descriptor and all Page Tables (see Chapter 9).|
|`CLONE_FS` |Shares the table that identifies the root directory and the current working directory, as well as the value of the bitmask used to mask the initial file permissions of a new file (the so-called file umask ).|
|`CLONE_FILES` |Shares the table that identifies the open files (see Chapter 12).|
|`CLONE_SIGHAND` |Shares the tables that identify the signal handlers and the blocked and pending signals (see Chapter 11). If this flag is true, the  CLONE_VM flag must also be set.|
|`CLONE_PTRACE` |If traced, the parent wants the child to be traced too. Furthermore, the debugger may want to trace the child on its own; in this case, the kernel forces the flag to 1.|
|`CLONE_VFORK` |Set when the system call issued is a  vfork( ) (see later in this section).|
|`CLONE_PARENT` |Sets the parent of the child ( parent and  real_parent fields in the process descriptor) to the parent of the calling process.|
|`CLONE_THREAD` |Inserts the child into the same thread group of the parent, and forces the child to share the signal descriptor of the parent. The child's  tgid and group_leader fields are set accordingly. If this flag is true, the|
|`CLONE_SIGHAND` |flag must also be set.|
|`CLONE_NEWNS` |Set if the clone needs its own namespace, that is, its own view of the mounted filesystems (see Chapter 12); it is not possible to specify both CLONE_NEWNS and  CLONE_FS .|
|`CLONE_SYSVSEM` |Shares the System V IPC undoable semaphore operations (see the section "IPC Semaphores" in Chapter 19).|
|`CLONE_SETTLS` |Creates a new Thread Local Storage (TLS) segment for the lightweight process; the segment is described in the structure pointed to by the  tls parameter.|
|`CLONE_PARENT_SETTID` |Writes the PID of the child into the User Mode variable of the parent pointed to by the  ptid parameter.|
|`CLONE_CHILD_CLEARTID` |When set, the kernel sets up a mechanism to be triggered when the child process will exit or when it will start executing a new program. In these cases, the kernel will clear the User Mode variable pointed to by the  ctid parameter and will awaken any process waiting for this event.|
|`CLONE_DETACHED` |A legacy flag ignored by the kernel.|
|`CLONE_UNTRACED` |Set by the kernel to override the value of the  CLONE_PTRACE flag (used for disabling tracing of kernel threads ; see the section "Kernel Threads" later in this chapter).|
|`CLONE_CHILD_SETTID` |Writes the PID of the child into the User Mode variable of the child pointed to by the  ctid parameter.|
|`CLONE_STOPPED` |Forces the child to start in the  TASK_STOPPED state.|



`clone( )` is actually a wrapper function defined in the C library (see the section "POSIX APIs and System Calls" in Chapter 10), which sets up the stack of the new **lightweight process** and invokes a `clone( )` system call hidden to the programmer. The  `sys_clone( )` service routine that implements the  `clone( )` system call does not have the  `fn` and  `arg` parameters. In fact, the wrapper function saves the pointer  `fn` into the child's stack position corresponding to the return address of the wrapper function itself; the pointer  `arg` is saved on the child's stack right below  `fn` . When the wrapper function terminates, the CPU fetches the return address from the stack and executes the `fn(arg)` function.

The traditional  [`fork( )`](http://man7.org/linux/man-pages/man2/fork.2.html) system call is implemented by Linux as a  `clone( )` system call whose  flags parameter specifies both a  `SIGCHLD` signal and all the clone flags cleared, and whose  `child_stack` parameter is the **current parent stack pointer**. Therefore, the parent and child temporarily share the same **User Mode stack**. But thanks to the Copy On Write mechanism, they usually get separate copies of the **User Mode stack** as soon as one tries to change the stack.

The  [`vfork( )`](http://man7.org/linux/man-pages/man2/vfork.2.html) system call, introduced in the previous section, is implemented by Linux as a  clone( ) system call whose  flags parameter specifies both a  `SIGCHLD` signal and the flags  `CLONE_VM` and `CLONE_VFORK` , and whose  `child_stack` parameter is equal to the **current parent stack pointer**.