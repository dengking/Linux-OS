# args

使用gdb调试的时候,如何传递参数的应用程序?本文对此进行总结.

## `gdb --args`

在 《Debugging with gdb》的"2 Getting In and Out of gdb"中，介绍了这种用法:

```shell
gdb --args gcc -O2 -c foo.c
```



## stackoverflow [How do I run a program with commandline arguments using GDB within a Bash script?](https://stackoverflow.com/questions/6121094/how-do-i-run-a-program-with-commandline-arguments-using-gdb-within-a-bash-script)

[A](https://stackoverflow.com/a/6121299)

You can run gdb with `--args` parameter,

```SH
gdb --args executablename arg1 arg2 arg3
```

If you want it to run automatically, place some commands in a file (e.g. 'run') and give it as argument: -x /tmp/cmds. Optionally you can run with -batch mode.

```SH
gdb -batch -x /tmp/cmds --args executablename arg1 arg2 arg3
```

[A](https://stackoverflow.com/a/29741504)

Another way to do this, which I personally find slightly more convenient and intuitive (without having to remember the `--args` parameter), is to compile normally, and use `r arg1 arg2 arg3` directly from within `gdb`, like so:

```
$ gcc -g *.c *.h
$ gdb ./a.out
(gdb) r arg1 arg2 arg3
```

## stackoverflow [How to pass arguments and redirect stdin from a file to program run in gdb?](https://stackoverflow.com/questions/4521015/how-to-pass-arguments-and-redirect-stdin-from-a-file-to-program-run-in-gdb)



[A](https://stackoverflow.com/a/4521023)

Pass the arguments to the `run` command from within gdb.

```SH
$ gdb ./a.out
(gdb) r < t
Starting program: /dir/a.out < t
```

[A](https://stackoverflow.com/a/4521576)

You can do this:

```shell
gdb --args path/to/executable -every -arg you can=think < of
```

The magic bit being `--args`.

Just type `run` in the gdb command console to start debugging.