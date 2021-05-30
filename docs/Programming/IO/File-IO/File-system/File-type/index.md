# wikipedia [Unix file types](https://en.wikipedia.org/wiki/Unix_file_types)

For *normal* files in the file system, [Unix](https://en.wikipedia.org/wiki/Unix) does not impose or provide any **internal file structure**. This implies that from the point of view of the [operating system](https://en.wikipedia.org/wiki/Operating_system), there is only one file type.

The structure and interpretation thereof is entirely dependent on how the [file](https://en.wikipedia.org/wiki/Computer_file) is interpreted by software.

> NOTE: 上面这段话中所描述的internal file structure所指的是文件在disk中存储的结构还是在当它们读入到内存中的结构呢？显然文件在disk中存储的结构是静态结构，而当进程读入文件到内存中，则此时就需要使用runtime structure了；关于文件的runtime structure，在《APUE-3.10-File-Sharing》中进行了描述；其中所涉及的相关概念，在Wikipedia中都有说明；

Unix does however have some special files. These special files can be identified by the `ls -l` command which displays the type of the file in the first alphabetic letter of the [file system permissions](https://en.wikipedia.org/wiki/File_system_permissions) field. A normal (regular) file is indicated by a [hyphen-minus](https://en.wikipedia.org/wiki/Hyphen-minus) '`-`'.



## Examples of implementations

Different OS-specific implementations allow more types than what POSIX requires (e.g. Solaris doors).

The [GNU coreutils](https://en.wikipedia.org/wiki/GNU_Core_Utilities) version of `ls` uses a call to `filemode()`, a [glibc](https://en.wikipedia.org/wiki/Glibc) function (exposed in the [gnulib](https://en.wikipedia.org/wiki/Gnulib) library[[3\]](https://en.wikipedia.org/wiki/Unix_file_types#cite_note-3)) to get the **mode string**.

FreeBSD uses a simpler approach[[4\]](https://en.wikipedia.org/wiki/Unix_file_types#cite_note-4) but allows a smaller number of **file types**.



## Regular file

Main article: [Computer file](https://en.wikipedia.org/wiki/Computer_file)

Files are also called "regular files" to distinguish them from "special files". They show up in `ls -l` without a specific character in the mode field:

```shell
$ ls -l /etc/passwd
-rw-r--r-- ... /etc/passwd
```

## Directory

Main article: [Directory (computing)](https://en.wikipedia.org/wiki/Directory_(computing))

The most common special file is the directory. The layout of a directory file is defined by the **filesystem** used. As several **filesystems**, both native and non-native, are available under Unix, there is not one directory file layout.

A directory is marked with a `d` as the first letter in the mode field in the output of `ls -dl` or `stat`, e.g.

```shell
$ ls -dl /
drwxr-xr-x 26 root root 4096 Sep 22 09:29 /

$ stat /
  File: "/"
  Size: 4096            Blocks: 8          IO Block: 4096   directory
Device: 802h/2050d      Inode: 128         Links: 26
Access: (0755/drwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
...
```

## Symbolic link

*Main article:* [Symbolic link](https://en.wikipedia.org/wiki/Symbolic_link)

A symbolic link is a reference to another file. This special file is stored as a textual representation of the referenced file's path (which means the destination may be a relative path, or may not exist at all).

A **symbolic link** is marked with an `**l**` (lower case `L`) as the first letter of the mode string, e.g.

```shell
lrwxrwxrwx ... termcap -> /usr/share/misc/termcap
lrwxrwxrwx ... S03xinetd -> ../init.d/xinetd
```



## Named pipe

*Main article:* [Named pipe](https://en.wikipedia.org/wiki/Named_pipe)

One of the strengths of Unix has always been [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication). Among the facilities provided by the OS are *pipes*. Pipes connect the output of one [process](https://en.wikipedia.org/wiki/Process_(computing)) to the input of another. This is fine if both processes exist in the same **parent process space**, started by the same user. There are, however, circumstances where the communicating processes must use *named* pipes. One such circumstance occurs when the processes must be executed under different user names and permissions.

**Named pipes** are special files that can exist anywhere in the file system. **Named pipe** special files are created with the command `mkfifo` as in `mkfifo mypipe`.

A named pipe is marked with a `**p**` as the first letter of the mode string, e.g.

```
prw-rw---- ... mypipe
```

## Socket

*Main article:* [Unix domain socket](https://en.wikipedia.org/wiki/Unix_domain_socket)

A socket is a special file used for [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication). These enable communication between two processes. In addition to sending data, processes can send [file descriptors](https://en.wikipedia.org/wiki/File_descriptor) across a Unix domain socket connection using the `sendmsg()` and `recvmsg()` system.

Unlike **named pipes** which allow only unidirectional data flow, sockets are fully [duplex-capable](https://en.wikipedia.org/wiki/Duplex_(telecommunications)).

A socket is marked with an `**s**` as the first letter of the mode string, e.g.

```
srwxrwxrwx /tmp/.X11-unix/X0
```

## Device file

Main article: [Device file](https://en.wikipedia.org/wiki/Device_file)

In Unix, almost all things are handled as files and have a location in the file system; even **hardware devices** like hard drives. The great exception for devices and the files that represent them are **network devices** that do not turn up in the file system but are handled separately.

Device files are used to apply access rights and to direct operations on the files to the appropriate **device drivers**.

> NOTE: 这是Unix的everything is a file 哲学；

Unix makes a distinction between **character devices** and **block devices**. The distinction is roughly as follows:

- **character devices** provide only a serial stream of input or accept a serial stream of output;
- **block devices** are randomly accessible;

although, for example, [disk partitions](https://en.wikipedia.org/wiki/Disk_partition) may have both character devices that provide un-buffered random access to blocks on the partition and block devices that provide buffered random access to blocks on the partition.

A character device is marked with a `**c**` as the first letter of the mode string. Likewise, a block device is marked with a `**b**`, e.g.

```shell
crw------- ... /dev/null
brw-rw---- ... /dev/sda
```

## Door

Main article: [Doors (computing)](https://en.wikipedia.org/wiki/Doors_(computing))

A door is a special file for inter-process communication between a client and server, currently implemented only in [Solaris](https://en.wikipedia.org/wiki/Solaris_(operating_system)).

A door is marked with a `**D**` (upper case) as the first letter of the mode string, e.g.

```shell
Dr--r--r-- ... name_service_door
```