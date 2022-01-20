# 将程序运行输出重定向到指定文件

## 使用内置 logging

一、2.4 Logging Output



## stackoverflow [GDB print to file instead of stdout](https://stackoverflow.com/questions/5941158/gdb-print-to-file-instead-of-stdout)

### [A](https://stackoverflow.com/a/19715092)

```shell
run > outfile
```

### [A](https://stackoverflow.com/a/5941271/10173843)

> NOTE: 
>
> `set logging on`

You need to enable logging:

```
(gdb) set logging on
```

Now GDB will log to `./gdb.txt`. You can tell it which file to use:

```
(gdb) set logging file my_god_object.log
```

And you can examine the current logging configuration:

```
(gdb) show logging
```

### [A](https://stackoverflow.com/a/36821621/10173843)

> NOTE: 
>
> `tee` 

Extending on @qubodup's answer

```shell
gdb core.3599 -ex bt -ex quit |& tee backtrace.log
```

the `-ex` switch runs a gdb command. So the above loads the core file, runs `bt` command, then `quit` command. Output is written to `backtrace.log` and also on the screen.

Another useful gdb invocation (giving stacktrace with local variables from all threads) is

```shell
gdb core.3599 -ex 'thread apply all bt full' -ex quit
```

> NOTE: 
>
> 我的实践: 
>
> ```shell
> sudo gdb -p 39968 -ex 'thread apply all bt full' |& tee gdb.log
> ```
>
> 



### [A](https://stackoverflow.com/a/63901492/10173843)

I had a backtrace that was so long (over 100k lines) that holding down the enter key was taking too long. I found a solution to that:

[Andreas Schneider's bt command](https://blog.cryptomilk.org/2010/12/23/gdb-backtrace-to-file/) writes a backtrace to file without any user interaction – just prefix your command with `bt `.

Here, I've turned it into a script:

```shell
#!/usr/bin/env bash
ex=(
    -ex "run"
    -ex "set logging overwrite on" 
    -ex "set logging file gdb.bt" 
    -ex "set logging on" 
    -ex "set pagination off"
    -ex "handle SIG33 pass nostop noprint"
    -ex "echo backtrace:\n"
    -ex "backtrace full"
    -ex "echo \n\nregisters:\n"
    -ex "info registers"
    -ex "echo \n\ncurrent instructions:\n"
    -ex "x/16i \$pc"
    -ex "echo \n\nthreads backtrace:\n"
    -ex "thread apply all backtrace"
    -ex "set logging off"
    -ex "quit"
)
echo 0 | gdb -batch-silent "${ex[@]}" --args "$@"
```