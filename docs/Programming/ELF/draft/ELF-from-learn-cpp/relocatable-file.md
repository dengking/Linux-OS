# [可重定位文件](https://blog.csdn.net/ylcangel/article/details/18188921)

本文使用的示例代码如下：

程序代码如下：

a.c

```c
int sum(int a,int b)
{
    return a+b;
}
```

b.c

```c
int mul(int a,int b)
{
    return a*b;
}
```

main.c

```c
#include<stdio.h>
int a=12;
int main()
{
    int b=12;
    printf("a+b=%d\n", sum(a,b));
    printf("a*b=%d\n", mul(a,b));
    return 0;
}
```



## 可重定位目标



**重定位**是将EFL文件中的**未定义符号**（包括函数和变量）关联到**有效值**的处理过程。在`main.o`中，这意味着对`printf`和`puts`的未定义的引用必须替换为该**进程的虚拟地址空间**中适当的**机器代码**所在的**地址**。在目标中用到的相关**符号**之处，都必须替换。

对*用户空间*  **程序符号**的替换，**内核**并不涉及其中，因为所有的替换操作都是由**外部工具**完成的。对内核模块来说，情况有所不同，因为内核所收到的**模块裸数据**，与其存储在二进制文件中的形式完全相同，内核本身需要负责重定位操作。

在每个**目标文件**中，都有一个专门的表，包含了**重定位项**，标识了需要进行重定位的。每个**表项**都包含下列信息：

​         1）一个**偏移量**，指定了修改的项的位置

​         2）对**符号**的**引用**（符号表的**索引**），提供了需要插入到**重定位位置**的数据

## 重定位步骤

​         1）重定位<!--此处的重定位是动词-->节(section)和符号定义。

​         **链接器**将所有**相同类型的节**合并为同一类型的新的**聚合节**。例如来自输入模块的`.data`节全部合并成一个节，这个节成为输出可执行目标文件的`.data`节。然后**链接器**将运行时**存储器地址**赋给新的**聚合节**，赋给输入模块定义的每个节，以及赋给输入模块定义的每个**符号**。当这一步完成时，程序中的每个**指令**和**全局变量**都有唯一的**运行时存储器地址**了。

​         2）重定位<!--此处的重定位是动词-->节(section)中的符号引用。

​         在这一步中，链接器修改**代码节**和**数据节**中对每个**符号**的**引用**，使得他们指向**正确的运行时地址**。为了执行这一步，链接器依赖于称之为**重定位条目**的可重定位目标模块中的数据结构。

> 对上面这段文字中提到的“**符号**的**引用**”的最好了解是main.c中调用了定义在a.c中的sum函数。

## 重定向条目

当**汇编器**生成一个**目标模块**时，它并不知道**数据**和**代码**最终将存放在**存储器**中的什么位置。它也不知道这个模块引用的任何外部定义的**函数**和**全局变量**。所以，无论何时**汇编器**遇到对最终位置未指定**目标引用，它就会生成一个**重定位条目**，告诉**链接器**在将**目标文件**合并**可执行文件**时如何修改这个**引用**。**代码重定位条目**放在.rel.text（**SHT_REL类型**的节（section））中。**已经初始化数据的重定位条目**放在.rel.data(**SHT_REL类型的节（section）)中。

### 数据结构

​         由于技术原因，有两种类型的重定位信息，由两种稍有不同的数据结构表示。第一种类型称之为**普通重定位**。`SHT_REL`类型的节（section）中的**重定位项**由以下数据结构定义：

```       c
/*Relocation table entry without addend (in section of type SHT_REL).  */
typedef struct
{

 Elf32_Addr   r_offset;/* Address 指定需要重定位的项的位置*/
 Elf32_Word  r_info;/* Relocation type and symbol index 提供了符号表中的一个位置，同时还包括重定位类型的有个信息。这是通过将值划分为两部分来达到的。该字段的结构如下：
        r_info == int symbol:24,type:8;*/

} Elf32_Rel;

```
另一种类型，称之为需要添加常数的**重定位项**，只出现在`SHT_RELA`类型的节中。数据结构如下：

