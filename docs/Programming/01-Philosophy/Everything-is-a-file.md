# Everything is a file

“Everything is a file”是Unix-like OS的一个philosophy，它对于在linux OS中进行programming大有裨益。

## 维基百科[Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file)

***"Everything is a file"*** describes one of the defining(最典型的) features of [Unix](https://en.wikipedia.org/wiki/Unix), and its derivatives — that a wide range of input/output [resources](https://en.wikipedia.org/wiki/System_resource) such as documents, directories, hard-drives, modems, keyboards, printers and even some inter-process and network communications are simple **streams of bytes** exposed through the [filesystem name space](https://en.wikipedia.org/wiki/Unix_directory_structure). 

***SUMMARY*** : 最后一段话是对***"Everything is a file"*** 含义的解释：即将这些resource都看做是file（**streams of bytes** ）

***SUMMARY*** : 上述 hard-drives，modems，keyboards，等都是device，显然在Unix中，它们都被看做成了file（**streams of bytes** ）

The advantage of this approach is that the same set of tools, utilities and [APIs](https://en.wikipedia.org/wiki/API) can be used on a wide range of resources. There are a number of [file types](https://en.wikipedia.org/wiki/Unix_file_types). When a file is opened, a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) is created. The [file path](https://en.wikipedia.org/wiki/Path_(computing)) becoming the addressing system and the file descriptor being the byte stream I/O interface. But **file descriptors** are also created for things like [anonymous pipes](https://en.wikipedia.org/wiki/Anonymous_pipe) and [network sockets](https://en.wikipedia.org/wiki/Network_socket) via different methods. So it is more accurate to say ***"Everything is a file descriptor"***.[[2\]](https://en.wikipedia.org/wiki/Everything_is_a_file#cite_note-2)[[3\]](https://en.wikipedia.org/wiki/Everything_is_a_file#cite_note-3)

Additionally, a range of [pseudo and virtual filesystems](https://en.wikipedia.org/wiki/List_of_file_systems#Pseudo-_and_virtual_file_systems) exists which exposes information about processes and other system information in a hierarchical file-like structure. These are [mounted](https://en.wikipedia.org/wiki/Mount_(computing)) into the [single file hierarchy](https://en.wikipedia.org/wiki/File_system#Unix-like_operating_systems).

An example of this purely virtual filesystem is under [/proc](https://en.wikipedia.org/wiki/Procfs) that exposes many system properties as files.

All of these "files" have standard Unix file attributes such as [an owner](https://en.wikipedia.org/wiki/Chown) and [access permissions](https://en.wikipedia.org/wiki/Chmod), and can be queried by the same [classic Unix tools](https://en.wikipedia.org/wiki/List_of_Unix_commands) and [filters](https://en.wikipedia.org/wiki/Filter_(Unix)). However, this is not universally considered a fast or portable approach. Some operating systems do not even mount /proc by default due to security or speed concerns.[[4\]](https://en.wikipedia.org/wiki/Everything_is_a_file#cite_note-4) It is, though, used heavily by both the widely installed [BusyBox](https://en.wikipedia.org/wiki/BusyBox) [[5\]](https://en.wikipedia.org/wiki/Everything_is_a_file#cite_note-5) on [embedded systems](https://en.wikipedia.org/wiki/Embedded_systems) and by procps, which is used on most [Linux](https://en.wikipedia.org/wiki/Linux) systems. In both cases it is used in implementations of process-related [POSIX](https://en.wikipedia.org/wiki/POSIX) shell commands. It is similarly used on [Android](https://en.wikipedia.org/wiki/Android_(operating_system)) systems in the operating system's Toolbox program.[[6\]](https://en.wikipedia.org/wiki/Everything_is_a_file#cite_note-6)

Unix's successor [Plan 9](https://en.wikipedia.org/wiki/Plan_9_from_Bell_Labs) took this concept into [distributed computing](https://en.wikipedia.org/wiki/Distributed_operating_system) with the [9P](https://en.wikipedia.org/wiki/9P_(protocol)) protocol.

## [Why is “Everything is a file” unique to the Unix operating systems?](https://superuser.com/questions/364152/why-is-everything-is-a-file-unique-to-the-unix-operating-systems)

### [A](https://superuser.com/a/364157)

> So, why is this unique to Unix?

Typical operating systems, prior to Unix, treated files one way and treated each peripheral device(外设) according to the characteristics of that device. That is, if the output of a program was written to a file on disk, that was the only place the output could go; you could not send it to the printer or the tape drive. Each program had to be aware of each device used for input and output, and have command options to deal with alternate I/O devices.

**Unix treats all devices as files**, but with special attributes. To simplify programs, *standard input* and *standard output* are the default input and output devices of a program(这句话解释了*standard input*，*standard output* 的原因 ). So program output normally intended for the console screen could go anywhere, to a disk file or a printer or a serial port. This is called **I/O redirection**.

> Does other operating systems such as Windows and Macs not operate on files?

Of course all modern OSes support various filesystems and can "operate on files", but the distinction is how are devices handled? Don't know about Mac, but Windows does offer some I/O redirection.

> And, compared to what other operating systems is it unique?

Not really any more. Linux has the same feature. Of course, if an OS adopts I/O redirection, then it tends to use other Unix features and ends up Unix-like in the end.

## 维基百科[Event loop](https://en.wikipedia.org/wiki/Event_loop)

在这篇文章的[File_interface](https://en.wikipedia.org/wiki/Event_loop#File_interface)章节对every thing is a file进行阐释；



## 维基百科[Device file](https://en.wikipedia.org/wiki/Device_file)

将device抽象为file，这就是everything is a file最好的体现；

## [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/index.html)

在这本书的第二章[2. What is a socket?](https://beej.us/guide/bgnet/html/multi/theory.html)中对everything is a file进行了阐述；



## APUE chapter 16 Network IPC: Sockets

昨天在阅读APUE的的chapter 16 Network IPC: Sockets时，所想：

everything in Unix is a file，所以和我应该采用看待普通文件的方式来看待Unix的socket。socket和file一样，都是通过**file descriptor**来进行访问。POSIX中提供的操作socket的函数的第一个参数都是`fd`，表示这个socket的file descriptor，这种做法和file是非常类似的。



[`socket()`](http://man7.org/linux/man-pages/man2/socket.2.html) 函数就好比[create()](https://linux.die.net/man/2/creat)函数。其实APUE的作者在16.2中就对比了Unix的针对file的API和针对socket的API。



如果从面向对象的角度来构造POSIX的文件api和socket api的话，接受file descriptor的api都可以作为成员函数，每个对象都有一个file descriptor。

在[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/index.html)的2. What is a socket?章节也是从file descriptor的角度来描述socket的；



## Why everything in Unix is a file



Unix是典型的[Monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)，所以它需要将很多东西封装好而只提供一个descriptor来供用户使用，这个descriptor从用户的角度来看就是file descriptor。显然，everything in Unix is a file是一种简化的抽象，它让用户更加容易理解。

当然，从内核的实现上是否真的是如此我目前还不得而知，但是从用户的角度来看，这是非常正确的。





## Everything in Unix is file 和 file API

需要注意的是，everything in Unix is file是一个个philosophy，它是概念上的，它更多的是指：将它看做是一个file，我们可以对其进行IO，但是这并不是指我们可以对everything in Unix都使用Unix file的API。

关于这一点，APUE的16.2 Socket Descriptors进行了一些描述；

关于这一点，在[pipe(7) - Linux man page](https://linux.die.net/man/7/pipe)的I/O on pipes and FIFOs章节中提及：

> It is not possible to apply [lseek(2)](https://linux.die.net/man/2/lseek) to a pipe.

显然，我们可以*认为*（从逻辑上）pipe是一个file，但是它实际上并不是file，所以，并不能够对其使用lseek系统调用。



## 从kernel实现的角度来看待everything in Unix is file

引用自维基百科[File descriptor](https://en.wikipedia.org/wiki/File_descriptor) :

> In [Unix-like](https://en.wikipedia.org/wiki/Unix-like) systems, file descriptors can refer to any [Unix file type](https://en.wikipedia.org/wiki/Unix_file_type) named in a file system. As well as regular files, this includes [directories](https://en.wikipedia.org/wiki/Directory_(file_systems)), [block](https://en.wikipedia.org/wiki/Block_device) and [character devices](https://en.wikipedia.org/wiki/Character_device) (also called "special files"), [Unix domain sockets](https://en.wikipedia.org/wiki/Unix_domain_socket), and [named pipes](https://en.wikipedia.org/wiki/Named_pipe). File descriptors can also refer to other objects that do not normally exist in the file system, such as [anonymous pipes](https://en.wikipedia.org/wiki/Anonymous_pipe)and [network sockets](https://en.wikipedia.org/wiki/Network_socket).

NOTE: [Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file) ；从kernel实现的角度来看看待everything in Unix is file，Unix-like system是[monolithic kernel](https://en.wikipedia.org/wiki/Monolithic_kernel)，上面提到的这些device或者file都是由kernel来进行维护，它们都有对应的kernel structure；我们通过file descriptor来引用这些kernel structure，我们只能够通过system call来对这些kernel structure进行操作；

对这个观点的验证包括：

- [EPOLL instance](http://man7.org/linux/man-pages/man2/epoll_create.2.html)