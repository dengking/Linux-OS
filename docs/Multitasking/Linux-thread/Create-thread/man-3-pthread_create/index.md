# [PTHREAD_CREATE(3)](http://man7.org/linux/man-pages/man3/pthread_create.3.html)

## NAME

`pthread_create` - create a new thread

## SYNOPSIS

```c
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
```

Compile and link with `-pthread`.

## DESCRIPTION 

The `pthread_create()` function starts a new thread in the calling process.  The new thread starts execution by invoking `start_routine()`; `arg` is passed as the sole argument of `start_routine()`.

### Thread terminate

The new thread terminates in one of the following ways:

1、It calls [pthread_exit(3)](http://man7.org/linux/man-pages/man3/pthread_exit.3.html), specifying an **exit status** value that is available to another thread in the same process that calls [pthread_join(3)](http://man7.org/linux/man-pages/man3/pthread_join.3.html).

2、It returns from `start_routine()`.  This is equivalent to calling [pthread_exit(3)](http://man7.org/linux/man-pages/man3/pthread_exit.3.html) with the value supplied in the return statement.

> NOTE: 在一些情况下，`start_routing`可能并不会return，这种情况下线程的terminates往往是由其它线程来控制的；

3、It is canceled (see [pthread_cancel(3)](http://man7.org/linux/man-pages/man3/pthread_cancel.3.html)).

4、Any of the threads in the process calls [exit(3)](http://man7.org/linux/man-pages/man3/exit.3.html), or the **main thread** performs a return from `main()`.  This causes the termination of all threads in the process.

### The `attr` argument

The `attr` argument points to a `pthread_attr_t` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using `pthread_attr_init(3)` and related functions.  If `attr` is NULL, then the thread is created with default attributes.

### Thread ID

Before returning, a successful call to `pthread_create()` stores the ID of the new thread in the buffer pointed to by thread; this identifier is used to refer to the thread in subsequent calls to other `pthreads` functions.

### Signal mask 

The new thread inherits a copy of the creating thread's signal mask ([pthread_sigmask(3)](http://man7.org/linux/man-pages/man3/pthread_sigmask.3.html)).  The set of pending signals for the new thread is empty ([sigpending(2)](http://man7.org/linux/man-pages/man2/sigpending.2.html)).  The new thread does not inherit the creating thread's alternate signal stack ([sigaltstack(2)](http://man7.org/linux/man-pages/man2/sigaltstack.2.html)).

### Floating-point environment 

The new thread inherits the calling thread's floating-point environment ([fenv(3)](http://man7.org/linux/man-pages/man3/fenv.3.html)).

### CPU-time clock 

The initial value of the new thread's CPU-time clock is 0 (see [pthread_getcpuclockid(3)](http://man7.org/linux/man-pages/man3/pthread_getcpuclockid.3.html)).



### Linux-specific details

The new thread inherits copies of the calling thread's capability sets (see [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html)) and CPU affinity mask (see [sched_setaffinity(2)](http://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)).



## NOTES

See [pthread_self(3)](http://man7.org/linux/man-pages/man3/pthread_self.3.html) for further information on the thread ID returned in thread by `pthread_create()`.  Unless real-time scheduling policies are being employed, after a call to `pthread_create()`, it is indeterminate which thread—the caller or the new thread—will next execute.

###  joinable or detached

A thread may either be ***joinable*** or ***detached***.  

If a thread is joinable, then another thread can call [pthread_join(3)](http://man7.org/linux/man-pages/man3/pthread_join.3.html) to wait for the thread to terminate and fetch its **exit status**.  Only when a terminated joinable thread has been joined are the last of its resources released back to the system.  

When a detached thread terminates, its resources are automatically released back to the system: it is not possible to join with the thread in order to obtain its exit status.  Making a thread detached is useful for some types of daemon threads whose exit status the application does not need to care about.  By default, a new thread is created in a joinable state, unless `attr` was set to create the thread in a detached state (using [pthread_attr_setdetachstate(3)](http://man7.org/linux/man-pages/man3/pthread_attr_setdetachstate.3.html)).

### `RLIMIT_STACK` soft resource limit 

Under the NPTL threading implementation, if the `RLIMIT_STACK` soft resource limit at the time the program started has any value other than "unlimited", then it determines the default stack size of new threads.  Using [pthread_attr_setstacksize(3)](http://man7.org/linux/man-pages/man3/pthread_attr_setstacksize.3.html), the **stack size attribute** can be explicitly set in the `attr` argument used to create a thread, in order to obtain a stack size other than the default.  If the `RLIMIT_STACK` resource limit is set to "unlimited", a per-architecture value is used for the stack size.  Here is the value for a few architectures:

```
              ┌─────────────┬────────────────────┐
              │Architecture │ Default stack size │
              ├─────────────┼────────────────────┤
              │i386         │               2 MB │
              ├─────────────┼────────────────────┤
              │IA-64        │              32 MB │
              ├─────────────┼────────────────────┤
              │PowerPC      │               4 MB │
              ├─────────────┼────────────────────┤
              │S/390        │               2 MB │
              ├─────────────┼────────────────────┤
              │Sparc-32     │               2 MB │
              ├─────────────┼────────────────────┤
              │Sparc-64     │               4 MB │
              ├─────────────┼────────────────────┤
              │x86_64       │               2 MB │
              └─────────────┴────────────────────┘
```