# [openat(2) - Linux man page](https://linux.die.net/man/2/openat)

## Name

`openat` - open a file relative to a directory file descriptor

## Synopsis

```C
#include <fcntl.h>

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```





## Description

The **openat**() system call operates in exactly the same way as [**open**(2)](https://linux.die.net/man/2/open), except for the differences described in this manual page.

If the pathname given in *pathname* is relative, then it is interpreted relative to the directory referred to by the file descriptor *dirfd* (rather than relative to the current working directory of the calling process, as is done by [**open**(2)](https://linux.die.net/man/2/open) for a relative pathname).

If *pathname* is relative and *dirfd* is the special value **AT_FDCWD**, then *pathname* is interpreted relative to the current working directory of the calling process (like [**open**(2)](https://linux.die.net/man/2/open)).

If *pathname* is absolute, then *dirfd* is ignored.



## Notes

**openat**() and other similar system calls suffixed "at" are supported for two reasons.

First, **openat**() allows an application to avoid race conditions that could occur when using [**open**(2)](https://linux.die.net/man/2/open) to open files in directories other than **the current working directory**. These **race conditions** result from the fact that some component of **the directory prefix** given to [**open**(2)](https://linux.die.net/man/2/open) could be changed in parallel with the call to [**open**(2)](https://linux.die.net/man/2/open). Such races can be avoided by opening a file descriptor for the target directory, and then specifying that file descriptor as the *dirfd* argument of **openat**().



Second, **openat**() allows the implementation of a per-thread "current working directory", via file **descriptor**(s) maintained by the application. (This functionality can also be obtained by tricks based on the use of */proc/self/fd/*dirfd, but less efficiently.)





## stackoverflow [why is openat() needed to avoid a two-step race condition with stat and then open()?](https://stackoverflow.com/questions/35478448/why-is-openat-needed-to-avoid-a-two-step-race-condition-with-stat-and-then-ope)

The explanation at

<http://man7.org/linux/man-pages/man2/open.2.html>

about why `openat` is needed, reads in part:

> **openat()** allows an application to avoid race conditions that could occur when using **open()** to open files in directories other than the current working directory. These race conditions result from the fact that some component of the directory prefix given to **open()** could be changed in parallel with the call to **open()**. Suppose, for example, that we wish to create the file *path/to/xxx.dep* if the file *path/to/xxx* exists. The problem is that between the existence check and the file creation step, path or to (which might be symbolic links) could be modified to point to a different location.

I don't see why this race is a problem. If an app wants to check for the existence of some file and if so, create a different file, then, of course these are **two steps**(先check，在create a file), and the app either should ensure that nothing interferes in between, or accept the consequences of doing a two-step operation. Only if a single call to `open()` could cause a race condition, might some other syscall, such as `openat()` be needed. Otherwise, this is not for syscalls to solve, but it is an application's responsibility to deal with.

What am I not understanding here?



### [A](https://stackoverflow.com/a/35498833)


`openat()` allows you to lock down(锁定) an entire directory path, resolving the race condition only once, then safely open files relative to that path without worrying about race conditions.

**Details**
You are correct that the race condition is still the responsibility of your program to anticipate and handle, but the `openat()` function allows you to *only do it once* for multiple files. If you want to open multiple files within the same directory, you *could* do it with individual calls to `open()`, but you will have to expect and handle the **race condition** every time. Instead, with `openat()`, you can grab a file descriptor to the parent directory first, which will prevent other processes from modifying or removing that path. You can now use `openat()` to open multiple files relative to that locked path safely, without worrying about the **race conditions** that opening absolute paths normally entails.

**Other Use Case**
Also note that the race condition isn't necessarily between your program opening files and other programs changing or deleting paths - it's also between threads within your program. `openat()` is useful when you want to work with relative paths and are in a multithreaded environment. Remember that if you change your working directory in one thread, it changes it for the entire process and its threads.

So when you fork off multiple threads, they can each grab a file descriptor for different directories, and use `openat()` with those *directory* file descriptors and relative paths from them to open files, without worrying about what the other threads are doing with the whole processes' working directory, or maintaining a load of absolute paths.

This use case is described by the second note in the man page for `openat`:

> Second, openat() allows the implementation of a per-thread "current working directory", via file descriptor(s) maintained by the application. (This functionality can also be obtained by tricks based on the use of /proc/self/fd/dirfd, but less efficiently.

**Sidenote**
I don't want to get too deep into a discussion of what responsibilities should be assumed by system calls because it will get subjective, but note that `openat` doesn't really *resolve* race conditions - you can still have one when you try to lock down the parent directory, and that's entirely your program's responsibility to handle. It is a tool to help you *prevent* race conditions, after you've achieved resolution once. I think that's a useful and reasonable mechanism to include in an OS as a system call.