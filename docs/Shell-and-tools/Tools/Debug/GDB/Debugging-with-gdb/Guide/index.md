# 关于本章

gdb的用户手册[Debugging with GDB](https://sourceware.org/gdb/onlinedocs/gdb/index.html)中的内容是非常完备，但是庞杂，为了更好地掌握其中的内容，本章对Debugging with gdb中的内容进行: 

- 梳理，从更高的角度对原文中的内容进行总结
- 专题讨论

另外本章还参考了：

- visualgdb [GDB Command Reference](https://visualgdb.com/gdbreference/commands/)
- cnblogs [gdb命令调试技巧](https://www.cnblogs.com/Forever-Kenlen-Ja/p/8631663.html)



## [Debugging with GDB](https://sourceware.org/gdb/onlinedocs/gdb/index.html) 内容概述

[Debugging with GDB](https://sourceware.org/gdb/onlinedocs/gdb/index.html)中的内容是非常庞杂的，因此对书中内容建立一个高屋建瓴的视角是非常有必要的。本节采取的是“基于特性”进行概括的思路。

### Control process

在`Shell-and-tools\Tools\Debug\GDB\Debugging-with-gdb\Guide\Guide-to-controlling-process.md`中对此进行了讨论。

### Examine data

本节标题的含义是：查看数据，它是gdb的一个非常重要的特性。下面是涉及这个主题的章节：

- [8 Examining the Stack](https://sourceware.org/gdb/onlinedocs/gdb/Stack.html#Stack)
- [9 Examining Source Files](https://sourceware.org/gdb/onlinedocs/gdb/Source.html#Source)
- [10 Examining Data](https://sourceware.org/gdb/onlinedocs/gdb/Data.html#Data)
- [16 Examining the Symbol Table](https://sourceware.org/gdb/onlinedocs/gdb/Symbols.html#Symbols)