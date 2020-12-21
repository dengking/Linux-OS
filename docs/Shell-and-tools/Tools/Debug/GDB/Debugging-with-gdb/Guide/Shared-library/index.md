# Shared library

本文描述gdb调试shared library的内容。

## Set breakpoint in shared library

Linux OS是支持多种使用shared library的方式的，无论是哪种方式，调试shared library的一个原则是:

> 只有当shared library被加载后，才能够读取其中的symbol，然后才能够对其进行调试。

stackoverflow [how to set breakpoint on function in a shared library which has not been loaded in gdb](https://stackoverflow.com/questions/2642983/how-to-set-breakpoint-on-function-in-a-shared-library-which-has-not-been-loaded): 

> Actually gdb should tell you that it's able to resolve the symbol in the future, when new libraries are loaded



## visualgdb [Shared library commands](https://visualgdb.com/gdbreference/commands/shared_library_commands)

> NOTE: 对shared library相关的command进行了较好的总结

| command                                                      | 简介                                 |
| ------------------------------------------------------------ | ------------------------------------ |
| [info sharedlibrary](https://visualgdb.com/gdbreference/commands/info_sharedlibrary) | 查看已经加载的shared library         |
| [set auto-solib-add](https://visualgdb.com/gdbreference/commands/set_auto-solib-add) | gdb break when a shared library load |
| [set solib-search-path](https://visualgdb.com/gdbreference/commands/set_solib-search-path) |                                      |
| [set stop-on-solib-events](https://visualgdb.com/gdbreference/commands/set_stop-on-solib-events) |                                      |
| [set sysroot](https://visualgdb.com/gdbreference/commands/set_sysroot) |                                      |
| [sharedlibrary](https://visualgdb.com/gdbreference/commands/sharedlibrary) |                                      |



## `set stop-on-solib-events` command



### visualgdb [set stop-on-solib-events](https://visualgdb.com/gdbreference/commands/set_stop-on-solib-events)

#### Syntax

```
set stop-on-solib-events 0
set stop-on-solib-events 1
show stop-on-solib-events
```

> NOTE: `set stop-on-solib-events 1` 对于通过`dlopen`来加载的shared library非常有用。

### codeyarns [How to set regex breakpoint for shared library in GDB](https://codeyarns.com/2017/08/22/how-to-set-regex-breakpoint-for-shared-library-in-gdb/)

- I find it useful to configure GDB to stop whenever a shared library is loaded. This can be done by setting this option: `set stop-on-solib-events 1`
- Now GDB stops every time at the point where one or more shared libraries need to be loaded. If I realize that the shared library I am interested in has now loaded, I run the regex breakpoint command at that point to set the breakpoints. Voila!





## Run-time load

本节标题的函数是“运行时加载”。dynamic library是run-time才会继续加载的，所以在程序运行之前，无法获取dynamic library的信息，这是因为此时gdb还没有加载dynamic library，所以没有读取其symbol table，所以无法获得dynamic library的实现的信息。

只有当程序开始运行后，才能够对dynamic library进行debug。

因此，在调试dynamic library的时候，我们一般使用下面的策略:

```shell
$ gdb a.out
(gdb) b main
Breakpoint 1 at 0x401a90: file main.cpp, line 17.
(gdb) r
Starting program:a.out
Breakpoint 1, main () at main.cpp:17
(gdb)info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007ffff7ddbad0  0x00007ffff7df7080  Yes (*)     /lib64/ld-linux-x86-64.so.2
0x00007ffff758e220  0x00007ffff75f537a  Yes (*)     /lib64/libstdc++.so.6
0x00007ffff7236310  0x00007ffff72a12d6  Yes (*)     /lib64/libm.so.6
0x00007ffff701da90  0x00007ffff702d245  Yes (*)     /lib64/libgcc_s.so.1
0x00007ffff6c6d8d0  0x00007ffff6dbd22f  Yes (*)     /lib64/libc.so.6
0x00007ffff6a378b0  0x00007ffff6a42e01  Yes (*)     /lib64/libpthread.so.0
0x00007ffff61d7f80  0x00007ffff61e56c3  Yes (*)     /lib64/libnsl.so.1
0x00007ffff5fd0d90  0x00007ffff5fd188e  Yes (*)     /lib64/libdl.so.2
0x00007ffff5dca1e0  0x00007ffff5dcd16c  Yes (*)     /lib64/librt.so.1
(*): Shared library is missing debugging information.
```

至此，dynamic library就已经装载了，此时可以对其进行调试。



## Load, unload and reload shared library 

### aixxe [Loading, unloading & reloading shared libraries](https://aixxe.net/2016/09/shared-library-injection)

Using dynamic linker functions to load, unload and reload our code into a process.

### stackoverflow [make gdb load a shared library from a specific path](https://stackoverflow.com/questions/33886913/make-gdb-load-a-shared-library-from-a-specific-path)



### Directly load shared library

gdb能够直接load shared library，即使没有可执行程序，这个特性是有一定价值的，我们可以可以直接读取shared library中的一些信息。



## TO READ

https://sysprogs.com/w/resolving-library-symbol-load-errors-when-debugging-with-cross-toolchains/

