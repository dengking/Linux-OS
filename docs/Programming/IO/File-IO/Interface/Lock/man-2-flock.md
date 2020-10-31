# [FLOCK(2)](http://man7.org/linux/man-pages/man2/flock.2.html)

## NAME

`flock` - apply or remove an advisory lock on an open file

## SYNOPSIS

```c
       #include <sys/file.h>

       int flock(int fd, int operation);
```

## DESCRIPTION

Apply or remove an advisory lock on the open file specified by `fd`. The argument operation is one of the following:

- LOCK_SH  Place a **shared lock**.  More than one process may hold a **shared lock** for a given file at a given time.

- LOCK_EX  Place an **exclusive lock**.  Only one process may hold an exclusive lock for a given file at a given time.

- LOCK_UN  Remove an existing lock held by this process.

A call to `flock()` may block if an incompatible lock is held by another process.  To make a **nonblocking request**, include `LOCK_NB` (by ORing) with any of the above operations.

A single file may not simultaneously have both shared and exclusive locks.

Locks created by flock() are associated with an open file description (see [open(2)](http://man7.org/linux/man-pages/man2/open.2.html)).  This means that duplicate file descriptors (created by, for example, [fork(2)](http://man7.org/linux/man-pages/man2/fork.2.html) or [dup(2)](http://man7.org/linux/man-pages/man2/dup.2.html)) refer to **the same lock**, and this lock may be modified or released using any of these **file descriptors**. Furthermore, the lock is released either by an explicit `LOCK_UN` operation on any of these duplicate file descriptors, or when all such file descriptors have been closed.

If a process uses [open(2)](http://man7.org/linux/man-pages/man2/open.2.html) (or similar) to obtain more than one file descriptor for the same file, these file descriptors are treated independently by flock().  An attempt to lock the file using one of these file descriptors may be denied by a lock that the calling process has already placed via another file descriptor.

Locks created by flock() are preserved across an [execve(2)](http://man7.org/linux/man-pages/man2/execve.2.html).

A shared or exclusive lock can be placed on a file regardless of the  mode in which the file was opened.

## RETURN VALUE

On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

## ERRORS

`EBADF`  `fd` is not an open file descriptor.

`EINTR`  While waiting to acquire a lock, the call was interrupted by delivery of a signal caught by a handler; see [signal(7)](http://man7.org/linux/man-pages/man7/signal.7.html).

`EINVAL` operation is invalid.

`ENOLCK` The kernel ran out of memory for allocating lock records.

`EWOULDBLOCK` The file is locked and the `LOCK_NB` flag was selected.

## NOTES 

Since kernel 2.0, flock() is implemented as a system call in its own right rather than being emulated in the GNU C library as a call to [fcntl(2)](http://man7.org/linux/man-pages/man2/fcntl.2.html).  With this implementation, there is no interaction between the types of lock placed by flock() and [fcntl(2)](http://man7.org/linux/man-pages/man2/fcntl.2.html), and flock() does not detect **deadlock**.  (Note, however, that on some systems, such as the modern BSDs, flock() and fcntl(2) locks do interact with one another.)

flock() places **advisory locks** only; given suitable permissions on a file, a process is free to ignore the use of flock() and perform I/O on the file.

***SUMMARY*** : 参见[2 Types of Linux File Locking (Advisory, Mandatory Lock Examples)](https://www.thegeekstuff.com/2012/04/linux-file-locking-types/)

flock() and fcntl(2) locks have different semantics with respect to forked processes and dup(2).  On systems that implement flock() using fcntl(2), the semantics of flock() will be different from those described in this manual page.

Converting a lock (shared to exclusive, or vice versa) is not guaranteed to be atomic: the existing lock is first removed, and then a new lock is established.  Between these two steps, a pending lock request by another process may be granted, with the result that the conversion either blocks, or fails if LOCK_NB was specified.  (This is the original BSD behavior, and occurs on many other implementations.)

