# gnu libc [13.15.3 I/O Operating Modes](https://www.gnu.org/software/libc/manual/html_node/Operating-Modes.html#Operating-Modes)

The operating modes affect how input and output operations using a **file descriptor** work. These flags are set by `open` and can be fetched and changed with `fcntl`.

> NOTE: 注意，什么这段话中使用的是input，output，而没有限制于file，所以它们应该也有可能适用于其他的IO，比如pipe等；

## Macro: int `O_APPEND`

The bit that enables **append mode** for the file. If set, then all `write` operations write the data at the end of the file, extending it, regardless of the **current file position**. This is the only **reliable** way to append to a file. In append mode, you are guaranteed that the data you write will always go to the current end of the file, regardless of other processes writing to the file. Conversely, if you simply set the file position to the end of file and write, then another process can extend the file after you set the file position but before you write, resulting in your data appearing someplace before the real end of file.



## Macro: int `O_NONBLOCK`

The bit that enables **nonblocking mode** for the file. If this bit is set, `read` requests on the file can return immediately with a failure status if there is no input immediately available, instead of blocking. Likewise, `write` requests can also return immediately with a failure status if the output can’t be written immediately.

Note that the `O_NONBLOCK` flag is overloaded as both an **I/O operating mode** and a **file name translation flag**; see [Open-time Flags](https://www.gnu.org/software/libc/manual/html_node/Open_002dtime-Flags.html#Open_002dtime-Flags).



## Macro: int `O_NDELAY`

This is an obsolete name for `O_NONBLOCK`, provided for compatibility with BSD. It is not defined by the POSIX.1 standard.



The remaining operating modes are BSD and GNU extensions. They exist only on some systems. On other systems, these macros are not defined.



## Macro: int `O_ASYNC`

The bit that enables **asynchronous input mode**. If set, then `SIGIO` signals will be generated when input is available. See [Interrupt Input](https://www.gnu.org/software/libc/manual/html_node/Interrupt-Input.html#Interrupt-Input).

Asynchronous input mode is a BSD feature.



## Macro: int `O_FSYNC`

The bit that enables synchronous writing for the file. If set, each `write` call will make sure the data is reliably stored on disk before returning.

Synchronous writing is a BSD feature.

## Macro: int `O_SYNC`

This is another name for `O_FSYNC`. They have the same value.

## Macro: int `O_NOATIME`

If this bit is set, `read` will not update the access time of the file. See [File Times](https://www.gnu.org/software/libc/manual/html_node/File-Times.html#File-Times). This is used by programs that do backups, so that backing a file up does not count as reading it. Only the owner of the file or the superuser may use this bit.

This is a GNU extension.