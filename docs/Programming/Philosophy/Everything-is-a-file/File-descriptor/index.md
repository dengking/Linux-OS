# File descriptor



## wikipedia [File descriptor](https://en.wikipedia.org/wiki/File_descriptor)

> NOTE: 
> 1、这篇文章总结的非常好

In [Unix](https://en.wikipedia.org/wiki/Unix) and [related](https://en.wikipedia.org/wiki/Unix-like) computer operating systems, a **file descriptor** (**FD**, less frequently **fildes**) is an abstract indicator ([handle](https://en.wikipedia.org/wiki/Handle_(computing))) used to access a [file](https://en.wikipedia.org/wiki/File_(computing)) or other [input/output](https://en.wikipedia.org/wiki/Input/output) [resource](https://en.wikipedia.org/wiki/System_resource), such as a [pipe](https://en.wikipedia.org/wiki/Pipe_(Unix)) or [network socket](https://en.wikipedia.org/wiki/Network_socket). **File descriptors** form part of the [POSIX](https://en.wikipedia.org/wiki/POSIX) [application programming interface](https://en.wikipedia.org/wiki/Application_programming_interface). A file descriptor is a non-negative [integer](https://en.wikipedia.org/wiki/Integer), generally represented in the [C](https://en.wikipedia.org/wiki/C_(programming_language)) programming language as the type int (negative values being reserved to indicate "no value" or an error condition).

Each Unix [process](https://en.wikipedia.org/wiki/Process_(computing)) (except perhaps a [daemon](https://en.wikipedia.org/wiki/Daemon_(computer_software))) should expect to have three standard POSIX file descriptors, corresponding to the three [standard streams](https://en.wikipedia.org/wiki/Standard_streams):

| Integer value |                          Name                           | [unistd.h](https://en.wikipedia.org/wiki/Unistd.h) symbolic constant | [stdio.h](https://en.wikipedia.org/wiki/Stdio.h) file stream |
| :-----------: | :-----------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|       0       |  [Standard input](https://en.wikipedia.org/wiki/Stdin)  |                        `STDIN_FILENO`                        |                           `stdin`                            |
|       1       | [Standard output](https://en.wikipedia.org/wiki/Stdout) |                       `STDOUT_FILENO`                        |                           `stdout`                           |
|       2       | [Standard error](https://en.wikipedia.org/wiki/Stderr)  |                       `STDERR_FILENO`                        |                           `stderr`                           |



### Overview

In the traditional implementation of Unix, **file descriptors** index into a per-process **file descriptor table** maintained by the kernel, that in turn indexes into a system-wide table of files opened by all processes, called the **file table**. This table records the *mode* with which the file (or other resource) has been opened: for reading, writing, appending, and possibly other modes. It also indexes into a third table called the [inode table](https://en.wikipedia.org/wiki/Inode) that describes the actual underlying files. To perform input or output, the process passes the file descriptor to the kernel through a [system call](https://en.wikipedia.org/wiki/System_call), and the kernel will access the file on behalf of the process. The process does not have direct access to the file or **inode tables**.

> NOTE : 在APUE的3.10 File Sharing也描述了这部分内容；需要注意的是：the data structures used by the kernel for all I/O.即所有的IO都是采用的类似于上述的结构；并且上述结构需要和[Process control block](https://en.wikipedia.org/wiki/Process_control_block) 一起来理解才能够很好的对Unix OS的IO有一个整体的认知；

> NOTE: 需要注意，上面这段话中提及 **file descriptor table** 和 **file table** 时，前面分别加上了修饰语： per-process 和  system-wide ；这两个修饰语是非常重要的，需要将它们和the data structures used by the kernel for all I/O一起来进行理解；因为 **file descriptor table** 的scope是process，即每个process都有一套自己的  **file descriptor table** ，所以每个process的file descriptor都是从0开始增长；显然比较两个process的file descriptor是没有意义的（处理0,1,2，因为它们都已经被默认绑定到`STDIN_FILENO` ,`STDOUT_FILENO` ,`STDERR_FILENO` ）；而file table的scope是system，即所有的process都将共享file table；

> NOTE: 每次调用`open`系统调用，都会创建一个file table entry

On [Linux](https://en.wikipedia.org/wiki/Linux), the set of file descriptors open in a process can be accessed under the path `/proc/PID/fd/`, where PID is the [process identifier](https://en.wikipedia.org/wiki/Process_identifier).

In [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems, file descriptors can refer to any [Unix file type](https://en.wikipedia.org/wiki/Unix_file_type) named in a file system. As well as regular files, this includes [directories](https://en.wikipedia.org/wiki/Directory_(file_systems)), [block](https://en.wikipedia.org/wiki/Block_device) and [character devices](https://en.wikipedia.org/wiki/Character_device) (also called "special files"), [Unix domain sockets](https://en.wikipedia.org/wiki/Unix_domain_socket), and [named pipes](https://en.wikipedia.org/wiki/Named_pipe). File descriptors can also refer to other objects that do not normally exist in the file system, such as [anonymous pipes](https://en.wikipedia.org/wiki/Anonymous_pipe) and [network sockets](https://en.wikipedia.org/wiki/Network_socket).

> NOTE: [Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file) ；从kernel实现的角度来看看待everything in Unix is file，Unix-like system是[monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)，上面提到的这些device或者file都是由kernel来进行维护，它们都有对应的kernel structure；我们通过file descriptor来引用这些kernel structure，我们只能够通过system call来对这些kernel structure进行操作；

The FILE data structure in the [C standard I/O library](https://en.wikipedia.org/wiki/Stdio) usually includes a low level file descriptor for the object in question on Unix-like systems. The overall data structure provides additional abstraction and is instead known as a *file handle.*



![img](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f8/File_table_and_inode_table.svg/300px-File_table_and_inode_table.svg.png)





File descriptors for a single process, file table and [inode](https://en.wikipedia.org/wiki/Inode) table. Note that multiple file descriptors can refer to the same file table entry (e.g., as a result of the [dup](https://en.wikipedia.org/wiki/Dup_(system_call)) system call[[3\]](https://en.wikipedia.org/wiki/File_descriptor#cite_note-bach-3):104 and that multiple file table entries can in turn refer to the same inode (if it has been opened multiple times; the table is still simplified because it represents inodes by file names, even though an inode can have [multiple names](https://en.wikipedia.org/wiki/Hard_link)). File descriptor 3 does not refer to anything in the file table, signifying that it has been closed.

> NOTE: 上述的三层对应关系存在着多种可能的情况，再加上OS提供的fork机制（子进程继承父进程的file descriptor和file table entry），各种IO操作（比如dup，read，write）等等都导致了问题的复杂性；
>
> 比如存在着这些可能的情况：
> - `dup`，同一进程中，多个file descriptor指向了同一个file table entry
>
> - `fork`后，父进程，子进程的同一个file descriptor共享同一个file table entry（因为file descriptor table是每个进程私有的，所以这种情况其实类似于第一种情况，即多个file descriptor指向了同一个file table entry）
>
> 上面描述了file descriptor和file table entry之间的对应关系，下面描述file table entry和iNode之间的关系：
> 是有可能存在多个不同的file table entry指向了同一个iNode的；
>
> 显然OS的这种设计，就导致当一个文件被多个不同的process进行share的时候，而每个process都可以执行一系列的IO操作，这就导致了可能存在的数据冲突问题；
>
> 总的来说，按照OS的这总结构设计，以及OS提供的各种操作，是可以总结出可能的所有情形的；



### Operations on file descriptors

> NOTE: 
>
> 1、下面的总结非常好

The following lists typical operations on file descriptors on modern [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems. Most of these functions are declared in the `<unistd.h>` header, but some are in the `<fcntl.h>` header instead.

#### Creating file descriptors

- [open](https://en.wikipedia.org/wiki/Open_(system_call))()
- [creat()](http://man7.org/linux/man-pages/man2/open.2.html) 
- [`socket()`](http://man7.org/linux/man-pages/man2/socket.2.html) 
- `accept()`
- `socketpair`()
- `pipe()`
- `opendir()`
- `open_by_handle_at()` (Linux)
- [`signalfd()`](http://man7.org/linux/man-pages/man2/signalfd.2.html) (Linux)
- [`eventfd()`](http://man7.org/linux/man-pages/man2/eventfd.2.html) (Linux)
- [`timerfd_create()`](http://man7.org/linux/man-pages/man2/timerfd_create.2.html) (Linux)
- `memfd_create()` (Linux)
- `userfaultfd()` (Linux)



#### Deriving file descriptors

- dirfd()
- fileno()



#### Operations on a single file descriptor

- [read](https://en.wikipedia.org/wiki/Read_(system_call))(), [write](https://en.wikipedia.org/wiki/Write_(system_call))()
- readv(), writev()
- pread(), pwrite()
- recv(), send()
- recvmsg(), sendmsg() (including allowing sending FDs)
- sendfile()
- lseek()
- [fstat()](https://en.wikipedia.org/wiki/Stat_(system_call))
- fchmod()
- fchown()
- fdopen()
- ftruncate()
- fsync()
- fdatasync()
- fstatvfs()
- dprintf()
- vmsplice() (Linux)



#### Operations on multiple file descriptors

- [select()](https://en.wikipedia.org/wiki/Select_(Unix)), pselect()
- poll()
- [epoll()](https://en.wikipedia.org/wiki/Epoll) (for Linux)
- [kqueue()](https://en.wikipedia.org/wiki/Kqueue) (for BSD-based systems).
- sendfile()
- [splice()](https://en.wikipedia.org/wiki/Splice_(system_call)), tee() (for Linux)



#### Operations on the file descriptor table



The `fcntl()` function is used to perform various operations on a file descriptor, depending on the command argument passed to it. There are commands to get and set attributes associated with a file descriptor, including `F_GETFD`, `F_SETFD`, `F_GETFL` and `F_SETFL`.

- [close()](https://en.wikipedia.org/wiki/Close_(system_call))
- closefrom() (BSD and Solaris only; deletes all file descriptors greater than or equal to specified number)
- [dup()](https://en.wikipedia.org/wiki/Dup_(system_call)) (duplicates an existing file descriptor guaranteeing to be the lowest number available file descriptor)
- [dup2()](https://en.wikipedia.org/wiki/Dup2) (the new file descriptor will have the value passed as an argument)
- fcntl (`F_DUPFD`)



#### Operations that modify process state

- fchdir() (sets the process's current working directory based on a directory file descriptor)
- mmap() (maps ranges of a file into the process's address space)



#### File locking

- flock()
- fcntl() (`F_GETLK`, `F_SETLK`) and `F_SETLKW`
- lockf()



#### Sockets

- connect()
- bind()
- listen()
- accept() (creates a new file descriptor for an incoming connection)
- getsockname()
- getpeername()
- getsockopt()
- setsockopt()
- shutdown() (shuts down one or both halves of a full duplex connection)



#### Miscellaneous

- [ioctl()](https://en.wikipedia.org/wiki/Ioctl) (a large collection of miscellaneous operations on a single file descriptor, often associated with a device)



### Upcoming operations

A series of new operations on file descriptors has been added to many modern Unix-like systems, as well as numerous C libraries, to be standardized in a future version of [POSIX](https://en.wikipedia.org/wiki/POSIX).[[5\]](https://en.wikipedia.org/wiki/File_descriptor#cite_note-5) The `at` suffix signifies that the function takes an additional first argument supplying a file descriptor from which [relative paths](https://en.wikipedia.org/wiki/Relative_path) are resolved, the forms lacking the `at` suffix thus becoming equivalent to passing a file descriptor corresponding to the current [working directory](https://en.wikipedia.org/wiki/Working_directory). The purpose of these new operations is to defend against a certain class of [TOCTTOU](https://en.wikipedia.org/wiki/Time-of-check-to-time-of-use) attacks.

- openat()
- faccessat()
- fchmodat()
- fchownat()
- fstatat()
- futimesat()
- linkat()
- mkdirat()
- mknodat()
- readlinkat()
- renameat()
- symlinkat()
- unlinkat()
- mkfifoat()
- fdopendir()



### File descriptors as capabilities

> NOTE: 
> 一、初次阅读下面这段话的时候，我是比较疑惑的: Linux中file descriptor的scope是process，也就是说file descriptor仅仅是在一个process内有效的，那"passed between processes"有什么意义呢？后来查阅了一些资料，发现:
>
> 1、是有意义的，Linux进行了特殊的实现，在`Pass-file-descriptor`章节对此进行了讨论。
>
> 2、由于Linux采用的是"File descriptors as capabilities"，那当passing一个file descriptor的时候，同时也就passing了"capabilities"。

Unix file descriptors behave in many ways as [capabilities](https://en.wikipedia.org/wiki/Capability-based_security). They can be passed between processes across [Unix domain sockets](https://en.wikipedia.org/wiki/Unix_domain_socket) using the `sendmsg()` system call. Note, however, that what is actually passed is a reference to an "open file description" that has mutable state (the file offset, and the file status and access flags). This complicates the secure use of file descriptors as capabilities, since when programs share access to the same open file description, they can interfere(冲突、妨碍) with each other's use of it by changing its offset or whether it is blocking or non-blocking, for example.[[6\]](https://en.wikipedia.org/wiki/File_descriptor#cite_note-6)[[7\]](https://en.wikipedia.org/wiki/File_descriptor#cite_note-7) In operating systems that are specifically designed as capability systems, there is very rarely any mutable state associated with a capability itself.

A Unix process' file descriptor table is an example of a [C-list](https://en.wikipedia.org/wiki/C-list_(computer_security)).

