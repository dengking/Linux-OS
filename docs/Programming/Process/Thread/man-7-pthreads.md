# [PTHREADS(7)](http://man7.org/linux/man-pages/man7/pthreads.7.html)

## NAME

pthreads - POSIX threads

## DESCRIPTION         

POSIX.1 specifies a set of interfaces (functions, header files) for threaded programming commonly known as POSIX threads, or Pthreads.  A single process can contain multiple threads, all of which are executing the same program.  These threads share the same global memory (data and heap segments), but each thread has its own **stack** (automatic variables).



POSIX.1 also requires that threads share a range of other attributes (i.e., these attributes are process-wide rather than per-thread):

-  process ID

-  parent process ID

-  process group ID and session ID

-  controlling terminal

-  user and group IDs

-  open file descriptors

-  record locks (see [fcntl(2)](http://man7.org/linux/man-pages/man2/fcntl.2.html))

-  signal dispositions

-  file mode creation mask ([umask(2)](http://man7.org/linux/man-pages/man2/umask.2.html))

-  current directory ([chdir(2)](http://man7.org/linux/man-pages/man2/chdir.2.html)) and root directory ([chroot(2)](http://man7.org/linux/man-pages/man2/chroot.2.html))

-  interval timers ([setitimer(2)](http://man7.org/linux/man-pages/man2/setitimer.2.html)) and POSIX timers ([timer_create(2)](http://man7.org/linux/man-pages/man2/timer_create.2.html))

-  nice value ([setpriority(2)](http://man7.org/linux/man-pages/man2/setpriority.2.html))

-  resource limits ([setrlimit(2)](http://man7.org/linux/man-pages/man2/setrlimit.2.html))

- measurements of the consumption of CPU time ([times(2)](http://man7.org/linux/man-pages/man2/times.2.html)) and resources ([getrusage(2)](http://man7.org/linux/man-pages/man2/getrusage.2.html))

  ***SUMMARY*** : 如何统计the consumption of CPU of a thread？参见[PTHREAD_GETCPUCLOCKID(3)](http://man7.org/linux/man-pages/man3/pthread_getcpuclockid.3.html)



As well as the stack, POSIX.1 specifies that various other attributes  are distinct for each thread, including:

-  thread ID (the `pthread_t` data type)

-  signal mask ([pthread_sigmask(3)](http://man7.org/linux/man-pages/man3/pthread_sigmask.3.html))

-  the [`errno`](http://man7.org/linux/man-pages/man3/errno.3.html) variable

-  alternate signal stack ([sigaltstack(2)](http://man7.org/linux/man-pages/man2/sigaltstack.2.html))

-  real-time scheduling policy and priority ([sched(7)](http://man7.org/linux/man-pages/man7/sched.7.html))

The following Linux-specific features are also per-thread:

-  capabilities (see [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html))

-  CPU affinity ([sched_setaffinity(2)](http://man7.org/linux/man-pages/man2/sched_setaffinity.2.html))



### Pthreads function return values

Most pthreads functions return 0 on success, and an **error number** on failure.  Note that the pthreads functions do not set [errno](http://man7.org/linux/man-pages/man3/errno.3.html).  For each of the pthreads functions that can return an error, POSIX.1-2001 specifies that the function can never fail with the error `EINTR`.

***SUMMARY*** : linux system call是会设置`errno`的。





### Thread IDs

Each of the threads in a process has a unique thread identifier (stored in the type pthread_t).  This identifier is returned to the caller of [pthread_create(3)](http://man7.org/linux/man-pages/man3/pthread_create.3.html), and a thread can obtain its own thread identifier using [pthread_self(3)](http://man7.org/linux/man-pages/man3/pthread_self.3.html).

Thread IDs are guaranteed to be unique only within a process.  (In all pthreads functions that accept a thread ID as an argument, that ID by definition refers to a thread in the same process as the caller.)

The system may reuse a thread ID after a terminated thread has been joined, or a detached thread has terminated.  POSIX says: "If an application attempts to use a thread ID whose lifetime has ended, the behavior is undefined."

### Thread-safe functions



### Async-cancel-safe functions

An **async-cancel-safe** function is one that can be safely called in an application where **asynchronous cancelability** is enabled (see [pthread_setcancelstate(3)](http://man7.org/linux/man-pages/man3/pthread_setcancelstate.3.html)).

Only the following functions are required to be async-cancel-safe by POSIX.1-2001 and POSIX.1-2008:



```c
pthread_cancel()
pthread_setcancelstate()
pthread_setcanceltype()
```



### Cancellation points

POSIX.1 specifies that certain functions must, and certain other functions may, be **cancellation points**.  If a thread is cancelable, its cancelability type is **deferred**, and a **cancellation request** is pending for the thread, then the thread is canceled when it calls a function that is a **cancellation point**.

The following functions are required to be **cancellation points** by POSIX.1-2001 and/or POSIX.1-2008:

```c
           accept()
           aio_suspend()
           clock_nanosleep()
           close()
           connect()
           creat()
           fcntl() F_SETLKW
           fdatasync()
           fsync()
           getmsg()
           getpmsg()
           lockf() F_LOCK
           mq_receive()
           mq_send()
           mq_timedreceive()
           mq_timedsend()
           msgrcv()
           msgsnd()
           msync()
           nanosleep()
           open()
           openat() [Added in POSIX.1-2008]
           pause()
           poll()
           pread()
           pselect()
           pthread_cond_timedwait()
           pthread_cond_wait()
           pthread_join()
           pthread_testcancel()
           putmsg()
           putpmsg()
           pwrite()
           read()
           readv()
           recv()
           recvfrom()
           recvmsg()
           select()
           sem_timedwait()
           sem_wait()
           send()
           sendmsg()
           sendto()
           sigpause() [POSIX.1-2001 only (moves to "may" list in POSIX.1-2008)]
           sigsuspend()
           sigtimedwait()
           sigwait()
           sigwaitinfo()
           sleep()
           system()
           tcdrain()
           usleep() [POSIX.1-2001 only (function removed in POSIX.1-2008)]
           wait()
           waitid()
           waitpid()
           write()
           writev()
```

The following functions may be cancellation points according to POSIX.1-2001 and/or POSIX.1-2008:

```c
access()
           asctime()
           asctime_r()
           catclose()
           catgets()
           catopen()
           chmod() [Added in POSIX.1-2008]
           chown() [Added in POSIX.1-2008]
           closedir()
           closelog()
           ctermid()
           ctime()
           ctime_r()
           dbm_close()
           dbm_delete()
           dbm_fetch()
           dbm_nextkey()
           dbm_open()
           dbm_store()
           dlclose()
           dlopen()
           dprintf() [Added in POSIX.1-2008]
           endgrent()
           endhostent()
           endnetent()
           endprotoent()
           endpwent()
           endservent()
           endutxent()
           faccessat() [Added in POSIX.1-2008]
           fchmod() [Added in POSIX.1-2008]
           fchmodat() [Added in POSIX.1-2008]
           fchown() [Added in POSIX.1-2008]
           fchownat() [Added in POSIX.1-2008]
           fclose()
           fcntl() (for any value of cmd argument)
           fflush()
           fgetc()
           fgetpos()
           fgets()
           fgetwc()
           fgetws()
           fmtmsg()
           fopen()
           fpathconf()
           fprintf()
           fputc()
           fputs()
           fputwc()
           fputws()
           fread()
           freopen()
           fscanf()
           fseek()
           fseeko()
           fsetpos()
           fstat()
           fstatat() [Added in POSIX.1-2008]
           ftell()
           ftello()
           ftw()
           futimens() [Added in POSIX.1-2008]
           fwprintf()
           fwrite()
           fwscanf()
           getaddrinfo()
           getc()
           getc_unlocked()
           getchar()
           getchar_unlocked()
           getcwd()
           getdate()
           getdelim() [Added in POSIX.1-2008]
           getgrent()
           getgrgid()
           getgrgid_r()
           getgrnam()
           getgrnam_r()
           gethostbyaddr() [SUSv3 only (function removed in POSIX.1-2008)]
           gethostbyname() [SUSv3 only (function removed in POSIX.1-2008)]
           gethostent()
           gethostid()
           gethostname()
           getline() [Added in POSIX.1-2008]
           getlogin()
           getlogin_r()
           getnameinfo()
           getnetbyaddr()
           getnetbyname()
           getnetent()
           getopt() (if opterr is nonzero)
           getprotobyname()
           getprotobynumber()
           getprotoent()
           getpwent()
           getpwnam()
           getpwnam_r()
           getpwuid()
           getpwuid_r()
           gets()
           getservbyname()
           getservbyport()
           getservent()
           getutxent()
           getutxid()
           getutxline()
           getwc()
           getwchar()
           getwd() [SUSv3 only (function removed in POSIX.1-2008)]
           glob()
           iconv_close()
           iconv_open()
           ioctl()
           link()
           linkat() [Added in POSIX.1-2008]
           lio_listio() [Added in POSIX.1-2008]
           localtime()
           localtime_r()
           lockf() [Added in POSIX.1-2008]
           lseek()
           lstat()
           mkdir() [Added in POSIX.1-2008]
           mkdirat() [Added in POSIX.1-2008]
           mkdtemp() [Added in POSIX.1-2008]
           mkfifo() [Added in POSIX.1-2008]
           mkfifoat() [Added in POSIX.1-2008]
           mknod() [Added in POSIX.1-2008]
           mknodat() [Added in POSIX.1-2008]
           mkstemp()
           mktime()
           nftw()
           opendir()
           openlog()
           pathconf()
           pclose()
           perror()
           popen()
           posix_fadvise()
           posix_fallocate()
           posix_madvise()
           posix_openpt()
           posix_spawn()
           posix_spawnp()
           posix_trace_clear()
           posix_trace_close()
           posix_trace_create()
           posix_trace_create_withlog()
           posix_trace_eventtypelist_getnext_id()
           posix_trace_eventtypelist_rewind()
           posix_trace_flush()
           posix_trace_get_attr()
           posix_trace_get_filter()
           posix_trace_get_status()
           posix_trace_getnext_event()
           posix_trace_open()
           posix_trace_rewind()
           posix_trace_set_filter()
           posix_trace_shutdown()
           posix_trace_timedgetnext_event()
           posix_typed_mem_open()
           printf()
           psiginfo() [Added in POSIX.1-2008]
           psignal() [Added in POSIX.1-2008]
           pthread_rwlock_rdlock()
           pthread_rwlock_timedrdlock()
           pthread_rwlock_timedwrlock()
           pthread_rwlock_wrlock()
           putc()
           putc_unlocked()
           putchar()
           putchar_unlocked()
           puts()
           pututxline()
           putwc()
           putwchar()
           readdir()
           readdir_r()
           readlink() [Added in POSIX.1-2008]
           readlinkat() [Added in POSIX.1-2008]
           remove()
           rename()
           renameat() [Added in POSIX.1-2008]
           rewind()
           rewinddir()
           scandir() [Added in POSIX.1-2008]
           scanf()
           seekdir()
           semop()
           setgrent()
           sethostent()
           setnetent()
           setprotoent()
           setpwent()
           setservent()
           setutxent()
           sigpause() [Added in POSIX.1-2008]
           stat()
           strerror()
           strerror_r()
           strftime()
           symlink()
           symlinkat() [Added in POSIX.1-2008]
           sync()
           syslog()
           tmpfile()
           tmpnam()
           ttyname()
           ttyname_r()
           tzset()
           ungetc()
           ungetwc()
           unlink()
           unlinkat() [Added in POSIX.1-2008]
           utime() [Added in POSIX.1-2008]
           utimensat() [Added in POSIX.1-2008]
           utimes() [Added in POSIX.1-2008]
           vdprintf() [Added in POSIX.1-2008]
           vfprintf()
           vfwprintf()
           vprintf()
           vwprintf()
           wcsftime()
           wordexp()
           wprintf()
           wscanf()
```


An implementation may also mark other functions not specified in the standard as **cancellation points**.  In particular, an implementation is likely to mark any nonstandard function that may **block** as a **cancellation point**.  (This includes most functions that can touch files.)



### Linux implementations of POSIX threads

Over time, two threading implementations have been provided by the GNU C library on Linux:

LinuxThreads

This is the original Pthreads implementation.  Since glibc 2.4, this implementation is no longer supported.

NPTL (Native POSIX Threads Library)

This is the modern Pthreads implementation.  By comparison with LinuxThreads, NPTL provides closer conformance to the requirements of the POSIX.1 specification and better performance when creating large numbers of threads.  NPTL is available since glibc 2.3.2, and requires features that are present in the Linux 2.6 kernel.

Both of these are so-called 1:1 implementations, meaning that each **thread** maps to a **kernel scheduling entity**.  Both threading implementations employ the Linux [clone(2)](http://man7.org/linux/man-pages/man2/clone.2.html) system call.  In NPTL, thread synchronization primitives (mutexes, thread joining, and so on) are implemented using the Linux [futex(2)](http://man7.org/linux/man-pages/man2/futex.2.html) system call.

