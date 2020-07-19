# GDB Command Reference

以visualgdb [GDB Command Reference](https://visualgdb.com/gdbreference/commands/)、cnblogs [gdb命令调试技巧](https://www.cnblogs.com/Forever-Kenlen-Ja/p/8631663.html)为蓝本进行总结。



## [Shared library commands](https://visualgdb.com/gdbreference/commands/shared_library_commands)

| command                                                      | 简介                                 |
| ------------------------------------------------------------ | ------------------------------------ |
| [info sharedlibrary](https://visualgdb.com/gdbreference/commands/info_sharedlibrary) |                                      |
| [set auto-solib-add](https://visualgdb.com/gdbreference/commands/set_auto-solib-add) | gdb break when a shared library load |
| [set solib-search-path](https://visualgdb.com/gdbreference/commands/set_solib-search-path) |                                      |
| [set stop-on-solib-events](https://visualgdb.com/gdbreference/commands/set_stop-on-solib-events) |                                      |
| [set sysroot](https://visualgdb.com/gdbreference/commands/set_sysroot) |                                      |
| [sharedlibrary](https://visualgdb.com/gdbreference/commands/sharedlibrary) |                                      |

### Pending break

> It's quite common to have a breakpoint inside a shared library. Shared libraries can be loaded and unloaded explicitly, and possibly repeatedly, as the program is executed. To support this use case, gdb updates breakpoint locations whenever any shared library is loaded or unloaded. Typically, you would set a breakpoint in a shared library at the beginning of your debugging session, when the library is not loaded, and when the symbols from the library are not available. When you try to set breakpoint, gdb will ask you if you want to set a so called pending breakpoint—breakpoint whose address is not yet resolved.

quote from https://sourceware.org/gdb/onlinedocs/gdb/Set-Breaks.html



### [How to set regex breakpoint for shared library in GDB](https://codeyarns.com/2017/08/22/how-to-set-regex-breakpoint-for-shared-library-in-gdb/)

> - I find it useful to configure GDB to stop whenever a shared library is loaded. This can be done by setting this option: `set stop-on-solib-events 1`
> - Now GDB stops every time at the point where one or more shared libraries need to be loaded. If I realize that the shared library I am interested in has now loaded, I run the regex breakpoint command at that point to set the breakpoints. Voila!



### [Load Shared library Symbols](https://www.thegeekstuff.com/2014/03/few-gdb-commands/)

Many a times, programmers will use shared libraries in their code. Sometimes, we might want to look into the shared library itself to understand what’s going on. Here I’ll show an example using GLib Library and how to obtains the debugging information for it.

By default, all distributions will strip the libraries to some extent. The complete debugging information will be stored in a separate package which they name like “package-1.0-dbg”, and only if needed user can install.

When you install the “package-1.0-dbg”, by default gdb will load all the debugging information, but to understand the concept here we will see how to manually load the symbol file.

```c
#include <stdio.h>
#include <glib.h>
struct a {
        int a;
        int b;
};
void *print( struct a *obj,int as) {
        printf("%d:%d\n",obj->a,obj->b);
}
int main() {
        struct a *obj;
        obj = (struct a*)malloc(sizeof(struct a));
        obj->a=3;
        obj->b=4;
        GList *list=NULL;
        list = g_list_append(list,obj);
        g_list_foreach(list,(GFunc)print,NULL);
}
```



```shell
$ cc  -g -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/  -lglib-2.0 glib_test.c
```

Note: You need to install the libglib2.0-0 to try out this example.

Now we will start the debugging.

```
(gdb) b 1
Breakpoint 1 at 0x4007db: file a.c, line 1.
(gdb) run
...
(gdb) info sharedlibrary 
From                To                  Syms Read   Shared Object Library
0x00007ffff7dddaf0  0x00007ffff7df5c83  Yes (*)     /lib64/ld-linux-x86-64.so.2
0x00007ffff7b016c0  0x00007ffff7b6e5cc  Yes (*)     /lib/x86_64-linux-gnu/libglib-2.0.so.0
0x00007ffff7779b80  0x00007ffff7890bcc  Yes (*)     /lib/x86_64-linux-gnu/libc.so.6
0x00007ffff751f9a0  0x00007ffff7546158  Yes (*)     /lib/x86_64-linux-gnu/libpcre.so.3
0x00007ffff7307690  0x00007ffff7312c78  Yes (*)     /lib/x86_64-linux-gnu/libpthread.so.0
0x00007ffff70fc190  0x00007ffff70ff4f8  Yes (*)     /lib/x86_64-linux-gnu/librt.so.1
(*): Shared library is missing debugging information.
```

From the above information, note that the library libglib-2.0.so.0 is having symbols, but the debuuging information like file_name, line_no etc… are missing.

Download the debug information for the package from respective distribution (libglib2.0-0-dbg in Debian – Wheezy).

```
(gdb) add-symbol-file /home/lakshmanan/libglib-2.0.so.0.3200.4 0x00007ffff7b016c0
add symbol table from file "/home/lakshmanan/libglib-2.0.so.0.3200.4" at
	.text_addr = 0x7ffff7b016c0
(y or n) y
Reading symbols from /home/lakshmanan/libglib-2.0.so.0.3200.4...done.
```

The address given in the `add-symbol-file` command is, the “From” address printed by “`info sharedlibrary`” command. Now the debugging information is loaded.

```
...
...
(gdb) n
g_list_foreach (list=0x0, func=0x4007cc , user_data=0x0) at /tmp/buildd/glib2.0-2.33.12+really2.32.4/./glib/glist.c:897
```



Sometimes the shared libraries won’t even have any symbols in it, and in those situations, the above method will be helpful.

### TO READ

https://sysprogs.com/w/resolving-library-symbol-load-errors-when-debugging-with-cross-toolchains/



## Function

### List function name

列出函数的名字`(gdb) info functions`
2、是否进入待调试信息的函数(gdb)step s
3、进入不带调试信息的函数(gdb)set step-mode on
4、退出正在调试的函数(gdb)return expression 或者 (gdb)finish
5、直接执行函数(gdb)start 函数名 call函数名
6、打印函数堆栈帧信息(gdb)info frame or i frame
7、查看函数寄存器信息(gdb)i registers
8、查看函数反汇编代码(gdb)disassemble func
9、打印尾调用堆栈帧信息(gdb)set debug entry-values 1
10、选择函数堆栈帧(gdb)frame n
11、向上或向下切换函数堆栈帧(gdb)up n down n

### OOP

#### Breakpoint for member functions

[breakpoint for member functions](https://stackoverflow.com/questions/35806129/c-gdb-breakpoint-for-member-functions)

```C++
class BST
{
    BST()
    ...
    private:
    int add((BST * root, BST *src);
}
```

[A](https://stackoverflow.com/a/35809049)

As Dark Falcon said, `break BST::add` should work if you don't have overloads.

You can also type:

```cpp
(gdb) break 'BST::add(<TAB>
```

(note the single quote). This should prompt GDB to perform tab-completion, and finish the line like so:

```cpp
(gdb) break 'BST::add(BST*, BST*)
```

and which point you can add the terminating `'`' and hit Enter to add the breakpoint.

> I can get a break point for the void display function

Function return type is not part of its signature and has *nothing* to do with what's happening.

