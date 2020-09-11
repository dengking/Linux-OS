# 2 Getting In and Out of gdb



## 2.1 Invoking gdb

You can also run `gdb` with a variety of arguments and options, to specify more of your debugging environment at the outset（开端）.



```shell
gdb program
```



```shell
gdb program core
```

You can, instead, specify a **process ID** as a second argument, if you want to debug a **running process**:

```shell
gdb program 1234
```



You can optionally have gdb pass any arguments after the executable file to the inferior using `--args`. This option stops option processing.

```shell
gdb --args gcc -O2 -c foo.c
```

> NOTE: 在linux OS中，我们常常使用script来启动application，这是因为启动它们的时候需要传入一堆args，上述指令告诉了我们如何来调试使用scrip启动的application。

This will cause `gdb` to debug `gcc`, and to set `gcc`’s command-line arguments (see Section 4.3 [Arguments], page 30) to ‘`-O2 -c foo.c`’.



```shell
gdb --silent
gdb -q
gdb --quite
```



### 2.1.1 Choosing Files

## 2.3 Shell Commands

If you need to execute occasional shell commands during your debugging session, there is no need to leave or suspend `gdb`; you can just use the `shell` command.

```
shell command-string
!command-string
```

The utility `make` is often needed in development environments. You do not have to use the shell command for this purpose in gdb:

```shell
make make-args
```



## 2.4 Logging Output

You may want to save the output of gdb commands to a file. There are several commands to control gdb’s logging.

```
set logging on

set logging off
```

> NOTE: 开启或关闭 logging

### Application: 将程序运行输出重定向到指定文件

`run > outfile`

参考:

- https://stackoverflow.com/a/19715092

`set logging on`

如何实现自定义文件？

参考: 

- stackoverflow [Gdb print to file instead of stdout](https://stackoverflow.com/questions/5941158/gdb-print-to-file-instead-of-stdout) `#` [A](https://stackoverflow.com/a/5941271)

`tee` 

Extending on @qubodup's answer

```
gdb core.3599 -ex bt -ex quit |& tee backtrace.log
```

the `-ex` switch runs a gdb command. So the above loads the core file, runs `bt` command, then `quit` command. Output is written to `backtrace.log` and also on the screen.

Another useful gdb invocation (giving stacktrace with local variables from all threads) is

```
gdb core.3599 -ex 'thread apply all bt full' -ex quit
```

参考:

- https://stackoverflow.com/a/36821621