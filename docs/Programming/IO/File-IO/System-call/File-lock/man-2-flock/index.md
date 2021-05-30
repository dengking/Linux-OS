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



## NOTES 



`flock()` places **advisory locks** only; given suitable permissions on a file, a process is free to ignore the use of flock() and perform I/O on the file.

> NOTE: 参见thegeekstuff [2 Types of Linux File Locking (Advisory, Mandatory Lock Examples)](https://www.thegeekstuff.com/2012/04/linux-file-locking-types/)

