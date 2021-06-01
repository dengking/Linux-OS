# IO redirection







需要搞清楚 [`dup`](http://pubs.opengroup.org/onlinepubs/007904975/functions/dup.html) 和 [`dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 的使用场景

可以发现`dup`系列函数与IO Redirection有关，通过Google，我在[这篇文章](http://cau.ac.kr/~bongbong/linux09/linux09-additional.ppt)中找到了一段代码，它就是使用的`dup`系列函数来实现IO Redirection。

刚刚阅读了opengroup的关于`dup`系列函数的文档，其中其实已经对`dup`系列函数的usage进行了非常详细的介绍，参见[opengroup `dup` and `dup2`](#opengroup  and ) ；



关于`dup`函数的用途，下面截取自stackoverflow的一些问答非常好；







## opengroup [`dup` and `dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)

### NAME

`dup`, `dup2` - duplicate an open file descriptor

### SYNOPSIS

```C++
#include <unistd.h>
int dup(int fildes);
int dup2(int fildes, int fildes2);
```

### EXAMPLES

#### Redirecting Standard Output to a File

The following example closes **standard output** for the current processes, re-assigns **standard output** to go to the file referenced by *pfd*, and closes the original file descriptor to **clean up**.

```
#include <unistd.h>
...
int pfd;
...
close(1);
dup(pfd);
close(pfd);
...
```

***SUMMARY\*** : 由于file descriptor的scope是process，所以file descriptor不存在进程间的race condition；并且`dup`函数能够在当前可用文件描述符中的最小值上对`pfd`进行赋值，所以在执行完成`close(1)`后，则当前可用文件描述符中的最小值就是`1`，所以上述能够保证`dup(pfd)`在`1`上进行dup；

##### Redirecting Error Messages

The following example redirects messages from *stderr* to *stdout*.

```
#include <unistd.h>
...
dup2(1, 2);
...
```

#### APPLICATION USAGE

Implementations may use **file descriptors** that must be inherited into child processes for the child process to remain conforming(一致性), such as for message catalog or tracing purposes. Therefore, an application that calls *dup2*() with an arbitrary integer for *fildes2* risks non-conforming behavior, and *dup2*() can only portably be used to overwrite file descriptor values that the application has obtained through explicit actions, or for the three file descriptors corresponding to the standard file streams. In order to avoid a **race condition** of leaking an unintended file descriptor into a child process, an application should consider opening all file descriptors with the `FD_CLOEXEC` bit set unless the file descriptor is intended to be inherited across [*exec*](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html).

***TRANSLATION\*** : 实现可以使用必须继承到子进程的文件描述符，以使子进程保持一致，例如用于消息目录或跟踪目的。 因此，为fildes2调用带有任意整数的dup2（）的应用程序存在不符合行为的风险，而dup2（）只能用于覆盖应用程序通过显式操作获取的文件描述符值，或者用于三个文件描述符 对应于标准文件流。 为了避免将非预期文件描述符泄漏到子进程中的竞争条件，应用程序应考虑打开所有文件描述符并设置FD_CLOEXEC位，除非文件描述符是要跨exec继承的。

#### RATIONALE

The *dup*() function is redundant. Its services are also provided by the [*fcntl*()](https://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html) function. It has been included in this volume of POSIX.1-2017 primarily for historical reasons, since many existing applications use it. On the other hand, the *dup2*() function provides unique services, as no other interface is able to atomically replace an existing file descriptor.

The *dup2*() function is not marked obsolescent because it presents a type-safe version of functionality provided in a type-unsafe version by [*fcntl*()](https://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html). It is used in the POSIX Ada binding.

The *dup2*() function is not intended for use in critical regions as a synchronization mechanism.

In the description of [EBADF], the case of *fildes* being out of range is covered by the given case of *fildes* not being valid. The descriptions for *fildes* and *fildes2* are different because the only kind of invalidity that is relevant for *fildes2* is whether it is out of range; that is, it does not matter whether *fildes2* refers to an open file when the *dup2*() call is made.