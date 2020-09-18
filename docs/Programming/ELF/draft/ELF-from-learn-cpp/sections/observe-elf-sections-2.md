# 20180318
## Special Sections
### .bss
>This section holds uninitialized data that contribute to the program's memory image. 
上面这段话在data后面加上了定语`contribute to the program's memory image`，是否是指那些全局的数据，而不是函数内部定义的临时变量呢？

>By definition, the system initializes the data with zeros when the program begins to run. The section occupies no file space, as indicated by the section type,  SHT_NOBITS 。
我比较好奇的是，既然它并不占用文件空间，那为什么还要保留这个section呢？？

### .data and  .data1
>These sections hold initialized data that contribute to the program's memory image.
还是以下面这个小程序为例来进行观察。
```
int i;
int j = 1;
int k;
void test_a()//定义函数test_a
{
     int h = 3;
     return;
}
```
进行编译，而不进行链接，命令如下：
```
gcc -c a.c -o a.o
```
然后使用readelf进行查看，输出结果如下：
```
节头：
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000000e  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000050
       0000000000000004  0000000000000000  WA       0     0     4
  [ 3] .bss              NOBITS           0000000000000000  00000054
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000054
       000000000000002e  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  00000082
       0000000000000000  0000000000000000           0     0     1
  [ 6] .eh_frame         PROGBITS         0000000000000000  00000088
       0000000000000038  0000000000000000   A       0     0     8
  [ 7] .rela.eh_frame    RELA             0000000000000000  00000250
       0000000000000018  0000000000000018   I       9     6     8
  [ 8] .shstrtab         STRTAB           0000000000000000  000000c0
       0000000000000054  0000000000000000           0     0     1
  [ 9] .symtab           SYMTAB           0000000000000000  00000118
       0000000000000120  0000000000000018          10     8     8
  [10] .strtab           STRTAB           0000000000000000  00000238
       0000000000000012  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

There are no section groups in this file.

本文件中没有程序头。

重定位节 '.rela.eh_frame' 位于偏移量 0x250 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     8: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM i
     9: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    2 j
    10: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM k
    11: 0000000000000000    14 FUNC    GLOBAL DEFAULT    1 test_a

No version information found in this file.

```
通过上面的程序可以看到，.data段的大小是4字节。现在我们修改程序，如下：
```
int i;
int j = 1;
int k = 2;
void test_a()//定义函数test_a
{
     int h = 3;
     return;
}
```
然后再进行编译，再读取这个文件，输出结果如下：
```
节头：
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000000e  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000050
       0000000000000008  0000000000000000  WA       0     0     4
  [ 3] .bss              NOBITS           0000000000000000  00000058
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000058
       000000000000002e  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  00000086
       0000000000000000  0000000000000000           0     0     1
  [ 6] .eh_frame         PROGBITS         0000000000000000  00000088
       0000000000000038  0000000000000000   A       0     0     8
  [ 7] .rela.eh_frame    RELA             0000000000000000  00000250
       0000000000000018  0000000000000018   I       9     6     8
  [ 8] .shstrtab         STRTAB           0000000000000000  000000c0
       0000000000000054  0000000000000000           0     0     1
  [ 9] .symtab           SYMTAB           0000000000000000  00000118
       0000000000000120  0000000000000018          10     8     8
  [10] .strtab           STRTAB           0000000000000000  00000238
       0000000000000012  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

There are no section groups in this file.

本文件中没有程序头。

重定位节 '.rela.eh_frame' 位于偏移量 0x250 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     8: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM i
     9: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    2 j
    10: 0000000000000004     4 OBJECT  GLOBAL DEFAULT    2 k
    11: 0000000000000000    14 FUNC    GLOBAL DEFAULT    1 test_a

No version information found in this file.
```
可以看到，现在.data段的大小是8字节。

我们再修改程序，在函数test_a中添加临时变量，并且对其进行赋值，如下：
```
int i;
int j = 1;
int k = 2;
void test_a()//定义函数test_a
{
     int h = 3;
     int l = 3;
     return;
}
```
通过readelf来看，发现.data段并没有变化。这激起了我的一个疑问，对于函数中声明的历史变量，ELF文件是否并不会进行保存？？并且上面提及的定语`contribute to the program's memory image.`应该是和这有关联的。

