# IO redirection



需要搞清楚 [`dup`](http://pubs.opengroup.org/onlinepubs/007904975/functions/dup.html) 和 [`dup2`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html) 的使用场景

可以发现`dup`系列函数与IO Redirection有关，通过Google，我在[这篇文章](http://cau.ac.kr/~bongbong/linux09/linux09-additional.ppt)中找到了一段代码，它就是使用的`dup`系列函数来实现IO Redirection。

刚刚阅读了opengroup的关于`dup`系列函数的文档，其中其实已经对`dup`系列函数的usage进行了非常详细的介绍，参见[opengroup `dup` and `dup2`](#opengroup  and ) ；



关于`dup`函数的用途，下面截取自stackoverflow的一些问答非常好；



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

## [A](https://stackoverflow.com/a/9084222)

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

However, there's a minor detail you might want to be careful with (from man dup):

> The two descriptors do not share file descriptor flags (the close-on-execflag). The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate descriptor is off.

If this is a problem, you might have to restore the close-on-exec flag, possibly using dup3() instead of dup2() to avoid race conditions.

Also, be aware that if your program is multi-threaded, other threads may accidentally write/read to your remapped stdin/stdout.

# [two file descriptors to same file](https://stackoverflow.com/questions/5284062/two-file-descriptors-to-same-file)

Using the posix `read()` `write()` linux calls, is it guaranteed that if I write through one file descriptor and read through another file descriptor, in a serial fashion such that the two actions are mutually exclusive of each other... that my read file descriptor will always see what was written last by the write file descriptor?

I believe this is the case, but I want to make sure and the man page isn't very helpful on this

## [A](https://stackoverflow.com/a/5284108)

It depends on where you got the two file descriptors. If they come from a `dup(2)` call, then they share file offset and status, so doing a `write(2)` on one will affect the position on the other. If, on the other hand, they come from two separate `open(2)` calls, each will have their own **file offset** and **status**.

A **file descriptor** is mostly just a **reference** to a kernel file structure, and it is that kernel structure that contains most of the state. When you `open(2)` a file, you get a new kernel file structure and a new file descriptor that refers to it. When you `dup(2)` a file descriptor (or pass a file descriptor through sendmsg), you get a new reference to the same kernel file struct.

