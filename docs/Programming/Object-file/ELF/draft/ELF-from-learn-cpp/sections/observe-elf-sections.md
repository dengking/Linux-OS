# 20180318
可以通过如下方式来观察relocatable file的section信息。程序如下:
```c
void test_a()//定义函数test_a
{
     printf("test_a");
     return;
}
```
只进行编译，不进行链接，这样就能够生成relocatable file，命令如下：
```shell
gcc -c a.c -o a.o
```
现在就可以通过readelf命令来查看这个relocatable file了，命令如下:
```shell
readelf -a a.o
```
程序的输出，即对该relocatable file的解释如下：
```shell
ELF 头：
  Magic：  7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (可重定位文件)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  入口点地址：              0x0
  程序头起点：              0 (bytes into file)
  Start of section headers:          520 (bytes into file)
  标志：             0x0
  本头的大小：       64 (字节)
  程序头大小：       0 (字节)
  Number of program headers:         0
  节头大小：         64 (字节)
  节头数量：         11
  字符串表索引节头： 8

节头：
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000007  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 3] .bss              NOBITS           0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000047
       000000000000002e  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  00000075
       0000000000000000  0000000000000000           0     0     1
  [ 6] .eh_frame         PROGBITS         0000000000000000  00000078
       0000000000000038  0000000000000000   A       0     0     8
  [ 7] .rela.eh_frame    RELA             0000000000000000  000001f0
       0000000000000018  0000000000000018   I       9     6     8
  [ 8] .shstrtab         STRTAB           0000000000000000  000000b0
       0000000000000054  0000000000000000           0     0     1
  [ 9] .symtab           SYMTAB           0000000000000000  00000108
       00000000000000d8  0000000000000018          10     8     8
  [10] .strtab           STRTAB           0000000000000000  000001e0
       000000000000000c  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

There are no section groups in this file.

本文件中没有程序头。

重定位节 '.rela.eh_frame' 位于偏移量 0x1f0 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     8: 0000000000000000     7 FUNC    GLOBAL DEFAULT    1 test_a

No version information found in this file.

```
下面结合这个输出结果和ELF官方文档进行详细的分析。
## Section Header的sh_offset成员和ELF Header的e_shoff成员
 上述输出结果来看，ELF Header的e_shoff的成员的值520，如下：
 ```shell
 Start of section headers:          520 (bytes into file)
 ```
 这表名section header table位于距离文件其实位置520字节处。

 再来开section header table的内容：
 ```shell
 节头：
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000007  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 3] .bss              NOBITS           0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000047
       000000000000002e  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  00000075
       0000000000000000  0000000000000000           0     0     1
  [ 6] .eh_frame         PROGBITS         0000000000000000  00000078
       0000000000000038  0000000000000000   A       0     0     8
  [ 7] .rela.eh_frame    RELA             0000000000000000  000001f0
       0000000000000018  0000000000000018   I       9     6     8
  [ 8] .shstrtab         STRTAB           0000000000000000  000000b0
       0000000000000054  0000000000000000           0     0     1
  [ 9] .symtab           SYMTAB           0000000000000000  00000108
       00000000000000d8  0000000000000018          10     8     8
  [10] .strtab           STRTAB           0000000000000000  000001e0
       000000000000000c  0000000000000000           0     0     1
 ```
我们看看.text section的位置，它的Offset值为ox40，翻译为十进制就是64，也就是它的位置是距离文件头64字节处。ELF header的大小是64字节，也就是.text section就紧挨着ELF header。

## Section Header的sh_size
这个字段用来描述该section的大小，还是以.text section为例，它的大小是7字节，如下:
```shell
[Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
[ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000007  0000000000000000  AX       0     0     1
```
## Section Types
下面根据section type对这些section进行分析。
### PROGBITS
类型为PROGBITS的section如下：
```shell
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000007  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 3] .bss              NOBITS           0000000000000000  00000047
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000047
       000000000000002e  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  00000075
       0000000000000000  0000000000000000           0     0     1
  [ 6] .eh_frame         PROGBITS         0000000000000000  00000078
       0000000000000038  0000000000000000   A       0     0     8
```
 可以看到.data段，.text段都是没有数据的。

 ### SYMTAB和DYNSYM
 类型为这两种的section如下：
 ```shell
   [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 9] .symtab           SYMTAB           0000000000000000  00000108
       00000000000000d8  0000000000000018          10     8     8
 ```
注意一下该section的EntSize字段，其值为0X18，ELF规范文档中对该字段的解释如下:

> Some sections hold a table of fixed-size entries, such as a symbol table. For such a section, this member gives the size in bytes of each entry. The member contains 0 if the section does not hold a table of fixed-size entries.

也就是说在.symtab中每一项的长度为0x18个字节。

该symbol table的内容如下：

 ```shell
 Symbol table '.symtab' contains 9 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     8: 0000000000000000     7 FUNC    GLOBAL DEFAULT    1 test_a
 ```
### RELA
属于该类的section如下：
```shell
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [7] .rela.eh_frame    RELA             0000000000000000  000001f0
       0000000000000018  0000000000000018   I       9     6     8
```
该section的内容如下：
```shell
重定位节 '.rela.eh_frame' 位于偏移量 0x1f0 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0
```
### STRTAB
属于该类的section如下:
```shell
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 8] .shstrtab         STRTAB           0000000000000000  000000b0
       0000000000000054  0000000000000000           0     0     1
  [10] .strtab           STRTAB           0000000000000000  000001e0
       000000000000000c  0000000000000000           0     0     1
```
## Section Attribute Flags

看了文档对这个字段的解释，感觉这个字段虽然名字比较小，比较满意存在感，但是它的作用确实很大的，它和程序的执行密切相关。它的取值如下:

```shell
W (write)
A (alloc)
X (execute)
M (merge)
S (strings)
l (large)
I (info)
L (link order)
G (group)
T (TLS)
E (exclude)
x (unknown)
O (extra OS processing required) o (OS specific)
p (processor specific)
```

