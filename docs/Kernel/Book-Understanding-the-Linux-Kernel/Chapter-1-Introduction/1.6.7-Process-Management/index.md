# 1.6.7. Process Management

Unix makes a neat distinction between the **process** and the **program** it is executing. To that end, the [fork( )](http://man7.org/linux/man-pages/man2/fork.2.html) and  [_exit( )](http://man7.org/linux/man-pages/man2/_exit.2.html) system calls are used respectively to create a new process and to terminate it, while an  [exec( )](http://man7.org/linux/man-pages/man3/exec.3.html) -like system call is invoked to load a new program. After such a system call is executed, the process resumes execution with a brand new address space containing the loaded program.

The process that invokes a  [fork( )](http://man7.org/linux/man-pages/man2/fork.2.html)  is the *parent*, while the new process is its *child*. Parents and children can find one another because the data structure describing each process includes a pointer to its immediate parent and pointers to all its immediate children.

A naive implementation of the  `fork( )` would require both the parent's data and the parent's code to be duplicated and the copies assigned to the child. This would be quite time consuming. Current kernels that can rely on hardware paging units follow the *Copy-On-Write* approach, which defers page duplication until the last moment (i.e., until the parent or the child is required to write into a page). We shall describe how Linux implements this technique in the section "Copy On Write" in Chapter 9.

The  `_exit( )` system call terminates a process. The kernel handles this system call by releasing the resources owned by the process and sending the parent process a  `SIGCHLD` signal, which is ignored
by default.

## 1.6.7.1. Zombie processes

How can a parent process inquire about termination of its children? The  [wait4( )](http://man7.org/linux/man-pages/man2/wait4.2.html) system call allows a process to wait until one of its children terminates; it returns the process ID (PID) of the terminated child.

When executing this system call, the kernel checks whether a child has already terminated. A special zombie process state is introduced to represent terminated processes: a process remains in that state until its parent process executes a  `wait4( )` system call on it. The system call handler extracts(提取) data about resource usage from the **process descriptor** fields; the **process descriptor** may be released once the data is collected. If no child process has already terminated when the  `wait4( )` system call is executed, the kernel usually puts the process in a wait state until a child terminates.

Many kernels also implement a  `waitpid( )` system call, which allows a process to wait for a specific child process. Other variants of  `wait4( )` system calls are also quite common.

It's good practice for the kernel to keep around information on a child process until the parent issues its  `wait4( )` call, but suppose the parent process terminates without issuing that call? The information takes up valuable memory slots that could be used to serve living processes. For example, many shells allow the user to start a command in the background and then log out. The process that is running the command shell terminates, but its children continue their execution.

The solution lies in a special system process called **init**, which is created during system initialization. When a process terminates, the kernel changes the appropriate process descriptor pointers of all the existing children of the terminated process to make them become children of **init**. This process monitors the execution of all its children and routinely issues  `wait4( )` system calls, whose side effect is to get rid of all orphaned zombies.



## 1.6.7.2. Process groups and login sessions

Modern Unix operating systems introduce the notion of process groups to represent a "job" abstraction. For example, in order to execute the command line:

```shell
$ ls | sort | more
```

a shell that supports **process groups**, such as  **bash** , creates a new group for the three processes corresponding to  `ls` ,  `sort` , and  `more` . In this way, the shell acts on the three processes as if they were a single entity (the **job**, to be precise). Each **process descriptor** includes a field containing the **process group ID** . Each group of processes may have a **group leader**, which is the process whose PID coincides with the **process group ID**. A newly created process is initially inserted into the process group of its parent.

Modern Unix kernels also introduce **login sessions**. Informally, a **login session** contains all processes that are descendants of the process that has started a working session on a specific terminal usually, the first command shell process created for the user. All processes in a **process group** must be in the same **login session**. A login session may have several process groups active simultaneously; one of these process groups is always in the foreground, which means that it has access to the terminal. The other active process groups are in the background. When a background process tries to access the terminal, it receives a  `SIGTTIN` or  `SIGTTOUT` signal. In many command shells, the internal commands  [`bg`](http://man7.org/linux/man-pages/man1/bg.1p.html) and  [`fg`](http://man7.org/linux/man-pages/man1/fg.1p.html) can be used to put a process group in either the background or the foreground.

