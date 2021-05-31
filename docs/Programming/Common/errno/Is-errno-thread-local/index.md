# Is `errno` thread local?

## stackoverflow [Is errno thread-safe?](https://stackoverflow.com/questions/1694164/is-errno-thread-safe)

In `errno.h`, this variable is declared as `extern int errno;` so my question is, is it safe to check `errno` value after some calls or use `perror()` in multi-threaded code. Is this a thread safe variable? If not, then whats the alternative ?

I am using linux with gcc on x86 architecture.



### [A](https://stackoverflow.com/a/1694170)


Yes, it is **thread safe**. On Linux, the global `errno` variable is [thread-specific](https://en.wikipedia.org/wiki/Thread-local_storage). POSIX requires that `errno` be threadsafe.

See <http://www.unix.org/whitepapers/reentrant.html>

> In POSIX.1, `errno` is defined as an external global variable. But this definition is unacceptable in a **multithreaded** environment, because its use can result in nondeterministic results. The problem is that two or more threads can encounter errors, all causing the same `errno` to be set. Under these circumstances, a thread might end up checking `errno` after it has already been updated by another thread.
>
> To circumvent the resulting nondeterminism, POSIX.1c redefines `errno` as a service that can access the per-thread error number as follows (ISO/IEC 9945:1-1996, §2.4):
>
> Some functions may provide the error number in a variable accessed through the symbol `errno`. The symbol `errno` is defined by including the header , as specified by the C Standard ... For each thread of a process, the value of `errno` shall not be affected by function calls or assignments to errno by other threads.

Also see <http://linux.die.net/man/3/errno>

> `errno` is thread-local; setting it in one thread does not affect its value in any other thread.



### [A](https://stackoverflow.com/a/1694177)

Yes

------

Errno isn't a simple variable anymore, it's something complex behind the scenes, specifically for it to be thread-safe.

See `$ man 3 errno`:

```c
ERRNO(3)                   Linux Programmer’s Manual                  ERRNO(3)

NAME
       errno - number of last error

SYNOPSIS
       #include <errno.h>

DESCRIPTION

      ...
       errno is defined by the ISO C standard to be  a  modifiable  lvalue  of
       type  int,  and  must not be explicitly declared; errno may be a macro.
       errno is thread-local; setting it in one thread  does  not  affect  its
       value in any other thread.
```

------

We can double-check:

```c
$ cat > test.c
#include <errno.h>
f() { g(errno); }
$ cc -E test.c | grep ^f
f() { g((*__errno_location ())); }
$ 
```