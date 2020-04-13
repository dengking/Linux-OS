# [CREDENTIALS(7)](http://man7.org/linux/man-pages/man7/credentials.7.html)





## DESCRIPTION

### Process ID (PID)

Each process has a unique nonnegative integer identifier that is assigned when the process is created using [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html).  A process can obtain its PID using [getpid(2)](http://man7.org/linux/man-pages/man2/getpid.2.html).  A PID is represented using the type `pid_t` (defined in `<sys/types.h>`).

PIDs are used in a range of system calls to identify the process affected by the call, for example: [	](http://man7.org/linux/man-pages/man2/kill.2.html), [ptrace(2)](http://man7.org/linux/man-pages/man2/ptrace.2.html), [setpriority(2)](http://man7.org/linux/man-pages/man2/setpriority.2.html) [setpgid(2)](http://man7.org/linux/man-pages/man2/setpgid.2.html), [setsid(2)](http://man7.org/linux/man-pages/man2/setsid.2.html), [sigqueue(3)](http://man7.org/linux/man-pages/man3/sigqueue.3.html), and [waitpid(2)](http://man7.org/linux/man-pages/man2/waitpid.2.html).

A process's PID is preserved across an [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html).











### Process group ID and session ID

Each process has a **session ID** and a **process group ID**, both represented using the type `pid_t`.  A process can obtain its session ID using [getsid(2)](http://man7.org/linux/man-pages/man2/getsid.2.html), and its process group ID using [getpgrp(2)](http://man7.org/linux/man-pages/man2/getpgrp.2.html).

A child created by [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html) inherits its parent's **session ID** and **process group ID**.  A process's session ID and process group ID are preserved across an [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html).

Sessions and process groups are abstractions devised to support **shell job control**.  A **process group** (sometimes called a "**job**") is a collection of processes that share the same **process group ID**; the shell creates a new process group for the process(es) used to execute single command or pipeline (e.g., the two processes created to execute the command "`ls | wc`" are placed in the same process group). A process's group membership can be set using [setpgid(2)](http://man7.org/linux/man-pages/man2/setpgid.2.html).  The process whose process ID is the same as its process group ID is the **process group leader** for that group.

A session is a collection of processes that share the same session ID.  All of the members of a process group also have the same **session ID** (i.e., all of the members of a process group always belong to the
same session, so that sessions and process groups form a strict two-level hierarchy of processes.)  A new session is created when a process calls [setsid(2)](http://man7.org/linux/man-pages/man2/setsid.2.html), which creates a new session whose session ID is the same as the PID of the process that called [setsid(2)](http://man7.org/linux/man-pages/man2/setsid.2.html).  The creator of the session is called the **session leader**.

All of the processes in a session **share** a **controlling terminal**.  The **controlling terminal** is established when the **session leader** first opens a **terminal** (unless the `O_NOCTTY` flag is specified when calling `open(2)`).  A terminal may be the **controlling terminal** of at most one session.

***SUMMARY*** : 如果session leader不去open terminal，则这个session就没有controlling terminal了；

At most one of the jobs in a session may be the **foreground job**; other jobs in the session are **background jobs**.  Only the foreground job may read from the terminal; when a process in the background attempts to
read from the terminal, its process group is sent a SIGTTIN signal,  which suspends the job.  If the TOSTOP flag has been set for the terminal (see termios(3)), then only the foreground job may write to the terminal; writes from background job cause a SIGTTOU signal to be generated, which suspends the job.  When terminal keys that generate a signal (such as the interrupt key, normally control-C) are pressed, the signal is sent to the processes in the foreground job.

Various system calls and library functions may operate on all members of a process group, including kill(2), killpg(3), getpriority(2), setpriority(2), ioprio_get(2), ioprio_set(2), waitid(2), and waitpid(2).  See also the discussion of the F_GETOWN, F_GETOWN_EX, F_SETOWN, and F_SETOWN_EX operations in fcntl(2).