```c
/* Relocation table entry with addend (insection of type SHT_RELA).  */
typedef struct
{
 Elf32_Addr   r_offset;            /* Address */
 Elf32_Word  r_info;                         /* Relocation type and symbol index */
 Elf32_Sword         r_addend;                  /* Addend 加数，计算重定位是，将根据重定位类型，对该值进行不同的处理。*/

} Elf32_Rela;
```

### 重定位类型

​         `ELF`定义了很多重定位类型，对每种支持的体系结构，都有一个独立的集合。这些类型大部分用于生成**动态**或**与装载位置无关的代码**。在一些平台上，特别是`IA32`平台，还必须弥补许多设计错误和历史包袱。幸运的是，Linux内核只对模块的**重定位**感兴趣，因此用以下两种重定位类型就可以了：

1）相对重定位

2）绝对重定位

**相对重定位**生成的**重定位表项**指向相对于**程序计数器**（`pc`，亦即指令指针）指定的**内存地址**，即**相对重定位**是相对于**程序计数器**进行**重定位**。这些主要用于**子例程**调用。另一种**重定位**生成**绝对地址**，从名字就能看出。通常，这种重定位项指向内存中在编译时就已知的数据，例如**字符串常数**。

在`IA32`<!--IA-32为Intel Architecture 32bit简称-->系统上，和两种重定位类型由常数`R_386_PC_32`(相对重定位)和`R_386_32`(绝对重定位)表示。重定位结果计算如下：

```c
R_386_32:Result= S+A
R_386_PC_32:Result=S-P+A
```

`A`代表`加数值`，在`IA32`体系结构上，由重定位位置处的内存内容隐式提供(一般为**操作码**后面的数值)。`S`是**符号表**中保存的符号的值，而`P`代表重定位的**位置偏移量**，换言之，即算出的数据写入到二进制文件中的**位置偏移量**(修改处的运行时地址或者偏移，对于**目标文件**`P`为修订处**段**内的偏移，对**可执行文件**P为**运行时的地址**)。如果加数值为0，那么**绝对重定位**只是将**符号表**中的符号的值插入在**重定位位置**。但在**相对重定位**中，需要计算**符号位置**和**重定位位置**之间的差值。换言之，需要通过计算确定符号与重定位位置相距多少字节。

在这两种情况下，都会加上加数值，因而使得结果产生一个**线性位移**。

首先我们明确的是**重定向**发生在**链接**的时候，当多个输入最终链接成一个**目标文件**的时候，当**符号**解析完成之后。

在此例子中，`a.c`和`b.c`没有外部引用，所以在`.o`文件中不存在重定位表项，只有`main.o`存在，如图：

查看`main.o`的重定位表：

```shell
[dk@dk rel]$ readelf -r main.o
重定位节 '.rela.text' 位于偏移量 0x300 含有 8 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000011  000900000002 R_X86_64_PC32     0000000000000000 a - 4
000000000022  000b00000002 R_X86_64_PC32     0000000000000000 sum - 4
000000000029  00050000000a R_X86_64_32       0000000000000000 .rodata + 0
000000000033  000c00000002 R_X86_64_PC32     0000000000000000 printf - 4
000000000039  000900000002 R_X86_64_PC32     0000000000000000 a - 4
00000000004a  000d00000002 R_X86_64_PC32     0000000000000000 mul - 4
000000000051  00050000000a R_X86_64_32       0000000000000000 .rodata + 8
00000000005b  000c00000002 R_X86_64_PC32     0000000000000000 printf - 4

重定位节 '.rela.eh_frame' 位于偏移量 0x3c0 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0
```

查看`main.o`的符号表：

```shell
[dk@dk rel]$ readelf -s main.o 

Symbol table '.symtab' contains 14 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     9: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 a
    10: 0000000000000000   102 FUNC    GLOBAL DEFAULT    1 main
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND sum
    12: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
    13: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND mul

```



