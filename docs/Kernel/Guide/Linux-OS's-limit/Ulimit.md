# Ulimit

## [ULIMIT(3)](http://man7.org/linux/man-pages/man3/ulimit.3.html) 



## [ulimit(1)](https://docs.oracle.com/cd/E19683-01/816-0210/6m6nb7mo3/index.html)



### `ulimit -c unlimited`

如果你是一个linux OS的开发者，建议你在你的`.bash_profile`中添加上上述语句，它告诉OS，不限制core dump file的大小，这样当你的process执行了错误的操作而被OS终止的时候，一来，你可以及时的获知这种情况的发送，而来，你可以通过`gdb`来进行分析。



#### ulimit: core file size: cannot modify limit: Operation not permitted

有的时候，执行`ulimit -c unlimited`会报这种错误，修改方案参见这个[链接](https://askubuntu.com/a/642661)

> `ulimit` is a shell builtin, and thus only affects the current shell, and processes started by that shell:
>
> ```bsh
> $ type ulimit
> ulimit is a shell builtin
> ```
>
> From [`man ulimit`](http://manpages.ubuntu.com/ulimit.1posix):
>
> ```bsh
> The  ulimit  utility  shall  set  or report the file-size writing limit
> imposed on files written by the shell and its child processes (files of
> any  size  may be read). Only a process with appropriate privileges can
> increase the limit.
> ```
>
> So, yes, child processes are affected.
>
> To set limits permanently or for all processes, edit [`/etc/security/limits.conf`](http://manpages.ubuntu.com/limits.conf.5) and reboot. The examples in the manpage are fairly good. You just need to add something like:
>
> ```bsh
> username - core unlimited
> ```