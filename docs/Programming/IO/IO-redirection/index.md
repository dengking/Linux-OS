# IO redirection



## 如何实现？

一、APUE chapter 3的 exercise 3.4 中的source code 给出了使用`dup`系列函数来实现IO redirection的demo code，参见 `Book-APUE\3-File-IO\3.12-dup-and-dup2-Functions` 章节

二、在 opengroup [`dup` and `dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 中，给出了也给出了使用`dup`系列函数来实现IO redirection的example code

这里给出`dup`函数的原型：

```c
int dup(int fildes);
int dup2(int fildes, int fildes2);
```



### Example: Redirecting Standard Output to a File

The following example closes standard output for the current processes, re-assigns standard output to go to the file referenced by *pfd*, and closes the original file descriptor to clean up.

```c
#include <unistd.h>
...
int pfd;
...
close(1);
dup(pfd);
close(pfd);
...
```

> NOTE: 
>
> 关于上述code的解释，参见 stackoverflow [Re-opening stdout and stdin file descriptors after closing them](https://stackoverflow.com/questions/9084099/re-opening-stdout-and-stdin-file-descriptors-after-closing-them) # [A](https://stackoverflow.com/a/9084222)
>
> 

上述代码只是一个demo，如果我们要将这种用法推广的话，它就是：将`STD_IN`，`STD_OUT`，`STD_ERR`进行重定向，将它们重定向到一个另外一个`fildes`所指向的文件（everything in Unix is a file），在这种用法中，后续就不再使用`fildes`了，而仅仅使用`stdio`；所以这种用法中，往往是需要将`fildes`给关闭掉的，所以这种用法中，往往后面还会涉及到一个`close(fildes)`系统调用；

> NOTE: "tag-Linux IO data structure-three tables-file descriptor as reference count memory management"

上述代码使用`dup2`来进行改写就是:

```C
dup2(pfd, STDIN_FILENO);
close(pfd);
```

显然，这种用法和下面的用法相比它的一个显著特征就是它需要用户显式地调用一下`close(fildes)`。

在APUE的chapter15.2节的图15-6的程序就是使用的这种用法，在这个例子的后面，作者对代码进行了一番解释，其中就提及了`dup2()`和`close`的搭配使用（其实就是这种用法）；作者详细解释的是为什么在执行`dup2()`和`close()`之前要先检查一下`fildes`和`fildes2`是否相等；作者给出的支持要进行检查的理由是：如果`fildes`和`fildes2`和相等，则显然`dup2`并不会`close(fildes2)`，然后按照我们的这种用法，会显式地调用一下`close(fildes)`，则就存在将`fildes`和`fildes2`指向的文件传递关闭可能（如果这个文件已经没有file descriptor指向它的话），则后续我们如果还使用`fildes2`的话，其实使用的是一个null file descriptor，因为它已经并不指向任何文件了；

> NOTE: APUE chapter 3的 exercise 3.4 中的source code 就是使用的`dup2` + `close` 的做法

所以APUE的作者在此提出的这种保护性的编程措施是非常好的；



### Example: Redirecting Error Messages



The following example redirects messages from *stderr* to *stdout*.

```c
#include <unistd.h>
...
dup2(1, 2);
...
```



这种用法和上述用法有异，他们两者的本质差别在于是否要将将`fildes`给关闭；显然在这种用法中，需要关闭的是`fildes2`。







## stackoverflow [Re-opening stdout and stdin file descriptors after closing them](https://stackoverflow.com/questions/9084099/re-opening-stdout-and-stdin-file-descriptors-after-closing-them)

I'm writing a function, which, given an argument, will either redirect the **`stdout`** to a file or read the `stdin` from a file. To do this I close the **file descriptor** associated with the **`stdout`** or **`stdin`**, so that when I open the file it opens under the descriptor that I just closed. This works, but the problem is that once this is done, I need to restore the `stdout` and `stdin` to what they should really be.

What I can do for stdout is `open("/dev/tty",O_WRONLY);` But I'm not sure why this works, and more importantly I don't know of an equivalent statement for `stdin`.

So I have, for `stdout`

```c++
close(1);
if (creat(filePath, O_RDWR) == -1)
{
    exit(1);
}
```

and for stdin

```c++
close(0);
if (open(filePath, O_RDONLY) == -1)
{
    exit(1);
}
```

### [A](https://stackoverflow.com/a/9084222)

> NOTE: 
>
> 这个答案展示了:
>
> 对file descriptor进行save、redirect、restore

You should use `dup()` and `dup2()` to clone a file descriptor.

```
int stdin_copy = dup(0);
int stdout_copy = dup(1);
close(0);
close(1);

int file1 = open(...);
int file2 = open(...);

< do your work. file1 and file2 must be 0 and 1, because open always returns lowest unused fd >

close(file1);
close(file2);
dup2(stdin_copy, 0);
dup2(stdout_copy, 1);
close(stdin_copy);
close(stdout_copy);
```

> NOTE: 
>
> 在 APUE chapter 3的 exercise 3.4 中的source code 给出了使用`dup2`来实现上述code中IO redirection的demo code，APUE chapter 3的 exercise 3.4 中的source code 可读性更好

However, there's a minor detail you might want to be careful with (from man dup):

> The two descriptors do not share file descriptor flags (the close-on-execflag). The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate descriptor is off.

If this is a problem, you might have to restore the close-on-exec flag, possibly using dup3() instead of dup2() to avoid race conditions.

Also, be aware that if your program is multi-threaded, other threads may accidentally write/read to your remapped stdin/stdout.

### A

I think you can "save" the descriptors **before redirecting**:

```c++
int save_in, save_out;

save_in = dup(STDIN_FILENO);
save_out = dup(STDOUT_FILENO);
```

Later on you can use `dup2` to restore them:

```C++
/* Time passes, STDIN_FILENO isn't what it used to be. */
dup2(save_in, STDIN_FILENO);
```



