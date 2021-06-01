

# opengroup [`dup` and `dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)

## NAME

`dup`, `dup2` - duplicate an open file descriptor

## SYNOPSIS

```C++
#include <unistd.h>
int dup(int fildes);
int dup2(int fildes, int fildes2);
```

## EXAMPLES

### Redirecting Standard Output to a File

The following example closes **standard output** for the current processes, re-assigns **standard output** to go to the file referenced by *pfd*, and closes the original file descriptor to **clean up**.

```C++
#include <unistd.h>
// ...
int pfd;
// ...
close(1);
dup(pfd);
close(pfd);
// ...
```

> NOTE: 
>
> 由于file descriptor的scope是process，所以file descriptor不存在进程间的race condition；并且`dup`函数能够在当前可用文件描述符中的最小值上对`pfd`进行赋值，所以在执行完成`close(1)`后，则当前可用文件描述符中的最小值就是`1`，所以上述能够保证`dup(pfd)`在`1`上进行dup；

### Redirecting Error Messages

The following example redirects messages from *stderr* to *stdout*.

```C++
#include <unistd.h>
...
dup2(1, 2);
...
```

## APPLICATION USAGE

Implementations may use **file descriptors** that must be inherited into child processes for the child process to remain conforming(一致性), such as for message catalog(消息目录) or tracing purposes. Therefore, an application that calls *`dup2()`* with an arbitrary integer for *`fildes2`* risks non-conforming(不相符的) behavior, and *`dup2()`* can only portably be used to overwrite file descriptor values that the application has obtained through explicit actions, or for the three file descriptors corresponding to the standard file streams. In order to avoid a **race condition** of leaking an unintended file descriptor into a child process, an application should consider opening all file descriptors with the `FD_CLOEXEC` bit set unless the file descriptor is intended to be inherited across [*exec*](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html).

> NOTE: 实现可以使用必须继承到子进程的文件描述符，以使子进程保持一致，例如用于消息目录或跟踪目的。 因此，为`fildes2`调用带有任意整数的`dup2`的应用程序存在不符合行为的风险，而`dup2`只能用于覆盖应用程序通过显式操作获取的文件描述符值，或者用于三个文件描述符 对应于标准文件流。 为了避免将非预期文件描述符泄漏到子进程中的竞争条件，应用程序应考虑打开所有文件描述符并设置`FD_CLOEXEC`位，除非文件描述符是要跨exec继承的。

