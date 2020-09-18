在ELF文档中link editing 和 dynamic linking这两个词是经常看到的，他们的具体含义我目前尚且不清楚。

在介绍shared object file的时候，作者使用的是下面这段话来描述的：

>A shared object file holds code and data suitable for linking in two contexts. First, the link editor may process it with other relocatable and shared object files to create another object file.Second, the dynamic linker combines it with an executable file and other shared objects to create a process image.

 shared object file可以在两种情况下进行linking：

第一种是link editor拼接它和其他的relocatable object file和 shared object file来组成新的 shared object file。

这是gcc的最后一步，它可以翻译为链接器，通常是由ld实现的。

```shell
[dk@hundsun ~]$ whereis ld
ld: /usr/bin/ld /usr/share/man/man1/ld.1.gz
```

第二种是dynamic linker组合它和其它的executable file和 shared object file来创建一个process image

它可以翻译为动态链接器是，通常是由ld-linux.so.2 来实现的。

```shell
[dk@hundsun ~]$ whereis ld-linux.so.2 
ld-linux.so: /lib/ld-linux.so.2 /usr/share/man/man8/ld-linux.so.8.gz
```

关于ld-linux.so.2，参考下面的文章：

[ 深入理解LINUX下动态库链接器/加载器ld-linux.so.2](http://blog.csdn.net/elfprincexu/article/details/51701242)

ld-linux.so.2 是linux下的动态库加载器/链接器，这篇文章主要来讲一下 ld-linux.so.2 是如何和Linux 以及相关应用打交道的。

# 1. 什么是 ld.linux.so ? 

很多现代应用都是通过动态编译链接的，当一个 需要动态链接 的应用被操作系统加载时，系统必须要 定位 然后 加载它所需要的所有**动态库文件**。 在Linux环境下，这项工作是由ld-linux.so.2来负责完成的，我们可以通过 ldd 命令来查看一个 应用需要哪些依赖的动态库:

```
$ ldd `which ls`
      linux-gate.so.1 =>  (0xb7fff000)
      librt.so.1 => /lib/librt.so.1 (0x00b98000)
      libacl.so.1 => /lib/libacl.so.1 (0x00769000)
      libselinux.so.1 => /lib/libselinux.so.1 (0x00642000)
      libc.so.6 => /lib/libc.so.6 (0x007b2000)
      libpthread.so.0 => /lib/libpthread.so.0 (0x00920000)
      /lib/ld-linux.so.2 (0x00795000)
      libattr.so.1 => /lib/libattr.so.1 (0x00762000)
      libdl.so.2 => /lib/libdl.so.2 (0x0091a000)
      libsepol.so.1 => /lib/libsepol.so.1 (0x0065b000)
```

当最常见的ls小程序加载时，操作系统会将 **控制权** 交给 ld-linux.so 而不是 交给程序正常的进入地址。 ld-linux.so.2 会**寻找**然后**加载**所有需要的库文件，然后再将控制权交给应用的起始入口。

**上面的ls在启动时，就需要ld-linux.so加载器将所有的动态库加载后然后再将控制权移交给ls程序的入口。**

ld-linux.so.2 man page给我们更高一层的全局介绍， 它是在 链接器（通常是ld）在运行状态下的部件，用来**定位**和**加载**动态库到应用的运行地址（或者是运行内存）当中去。通常，**动态链接**是 **链接阶段**([linux下编译的步骤](https://github.com/dengking/learn-cpp/blob/master/compile-and-link-error/step-of-compile/step-of-compile-in-linux.md)当中 隐式指定的<!--在makefile文件中会指定需要链接的so-->。 gcc -W1 options -L/path/included -lxxx 会将 options 传递到ld 然后指定相应的**动态库加载**。 



ELF 文件提供了相应的加载信息， GCC包含了一个特殊的 ELF 头： INTERP， 这个 INTERP指定了 加载器的路径，我们可以用readelf 来查看相应的程序

```
$ readelf -l a.out

Elf file type is EXEC (Executable file)
Entry point 0x8048310
There are 9 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  PHDR           0x000034 0x08048034 0x08048034 0x00120 0x00120 R E 0x4
  INTERP         0x000154 0x08048154 0x08048154 0x00013 0x00013 R   0x1
      [Requesting program interpreter: /lib/ld-linux.so.2]
  LOAD           0x000000 0x08048000 0x08048000 0x004cc 0x004cc R E 0x1000
  LOAD           0x000f0c 0x08049f0c 0x08049f0c 0x0010c 0x00110 RW  0x1000
. . .
```

ELF 规格要求，假如 PT_INTERP 存在的话，操作系统必须创建这个 interpreter文件的运行映射，而不是这个程序本身， 控制权会交给这个interpreter，用来定位和加载所有的动态库，



Segment Types中确实存在PT_INTERP这种类型的segment，关于 PT_INTERP这是ELF文档中的相关介绍：

The array element specifies the location and size of a null-terminated path name to invoke as an interpreter. See Book III.



