# The Implementation of epoll

一、作者不允许转载

## [The Implementation of epoll (1)](https://idndx.com/the-implementation-of-epoll-1/) 



### The Old Days

这段话的大意是: `select`、`poll` 都诞生地比较早，当时的concurrent server的量级是 "thousands of concurrent clients"，而对于当今的C10K concurrent  server，它们是应付不来的。

一、 `select`、`poll` 的实现思路是类似的: 

1、data structure: array

"application generates an array of fds that it is interested in"

2、线性遍历array of fds来逐个判断是否有event发生

```
for fd in fds:
    poll(fd)
```

> 需要注意: 上述`poll`不是man 2 poll

3、如何将结果通知给用户呢？

`select` 生成一个bit array，并将它copy到user space，用这个bit array来告诉用户结果

`poll` 则是直接操作用户传入的 `pollfd` struct，避免了`select`的copy



二、它们的source code

`fs/select.c`

### The Problem

这段话的大意是:

`select`、`poll`的线性扫描的复杂度是O(N)，这就决定了它们无法应付大量级的file descriptor，比如当今的互联网应用，动则10万的TCP连接；

显然，对于高并发的互联网应用，如果还使用 `select`、`poll` 的话，显然它们会将很多CPU资源浪费在polling the file descriptor，显然这将直接降低the scalability and responsiveness of the server。

基于上述分析，我们大概知道了epoll所要解决的问题了: 高效地处理C10K问题。



### An Overview

这段话重要介绍了epoll的设计思路:

`epoll`没有采用`select`、`poll`的"building and passing a giant array of file descriptors into the Kernel every time"的方式(这种方式是非常低效的)

epoll采用的是:

一、`epoll` instance

这个是一个in kernel data structure，它是epoll的核心

二、register file descriptor

用户提供`epoll_ctrl`来向`epoll` instance注册file descriptor

三、"And rather than polling a whole array of file descriptors, the `epoll` instance **monitors** registered file descriptors and "report" events to the application when being asked."

原文的这段话是需要对比`select`来进行理解的: `select`使用固定大小的`fd_set`来传递fd，显然在内核中，需要遍历它来找到用户设置的fd，相比之下，`epoll`提供了register的方式，所以epoll就可以直接对用户注册的fd进行监控，

### The `epoll` Instance

这段话介绍了`epoll` Instance的实现:

一、source code

`epoll` Instance对应的是kernel data structure `struct eventpoll`, defined in `fs/eventpoll.c`

二、`epoll` instance的实现也是遵循"everything is a file descriptor"的

### How does the epoll instance "remembers" file descriptors?

这段话告诉我们: 

一、`epoll` 是使用 [Red–black tree](https://en.wikipedia.org/wiki/Red–black_tree) (后面简称为RB tree)来组织向它注册的file descriptor的，下面对RB tree进行介绍:

RB tree node: `struct epitem`

RB tree node comparator、key: `struct epoll_filefd`

```C++
struct epoll_filefd {
	struct file *file; // pointer to the target file struct corresponding to the fd
	int fd; // target file descriptor number
} __packed;
```

`ep_cmp_ffd()` 来对 `epoll_filefd` 进行比较:

1、首先比较`file` memory address

2、如果`file` memory address相等，则比较`fd`



显然，按照上述的方式来组织fd，查找它的算法复杂度是O(log(N))



## [The Implementation of epoll (2)](https://idndx.com/the-implementation-of-epoll-2/)



### The `ep_insert()` Function

`poll_table`

