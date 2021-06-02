# 3.12 `dup` and `dup2` Functions

An existing file descriptor is duplicated by either of the following functions:

```C++
#include <unistd.h>
int dup(int fd);
int dup2(int fd, int fd2);
```

Both return: new file descriptor if OK, `−1` on error.

> NOTE: 
>
> `dup` 和 `dup2` 所copy的是file descriptor，并不file table entry。这是它和open的差异。

With `dup2`, we specify the value of the new descriptor with the `fd2` argument. (下面根据`fd2`是否open，可以对它的用法进行分类: )

一、If `fd2` is already open, it is first closed. If `fd` equals `fd2`, then `dup2` returns `fd2` without closing it. 

> NOTE: 
>
> 这种用法是将`fd2`重定向到`fd`，这种情况下，会首先`close fd2`，然后让`fd2`的file descriptor的file pointer指向`fd`的file table entry；此时`dup2`函数执行的功能非常类似于指针赋值。

二、Otherwise, the `FD_CLOEXEC` file descriptor flag is cleared for `fd2`, so that `fd2` is left open if the process calls `exec`.

> NOTE: 在下面的"File descriptor flag"节中会对"the `FD_CLOEXEC` file descriptor flag "进行介绍，结合其中的内容可知这段话的意思是:  `fd2` file descriptor的"`FD_CLOEXEC` file descriptor flag"的默认值是 "cleared" 的，因此"`fd2` is left open if the process calls `exec`"。
>
> 在 stackoverflow [Re-opening stdout and stdin file descriptors after closing them](https://stackoverflow.com/questions/9084099/re-opening-stdout-and-stdin-file-descriptors-after-closing-them) 的第一个回答中，有着各加直接的说明:
>
> > The two descriptors do not share file descriptor flags (the close-on-exec flag). The close-on-exec flag (`FD_CLOEXEC`; see `fcntl(2)`) for the duplicate descriptor is off.
>
> 也就是说，`dup`系列函数是不copy "file descriptor flags"的。

The new file descriptor that is returned as the value of the functions shares the same **file table entry** as the fd argument. We show this in Figure 3.9.

![](./APUE-3.12-Figure-3.9-Kernel-data-structures-after-dup(1).png)

In this figure, we assume that when it’s started, the process executes

```c
newfd = dup(1);
```



## File descriptor flag

Each descriptor has its own set of **file descriptor flags**. As we describe in Section 3.14, the close-on-exec file descriptor flag for the new descriptor is always cleared by the `dup` functions.



## `fcntl` equivalent

Similarly, the call

```C++
dup2(fd, fd2);
```

is equivalent to

```C++
close(fd2);
fcntl(fd, F_DUPFD, fd2);
```

In this last case, the `dup2` is not exactly the same as a `close` followed by an `fcntl`. The differences are as follows:

1、`dup2` is an atomic operation, whereas the alternate form involves two function calls. It is possible in the latter case to have a signal catcher called between the `close` and the `fcntl` that could modify the file descriptors. (We describe signals in Chapter 10.) The same problem could occur if a different thread changes the file descriptors. (We describe threads in Chapter 11.)

2、There are some `errno` differences between `dup2` and `fcntl`.



## 使用场景

需要搞清楚 [`dup`](http://pubs.opengroup.org/onlinepubs/007904975/functions/dup.html) 和 [`dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 的使用场景: 

1、`dup`系列函数可以用于实现IO Redirection，通过Google，我在[这篇文章](http://cau.ac.kr/~bongbong/linux09/linux09-additional.ppt)中找到了一段代码，它就是使用的`dup`系列函数来实现IO Redirection。





## chapter 3的exercise 3.4

许多程序都包含下面一段代码:

```c
dup2(fd, 0);
dup2(fd, 1);
dup2(fd, 2);
if (fd > 2)
	close(fd);
```

为了说明`if`语句的必要性，假设`fd`是1，画出每次调用`dup2`时，3个描述符项及相应的文件表项的变化情况。然后画出`fd`为3的情况。

### 解答

If `fd` is 1, then the `dup2(fd, 1)` returns `1` without closing file descriptor `1`. (Remember our discussion of this in Section 3.12.) After the three calls to `dup2`, all three descriptors point to the same file table entry. Nothing needs to be closed.

If `fd` is `3`, however, after the three calls to `dup2`, four descriptors are pointing to the same **file table entry**. In this case, we need to `close` descriptor `3`.

### opengroup [`dup` and `dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 中的说明

在第一次阅读上述代码的时候，我没有搞清楚为什么作者会添加`if (fd > 2)	close(fd);`，看来opengroup [`dup` and `dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 中的解释后才知其中缘由：

1、上述代码作者的目的在于将`STDIN_FILENO` ,`STDOUT_FILENO` ,`STDERR_FILENO` 全部都重定向到`fd`上，添加上`if (fd > 2)	close(fd);`的目的在于clean up，即将无用的file descriptor全部都关闭掉，这样可以有很多好处，如防止leak to child process；

> tag-not leak泄露resource into child process-unintended file descriptor

