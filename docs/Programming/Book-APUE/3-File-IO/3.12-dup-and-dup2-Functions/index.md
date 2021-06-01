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



The new file descriptor that is returned as the value of the functions shares the same **file table entry** as the fd argument. We show this in Figure 3.9.

![](./APUE-3.12-Figure-3.9-Kernel-data-structures-after-dup(1).png)

In this figure, we assume that when it’s started, the process executes

```c
newfd = dup(1);
```





需要搞清楚 [`dup`](http://pubs.opengroup.org/onlinepubs/007904975/functions/dup.html) 和 [`dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 的使用场景

受chapter 3的exercise 3.4的下面这段代码的启发：

```c
dup2(fd, 0);
dup2(fd, 1);
dup2(fd, 2);
if (fd > 2)
	close(fd);
```

***SUMMARY*** : 在第一次阅读上述代码的时候，我没有搞清楚为什么作者会添加`if (fd > 2)	close(fd);`，看来[APPLICATION USAGE](#APPLICATION USAGE)后才知其中缘由：上述代码作者的目的在于将`STDIN_FILENO` ,`STDOUT_FILENO` ,`STDERR_FILENO` 全部都重定向到`fd`上，添加上`if (fd > 2)	close(fd);`的目的在于clean up，即将无用的file descriptor全部都关闭掉，这样可以有很多好处，如防止leak to child process；



可以发现`dup`系列函数与IO Redirection有关，通过Google，我在[这篇文章](http://cau.ac.kr/~bongbong/linux09/linux09-additional.ppt)中找到了一段代码，它就是使用的`dup`系列函数来实现IO Redirection。

刚刚阅读了opengroup的关于`dup`系列函数的文档，其中其实已经对`dup`系列函数的usage进行了非常详细的介绍，参见[opengroup `dup` and `dup2`](#opengroup `dup` and `dup2`) ；



关于`dup`函数的用途，下面截取自stackoverflow的一些问答非常好；