从`main.c`源文件也不难看出，它引用了外面`sum`和`mul`符号，并且引用了一个全局`a`符号。并且从上图也可以看出。并且a的**重定位类型**为**相对重定位**。

并且可以得到：

a第一处`r_offset` ：` 0x11` 重定位的字节处 并且从第二幅图可以得知`a`的大小为4个字节

a第二处`r_offset `：    ` 0x3f`

`sumr_offset`    ：    ` 0x29`

`mulr_offset` ：      `0x4e`



计算`a`的重定位后的地址：根据公式`S+A`

`S`为**目标文件符号表**中的对应的地址（为什么不是`.o`文件呢，因为`.o`文件的符号表中的地址都是重定位REL类型，都为0）：

查看`main`的符号表，其中需要注意的是全局变量`a`的值，因为下面将以a为例来说明**重定位**过程，从输出结果可以看出，变量`a`的值为`OX601034`

```shell
[dk@dk rel]$ readelf -s main|grep a
Symbol table '.dynsym' contains 4 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
Symbol table '.symtab' contains 70 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    17: 00000000004006a8     0 SECTION LOCAL  DEFAULT   17 
    30: 00000000004004a0     0 FUNC    LOCAL  DEFAULT   13 register_tm_clones
    31: 00000000004004e0     0 FUNC    LOCAL  DEFAULT   13 __do_global_dtors_aux
    33: 0000000000600e18     0 OBJECT  LOCAL  DEFAULT   19 __do_global_dtors_aux_fin
    34: 0000000000400500     0 FUNC    LOCAL  DEFAULT   13 frame_dummy
    35: 0000000000600e10     0 OBJECT  LOCAL  DEFAULT   18 __frame_dummy_init_array_
    36: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
    38: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS main.c
    43: 0000000000600e18     0 NOTYPE  LOCAL  DEFAULT   18 __init_array_end
    45: 0000000000600e10     0 NOTYPE  LOCAL  DEFAULT   18 __init_array_start
    48: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
    49: 0000000000601030     0 NOTYPE  WEAK   DEFAULT   24 data_start
    50: 0000000000601038     0 NOTYPE  GLOBAL DEFAULT   24 _edata
    53: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_
    54: 0000000000601030     0 NOTYPE  GLOBAL DEFAULT   24 __data_start
    55: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    56: 0000000000400648     0 OBJECT  GLOBAL HIDDEN    15 __dso_handle
    61: 0000000000400440     0 FUNC    GLOBAL DEFAULT   13 _start
    62: 0000000000601034     4 OBJECT  GLOBAL DEFAULT   24 a
    63: 0000000000601038     0 NOTYPE  GLOBAL DEFAULT   25 __bss_start
    64: 0000000000400554   102 FUNC    GLOBAL DEFAULT   13 main
    66: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _Jv_RegisterClasses
    68: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable

```

可以得到 `S(a) =0x601034`，接下来要确定加值A，这要看`main.o `的汇编代码了，利用`objdump`来查看该.text节的汇编代码：

```assembly
[dk@dk rel]$ objdump -d main.o 

main.o：     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 10          	sub    $0x10,%rsp
   8:	c7 45 fc 0c 00 00 00 	movl   $0xc,-0x4(%rbp)
   f:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 15 <main+0x15>
  15:	8b 55 fc             	mov    -0x4(%rbp),%edx
  18:	89 d6                	mov    %edx,%esi
  1a:	89 c7                	mov    %eax,%edi
  1c:	b8 00 00 00 00       	mov    $0x0,%eax
  21:	e8 00 00 00 00       	callq  26 <main+0x26>
  26:	89 c6                	mov    %eax,%esi
  28:	bf 00 00 00 00       	mov    $0x0,%edi
  2d:	b8 00 00 00 00       	mov    $0x0,%eax
  32:	e8 00 00 00 00       	callq  37 <main+0x37>
  37:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 3d <main+0x3d>
  3d:	8b 55 fc             	mov    -0x4(%rbp),%edx
  40:	89 d6                	mov    %edx,%esi
  42:	89 c7                	mov    %eax,%edi
  44:	b8 00 00 00 00       	mov    $0x0,%eax
  49:	e8 00 00 00 00       	callq  4e <main+0x4e>
  4e:	89 c6                	mov    %eax,%esi
  50:	bf 00 00 00 00       	mov    $0x0,%edi
  55:	b8 00 00 00 00       	mov    $0x0,%eax
  5a:	e8 00 00 00 00       	callq  5f <main+0x5f>
  5f:	b8 00 00 00 00       	mov    $0x0,%eax
  64:	c9                   	leaveq 
  65:	c3                   	retq 
```

