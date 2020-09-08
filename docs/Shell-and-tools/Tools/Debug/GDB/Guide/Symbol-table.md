# Symbol table

在工程compiler-principle的`Chapter-2-A-Simple-Syntax-Directed-Translator\2.7-Symbol-Tables`中介绍了symbol table，其中提及了：

> debug阶段：在debug的时候，只有读取了symbol table了，才能够灵活地设置。

一个典型的例子是：

在debug dynamic library的时候，如果对应的dynamic library没有load，则无法dynamic library的实现中的symbol进行break。

## symbol table的重要价值

在工程compiler-principle的`Chapter-2-A-Simple-Syntax-Directed-Translator\2.7-Symbol-Tables`中已经介绍了symbol table的重要价值，现在结合`gdb`再次来进行说明：

- gdb中关于source code的命令，基本上是基于symbol table实现的，比如`info function`

## gdb onlinedocs [16 Examining the Symbol Table](https://sourceware.org/gdb/onlinedocs/gdb/Symbols.html#Symbols)



## `struct` 

- [How do I show what fields a struct has in GDB?](https://stackoverflow.com/questions/1768620/how-do-i-show-what-fields-a-struct-has-in-gdb)





## `add-symbol-file` command

这个命令有时是非常有用的。

### gdb onlinedocs [18.1 Commands to Specify Files](https://sourceware.org/gdb/onlinedocs/gdb/Files.html#Files)



### thegeekstuff [Load Shared library Symbols](https://www.thegeekstuff.com/2014/03/few-gdb-commands/)

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

```shell
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

From the above information, note that the library libglib-2.0.so.0 is having symbols, but the debuuging information like `file_name`, `line_no` etc… are missing.

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