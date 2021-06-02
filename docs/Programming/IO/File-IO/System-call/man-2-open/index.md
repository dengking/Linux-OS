# [open(2)](http://man7.org/linux/man-pages/man2/open.2.html)

```c++
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);

/* Documented separately, in openat2(2): */
int openat2(int dirfd, const char *pathname, const struct open_how *how, size_t size);
```

A call to `open()` creates a new **open file description**, an entry in the system-wide **table of open files**.  The **open file description** records the **file offset** and the **file status flags** (see below).  A **file descriptor** is a reference to an **open file description**; this reference is unaffected if pathname is subsequently removed or modified to refer to a different file.  For further details on open file descriptions, see NOTES.

> NOTE: 
>
> 一、"**open file description**"其实就是file table entry
>
> 二、"tag-Linux IO data structure-three tables-file descriptor reference to file table entry"

## Open file descriptions

The term **open file description** is the one used by POSIX to refer to the entries in the system-wide table of open files.  In other contexts, this object is variously also called an "open file object", a "file handle", an "open file table entry", or—in kernel-developer parlance—a struct file.

When a file descriptor is duplicated (using `dup(2)` or similar), the duplicate refers to the same open file description as the original file descriptor, and the two file descriptors consequently share the file offset and file status flags.  Such sharing can also occur between processes: a child process created via `fork(2)` inherits duplicates of its parent's file descriptors, and those duplicates refer to the same open file descriptions.

Each `open()` of a file creates a new open file description; thus, there may be multiple open file descriptions corresponding to a file inode.

On Linux, one can use the [kcmp(2)](https://man7.org/linux/man-pages/man2/kcmp.2.html) `KCMP_FILE` operation to test whether two file descriptors (in the same process or in two different processes) refer to the same open file description.



## Synchronized I/O

The POSIX.1-2008 "synchronized I/O" option specifies different variants of synchronized I/O, and specifies the `open()` flags `O_SYNC`, `O_DSYNC`, and `O_RSYNC` for controlling the behavior. Regardless of whether an implementation supports this option, it must at least support the use of `O_SYNC` for regular files.

Linux implements `O_SYNC` and `O_DSYNC`, but not `O_RSYNC`.  Somewhat incorrectly, `glibc` defines `O_RSYNC` to have the same value as `O_SYNC`.  

`O_SYNC` provides synchronized I/O file integrity completion,  meaning write operations will flush data and all associated metadata to the underlying hardware.  

`O_DSYNC` provides synchronized I/O data integrity completion, meaning write operations will flush data to the underlying hardware, but will only flush metadata updates that are required to allow a subsequent read operation to complete successfully.  

Data integrity completion can reduce the number of disk operations  that are required for applications that don't need the guarantees of file integrity completion.