这样来读这些代码：

1）左边两栏中最左面一栏是上面所有**机器指令**的字节数（16进制），紧接着其后的是**机器代码**（十六进制形式）。其实真正的二进制代码是这样的（十六进制），前两行`8d 4c 24 04 83 e4 f0`，工具为了方便阅读。

我在工具的基础上为了方便说明这两栏，只提取了前面两栏（好比一个大的字节数组从零开始）。

```shell
 0:   8d 4c 24 04  以前是0个字节，下标是从0开始，其中8d是操作码

 4:   83 e4 f0    上面一共四个字节，此行小标也是从4开始，83是操作码
```

 2）最后一栏是汇编指令

```assembly
    lea    0x4(%esp),%ecx

    and   $0xfffffff0,%esp
```

在上面`objdump -d main.o `中，我们看第`0x11`字节开始的四个字节的内容皆为0。则根据公式`R_386_PC_32:Result=S-P+A`，也就是**目标文件**的`11`后面的后4个字节要被替换为该值。

> 此处是如何计算出重定向值的呢？？

下面是查看`main`中main函数的汇编代码：

```shell
[dk@dk rel]$ objdump -d main >> assemb
```

输出结果如下：

```assembly
0000000000400554 <main>:
  400554:	55                   	push   %rbp
  400555:	48 89 e5             	mov    %rsp,%rbp
  400558:	48 83 ec 10          	sub    $0x10,%rsp
  40055c:	c7 45 fc 0c 00 00 00 	movl   $0xc,-0x4(%rbp)
  400563:	8b 05 cb 0a 20 00    	mov    0x200acb(%rip),%eax        # 601034 <a>
  400569:	8b 55 fc             	mov    -0x4(%rbp),%edx
  40056c:	89 d6                	mov    %edx,%esi
  40056e:	89 c7                	mov    %eax,%edi
  400570:	b8 00 00 00 00       	mov    $0x0,%eax
  400575:	e8 b3 ff ff ff       	callq  40052d <sum>
  40057a:	89 c6                	mov    %eax,%esi
  40057c:	bf 50 06 40 00       	mov    $0x400650,%edi
  400581:	b8 00 00 00 00       	mov    $0x0,%eax
  400586:	e8 85 fe ff ff       	callq  400410 <printf@plt>
  40058b:	8b 05 a3 0a 20 00    	mov    0x200aa3(%rip),%eax        # 601034 <a>
  400591:	8b 55 fc             	mov    -0x4(%rbp),%edx
  400594:	89 d6                	mov    %edx,%esi
  400596:	89 c7                	mov    %eax,%edi
  400598:	b8 00 00 00 00       	mov    $0x0,%eax
  40059d:	e8 9f ff ff ff       	callq  400541 <mul>
  4005a2:	89 c6                	mov    %eax,%esi
  4005a4:	bf 58 06 40 00       	mov    $0x400658,%edi
  4005a9:	b8 00 00 00 00       	mov    $0x0,%eax
  4005ae:	e8 5d fe ff ff       	callq  400410 <printf@plt>
  4005b3:	b8 00 00 00 00       	mov    $0x0,%eax
  4005b8:	c9                   	leaveq 
  4005b9:	c3                   	retq   
  4005ba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
```

从上面结果可以看出，在进行重定向的位置，`objdump`程序已经进行了标注。



