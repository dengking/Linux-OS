#Relocation

Relocation is the process of connecting symbolic references with symbolic definitions. For
example, when a program calls a function, the associated call instruction must transfer control
to the proper destination address at execution. In other words, relocatable files must have
information that describes how to modify their section contents, thus allowing executable and
shared object files to hold the right information for a process's program image. Relocation
entries are these data.

Relocation是联系symbolic references（引用）和 symbolic definitions（定义）的过程。例如，当一个程序在运行时调用一个函数时，这个调用指令必须把控制传输到这个函数的定义位置，也就是目的地址。换句话说，relocatable文件必须要包含如何修改其section 内容的消息，这样executable file和shared object file才能够包含正确的消息，这样程序才能够运行起来。

我们以汇编语言来看这个问题，调用一个函数使用汇编来描述就是：

```assembly
mov 函数地址
```



而刚开始，在relocatable file中，调用函数，使用的仍然是这个函数的symbolic reference。

下面介绍了Relocation Entries的结构定义：

```c
typedef struct {
Elf32_Addr r_offset;
Elf32_Word r_info;
} Elf32_Rel;
typedef struct {
Elf32_Addr r_offset;
Elf32_Word r_info;
Elf32_Sword r_addend;
} Elf32_Rela;
```

r_offset

This member gives the location at which to apply the relocation action. For a relocatable file, the value is the byte offset from the beginning of the section to the storage unit affected by the relocation. For an executable file or a shared object, the value is the virtual address of the storage unit affected by the relocation.

这个成员变量指定了这个relocation动作执行的位置。对于relocatable file，这个值是从受relocation影响的section的开始位置起的字节偏移量；对于executable file和shared object，这个值是受relocation影响的存储单元的virtual address。

r_info 

This member gives both the symbol table index with respect to which the relocation must be made, and the type of relocation to apply. For example, a call instruction's relocation entry would hold the symbol table index of the function being called. If the index is  STN_UNDEF , the undefined symbol
index, the relocation uses 0 as the "symbol value.'' Relocation types are processor-specific; descriptions of their behavior appear in the processor supplement. When the text in the processor supplement refers to a relocation entry's relocation type or symbol table index, it means the result
of applying  ELF32_R_TYPE or ELF32_R_SYM , respectively, to the entry's  r_info member.

我们是需要对symbol进行重定位，因此这个成员指定了执行重定位的symbol在symbol table中的index和type of relocation（重定位类型）。例如，一个函数调用指令的relocation entry（重定位项）会指定被调函数在symbol table中的index。

Relocation type是处理器相关的，通过调用如下两个函数来从r_info中解析出index和relocation type。

```c
#define ELF32_R_SYM(i) ((i)>>8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))
```

r_addend 

This member specifies a constant addend used to compute the value to be stored into the relocatable field

Q&A

1. 解释器如何得知哪些section是需要进行relocation的？

   |     sh_type      |                 sh_link                  |                 sh_info                  |
   | :--------------: | :--------------------------------------: | :--------------------------------------: |
   | SHT_REL和SHT_RELA | 保存的是相关联的symbol table在section header table中的索引 | 这个字段的含义是relocation将在哪个section上执行，这个字段保存的是目标section在section header table中的索引 |

2. 编译器是否会为每个需要重定位的section都生成一个对应的relocation table？？

