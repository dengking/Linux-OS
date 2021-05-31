# gnu libc [13.15.2 Open-time Flags](https://www.gnu.org/software/libc/manual/html_node/Open_002dtime-Flags.html#Open_002dtime-Flags)

The **open-time flags** specify options affecting how `open` will behave. These options are not preserved once the file is open. The exception to this is `O_NONBLOCK`, which is also an I/O operating mode and so it *is* saved. See [Opening and Closing Files](https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html#Opening-and-Closing-Files), for how to call `open`.

> NOTE: 显然，这些flag应该仅仅适用于`open`函数

There are two sorts of options specified by open-time flags.

1、*File name translation flags* affect how `open` looks up the **file name** to locate the file, and whether the file can be created.

2、*Open-time action flags* specify extra operations that `open` will perform on the file once it is open.

Here are the **file name translation flags**.

## Macro: int `O_CREAT`

If set, the file will be created if it doesn’t already exist.



## Macro: int `O_EXCL`

If both `O_CREAT` and `O_EXCL` are set, then `open` fails if the specified file already exists. This is guaranteed to never clobber an existing file.

The `O_EXCL` flag has a special meaning in combination with `O_TMPFILE`; see below.



## Macro: int `O_TMPFILE`

If this flag is specified, functions in the `open` family create an **unnamed temporary file**. In this case, the pathname argument to the `open` family of functions (see [Opening and Closing Files](https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html#Opening-and-Closing-Files)) is interpreted as the directory in which the **temporary file** is created (thus determining the file system which provides the storage for the file). The `O_TMPFILE` flag must be combined with `O_WRONLY` or `O_RDWR`, and the mode argument is required.

The **temporary file** can later be given a name using `linkat`, turning it into a **regular file**. This allows the atomic creation of a file with the specific file attributes (mode and extended attributes) and file contents. If, for security reasons, it is not desirable that a name can be given to the file, the `O_EXCL` flag can be specified along with `O_TMPFILE`.

Not all kernels support this open flag. If this flag is unsupported, an attempt to create an unnamed temporary file fails with an error of `EINVAL`. If the underlying file system does not support the `O_TMPFILE` flag, an `EOPNOTSUPP` error is the result.

The `O_TMPFILE` flag is a GNU extension.

## Macro: int `O_NONBLOCK`

This prevents `open` from blocking for a “long time” to open the file. This is only meaningful for some kinds of files, usually devices such as **serial ports**; when it is not meaningful, it is harmless and ignored. Often, opening a port to a modem blocks until the modem reports carrier detection; if `O_NONBLOCK` is specified, `open` will return immediately without a carrier.

Note that the `O_NONBLOCK` flag is overloaded as both an I/O operating mode and a file name translation flag. This means that specifying `O_NONBLOCK` in `open` also sets nonblocking I/O mode; see [Operating Modes](https://www.gnu.org/software/libc/manual/html_node/Operating-Modes.html#Operating-Modes). To open the file without blocking but do normal I/O that blocks, you must call `open` with `O_NONBLOCK` set and then call `fcntl` to turn the bit off.



## Macro: int `O_NOCTTY`

If the **named file** is a **terminal device**, don’t make it the **controlling terminal** for the process. See [Job Control](https://www.gnu.org/software/libc/manual/html_node/Job-Control.html#Job-Control), for information about what it means to be the **controlling terminal**.

On GNU/Hurd systems and 4.4 BSD, opening a file never makes it the controlling terminal and `O_NOCTTY` is zero. However, GNU/Linux systems and some other systems use a nonzero value for `O_NOCTTY` and set the controlling terminal when you open a file that is a terminal device; so to be portable, use `O_NOCTTY` when it is important to avoid this.





The following three file name translation flags exist only on GNU/Hurd systems.



## Macro: int `O_IGNORE_CTTY`

Do not recognize the named file as the **controlling terminal**, even if it refers to the process’s existing controlling terminal device. Operations on the new **file descriptor** will never induce **job control signals**. See [Job Control](https://www.gnu.org/software/libc/manual/html_node/Job-Control.html#Job-Control).



## Macro: int `O_NOLINK`

If the named file is a symbolic link, open the link itself instead of the file it refers to. (`fstat` on the new file descriptor will return the information returned by `lstat` on the link’s name.)



## Macro: int `O_NOTRANS`

If the named file is specially translated, do not invoke the translator. Open the bare file the translator itself sees.



The open-time action flags tell `open` to do additional operations which are not really related to opening the file. The reason to do them as part of `open` instead of in separate calls is that `open` can do them *atomically*.



## Macro: int `O_TRUNC`

Truncate the file to zero length. This option is only useful for regular files, not special files such as directories or FIFOs. POSIX.1 requires that you open the file for writing to use `O_TRUNC`. In BSD and GNU you must have permission to write the file to truncate it, but you need not open for write access.

This is the only open-time action flag specified by POSIX.1. There is no good reason for truncation to be done by `open`, instead of by calling `ftruncate` afterwards. The `O_TRUNC` flag existed in Unix before `ftruncate` was invented, and is retained for backward compatibility.



The remaining operating modes are BSD extensions. They exist only on some systems. On other systems, these macros are not defined.



## Macro: int `O_SHLOCK`

Acquire a shared lock on the file, as with `flock`. See [File Locks](https://www.gnu.org/software/libc/manual/html_node/File-Locks.html#File-Locks).

If `O_CREAT` is specified, the locking is done atomically when creating the file. You are guaranteed that no other process will get the lock on the new file first.



## Macro: int `O_EXLOCK`

Acquire an exclusive lock on the file, as with `flock`. See [File Locks](https://www.gnu.org/software/libc/manual/html_node/File-Locks.html#File-Locks). This is atomic like `O_SHLOCK`.