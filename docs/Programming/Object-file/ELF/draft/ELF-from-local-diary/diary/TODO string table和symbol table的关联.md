在Section Types中有如下两种类型引起了我的注意：

1. SHT_SYMTAB 和SHT_DYNSYM
2. SHT_STRTAB

在ELF文档中对这两种类型是这样解释的：

1. SHT_SYMTAB and SHT_DYNSYM

   These sections hold a symbol table.即这两种类型的section保存的是symbol table

2. SHT_STRTAB

   The section holds a string table.

联系到我之前在阅读section header的时候，发现section header的结构中有如下成员变量：

sh_entsize 

Some sections hold a table of fixed-size entries, such as a **symbol table**. For such a section, this member gives the size in bytes of each entry. The member contains 0 if the section does not hold a table of fixed-size entries.

显然，对于上面两种类型的section，他们都是包含table的，所以他们的section header的sh_entsize成员就必须有值。

关于这两者，我有如下疑问：

1. 它们分别存放上面内容
2. 它们存放的内容是否有关联



#string table

ELF中不止一个string table，有.strtab，.shstrtab 

.strtab 

This section holds strings, most commonly the strings that represent the names associated with symbol table entries. If a file has a loadable segment that includes the symbol string table, the section's attributes will include the SHF_ALLOC bit; otherwise, that bit will be off.

和string table有关的成员变量有：

1. section header的sh_name成员变量的值就是 string table section的索引
2. ELF header的e_shstrndx成员变量也是string table section的索引
3. Symbol Table Entry的st_name成员变量是 symbol string table的索引

#symtab 

.symtab 

This section holds a symbol table, as "Symbol Table'' in this chapter describes. If a file has a loadable segment that includes the symbol table,the section's attributes will include the SHF_ALLOC bit; otherwise, that bit will be off.

## Symbol Table Entry

```c
typedef struct {
Elf32_Word st_name;
Elf32_Addr st_value;
Elf32_Word st_size;
unsigned char st_info;
unsigned char st_other;
Elf32_Half st_shndx;
} Elf32_Sym;
```

###st_name 

This member holds an index into the object file's symbol string table, which holds the character representations of the symbol names.

### st_value

This member gives the value of the associated symbol. Depending on the context,this may be an absolute value, an address, and so on; details appear below.

st_value到底保存的是symbol的什么内容？是地址还是值？symbol的值是否保存在data section中？？

在ELF文档的Symbol Values章节介绍了这部分内容，是地址。

###st_size

Many symbols have associated sizes. For example, a data object's size is the number of bytes contained in the object. This member holds 0 if the symbol has no size or an unknown size.

为什么symbol要保存size？？

### st_shndx

Every symbol table entry is "defined'' in relation to some section; this member holds the relevant section header table index. As Figure 1-7 and the related text describe,some section indexes indicate special meanings.

有的symbol是相对于某个section定义的，Elf32_Sym的st_shndx成员就表明该symbol所参照的section。

### st_info 

This member specifies the symbol's type and binding attributes. A list of the values and meanings appears below. The following code shows how to manipulate the values.

这里提到了每个符号的两个重要属性：

1. type
2. binding

#### Symbol Binding,  ELF32_ST_BIND

|    Name    | Value |
| :--------: | :---: |
| STB_LOCAL  |   0   |
| STB_GLOBAL |   1   |
|  STB_WEAK  |   2   |
| STB_LOPROC |  13   |
| STB_HIPROC |  15   |

STB_LOCAL

 Local symbols are not visible outside the object file containing their definition. Local symbols of the same name may exist in multiple files without interfering with each other.
STB_GLOBAL

 Global symbols are visible to all object files being combined. One file's definition of a global symbol will satisfy another file's undefined reference to the same global symbol.

STB_WEAK 

Weak symbols resemble global symbols, but their definitions have lower precedence.
STB_LOPROC through  STB_HIPROC

Values in this inclusive range are reserved for processor-specific semantics.

In each symbol table, all symbols with  STB_LOCAL binding precede the weak and global
symbols. A symbol's type provides a general classification for the associated entity.

#### Symbol Types, ELF32_ST_TYPE

|    Name     | Value |
| :---------: | :---: |
| STT_NOTYPE  |   0   |
| STT_OBJECT  |   1   |
|  STT_FUNC   |   2   |
| STT_SECTION |   3   |
|  STT_FILE   |   4   |
| STT_LOPROC  |  13   |
| STT_HIPROC  |  15   |

STT_NOTYPE 

The symbol's type is not specified.
STT_OBJECT

 The symbol is associated with a data object, such as a variable, an array,and so on.
STT_FUNC 

The symbol is associated with a function or other executable code.
STT_SECTION 

The symbol is associated with a section. Symbol table entries of this type exist primarily for relocation and normally have  STB_LOCAL binding.这种类型的symbol主要用于relocation

STT_FILE

A file symbol has  STB_LOCAL binding, its section index is  SHN_ABS , and it precedes the other  STB_LOCAL symbols for the file, if it is present.

显然STT_FILE是相对于SHN_ABS section定义的