# 10.5 Interrupted System Calls

A characteristic of earlier UNIX systems was that if a process caught a signal while the process was blocked in a ‘‘**slow**’’ system call, the system call was interrupted. The system call returned an error and `errno` was set to `EINTR`. This was done under the assumption that since a signal occurred and the process caught it, there is a good chance that something has happened that should wake up the blocked system call.

To support this feature, the **system calls** are divided into two categories: the ‘‘slow’’ system calls and all the others. The slow system calls are those that can **block forever**. Included in this category are

1、Reads that can block the caller forever if data isn’t present with certain file types (pipes, terminal devices, and network devices)

2、Writes that can block the caller forever if the data can’t be accepted immediately by these same file types

3、Opens on certain file types that block the caller until some condition occurs (such as a terminal device open waiting until an attached modem answers the phone)

4、The `pause` function (which by definition puts the calling process to sleep until a signal is caught) and the `wait` function

5、Certain `ioctl` operations

6、Some of the interprocess communication functions (Chapter 15)

The notable exception to these slow system calls is anything related to disk I/O. Although a `read` or a `write` of a disk file can block the caller temporarily (while the disk driver queues the request and then the request is executed), unless a hardware error occurs, the I/O operation always returns and unblocks the caller quickly.

> NOTE: 显然，上述对system call的分类方法是根据这个system call是否可能会将process **block forever**的，短暂的block是不算slow的，这个短暂的block就是a `read` or a `write` of a disk file。并且slow system call是和signal密切相关的；