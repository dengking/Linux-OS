#Book I:Executable and Linking Format (ELF)

## Introduction介绍

这一节描述object file的格式，它被称为ELF(Executable and Linking Format).主要有三种类型的object file：

- **relocatable file**可重定位文件：这种类型的文件用于保存与其他object file**链接**以创建**executable object file**可执行文件或**shared object file**可共享对象文件的**代码**和**数据**。有link editor来实现链接。
- **executable file**可执行文件：保存适合于执行的程序。
- **shared object file**可共享对象文件：用于保存适于在两种上下文环境中进行链接的代码和数据。第一种，**link editor**链接编辑器可以**link**链接它和其他**relocatable** object file可重定位或**shared** object file可共享来创建一个新的object file。第二种，**dynamic linker**动态链接器将它与**executable file**可执行文件和其他**shared objects**可共享对象进行组合来创建过程映像。

**object file**由**assembler**汇编器和**link editor**链接编辑器创建，它是能够直接在处理器上执行的程序的二进制表示。

在介绍之后，本章重点介绍object file以及它与构建程序的关系。第2章也描述了object file的部分内容，集中介绍于执行程序所需的信息。

##Object File的格式

**object file**可以参与程序链接（构建程序）和程序执行（运行程序）。为了方便和高效，**object file**的格式同时提供了展示文件内容的两种视图：

1. 链接视图

2. 执行视图

使用两种视图是为了满足这两种活动（构建程序和运行程序）的不同需求。如图1-1所示一个**object file**的组织。

![图1](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图1.png)

### ELF header

**ELF header**位于object file的开始处，它保存描述**object file**的组织结构的“路线图”。**Section**包含用于**链接视图**的信息：指令Section (instructions)，数据Section (data)，符号表Section (symbol table)，重定位信息Section (relocation information)，等等。本节后面对各个Section进行详细描述。第二章也将介绍各个Segments和object file的**执行视图**。

### program header table

程序头表（program header table）（如果存在的话）告诉系统如何创建进程映像。用于构建进程映像的object file（执行程序）必须有程序头表（program header table）。可重定位文件（relocatable file）则并不需要程序头表（program header table）。

### section header table

section header table包含描述各个section的信息。每个section在section header table中有一个对应的**条目**（相当于一条记录）; 每个条目给出该section的名称，大小等信息。用于**链接**期间使用的object file必须具有section header table; 其他object file可能有也可能没有。

> NOTE。虽然图中显示了program header table位于ELF header的后面，section header table位于各section的后面，实际的目标文件这几个部分的顺序关系可能与上图中展示的不同，可以确定的是ELF header一定位于文件的头部。

## Data Representation数据表示

如这里所描述的，object file的格式支持具有8位字节和32位架构的各种处理器。然而，它旨在可扩展到更大（或更小）的架构。因此，object file使用**与机器无关**的格式来表示它的**control data**，使得可以以**通用方式**来识别object file并解释其内容。object file中的剩余数据使用**目标处理器**的编码，而不用考虑创建该object file的计算机。这样在A机器上创建的object file就可以拿到B机器上进行运行或链接，即使A与B的架构不相同。

![图2](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图2.png)

object file格式定义的所有数据结构都遵循相关类的“自然”大小和对齐准则。如果必要，数据结构包含显式填充，以确保4字节对象的4字节对齐（32位处理器一次读取32位），将结构大小强制为4的倍数，依此类推。数据也从文件的开头具有适当的对齐。因此，例如，包含Elf32_Addr成员的结构将在文件内的4字节边界上对齐。

出于可移植性的原因，ELF不使用位字段。

## Character Representations字符表示

本节介绍ELF默认的字符表示，并为能够在不同系统之间移植的外部文件定义标准字符集。一些外部文件格式使用字符来表示控制信息。这些单字节字符使用7位ASCII字符集。换句话说，当ELF接口文档提到**字符常量**，例如'/'或'\ n'时，它们的**数值**应遵循7位ASCII码。对于前面的字符常量，单字节值将是47 和10。

根据字符编码，0到127范围之外的字符值可能占用一个或多个字节。应用程序可以对不同的语言使用不同的字符集扩展来控制它的字符集。虽然TIS-conformance不限制字符集，但它们通常应遵循一些简单的准则：

- 0到127之间的字符值应对应于7位ASCII码。也就是说，具有高于127的编码的字符集应该将的7位ASCII码作为子集。
- 值大于127的多字节字符编码应该只包含值在0到127范围之外的字节。也就是说，每个字符使用多个字节的字符集不应该“嵌入”类似于7位ASCII字符的字节在一个多字节，非ASCII字符内。
- 多字节字符应该是自识别的。 这允许例如在任何多字节字符对之间插入任何多字节字符，而不改变字符的解释。

这些注意事项与多语言应用程序特别相关。

## ELF Header

![图3](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图3.png)

根据该结构中各个变量的命名其实都可以推断出这些变量各自的含义，ident对应的是identity，即标识，后面会进行具体的描述。e_entry即程序的入口地址，e_phoff的含义需要拆解开来，ph即program header table，off即offset，偏移量；e_shoff的分解和e_phoff类似，sh即section header table，off即offset，偏移量；e_phentsize的含义也需要拆解开来进行了解，ph即program header table，ent即entity，条目，size即大小，那么这个变量的含义就好理解了，它用来标识program header table中一个条目的大小。e_phnum即program header entity number，表示program header table中记录的个数。e_ehsize的含义是ELF header size，即ELF header的大小。

### 1.   e_ident 

object file的初始字节主要用于将文件标记为object file，并提供与机器无关的数据，用于解码和解释文件的内容。完整的描述显示在下面的“ELF Identification”章节。

### 2.   e_type 

此成员标识对象文件的类型。

![图4](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图4.png)

虽然Core文件的内容未指定，但保留类型ET_CORE以标记这种文件类型。从ET_LOPROC到ET_HIPROC（包括）的值保留用于处理器特定的语义。保留其他值，并根据需要将其分配给新的对象文件类型。

### 3.   e_machine 

此成员的值指定单个文件所需的CPU体系结构。

![图9](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图9.png)

保留其他值，并根据需要将其分配给新计算机。特定于处理器的ELF名称使用计算机名称来区分它们。例如，下面提到的标志使用前缀EF_; 一个名为WIDGET的标志

EM_XYZ机器将被称为EF_XYZ_WIDGET。

### 4.   e_version 

此成员标识对象文件版本。

![图10](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图10.png)

值1表示原始文件格式; 扩展将创建具有更高数字的新版本。 EV_CURRENT的值，尽管在上面给出为1，将根据需要更改以反映当前版本号。

### 5.   e_entry 

该成员给出系统首次传输控制的虚拟地址，从而启动进程。 如果文件没有关联的入口点（entrypoint），则此成员保存为零。

### 6.   e_phoff

该成员保存program header table的文件偏移量（以字节为单位）。如果文件没有program header table，则此成员保存为零。

### 7.   e_shoff

该成员保存section header table的文件偏移量（以字节为单位）。 如果文件没有sectionheader table，则此成员保存为零。

### 8.   e_flags

此成员保存与文件相关联的处理器特定标志。 标志名的格式为EF_machine_flag。

### 9.  e_ehsize

该成员保存ELF头的大小（以字节为单位）。

### 10. e_phentsize

该成员保存文件程序头表（programheader table）中一个条目的大小（以字节为单位）;所有条目的大小相同。

### 11. e_phnum

此成员保存程序头表（programheader table）中的条目数。因此，e_phentsize和e_phnum的乘积给出了program header table的大小（以字节为单位）。如果文件没有program header table，e_phnum保持值为零。

### 12.        e_shentsize

该成员保存段头section header的大小（以字节为单位）。 段头sectionheader是section header table中的一个条目; 所有条目的大小相同。

### 13.        e_shnum

此成员保存section headertable中的条目数。因此，e_shentsize和e_shnum的乘积给出了section header table的大小（以字节为单位）。如果文件没有section header table，e_shnum保持值为零。

### 14.        e_shstrndx

此成员保存与节名称字符串表（section name string table）相关联的条目在节标题表（section header table）中的索引值。如果文件没有节名称字符串表（section name string table），则此成员保存值SHN_UNDEF。 有关详细信息，请参阅下面的“Sections”和“StringTable”章节。

### ELF Identification

如上所述，ELF提供了一个object file框架来支持多种处理器，多种数据编码和多类机器。为了支持该object file   family，某个object file的初始字节指定如何解释该文件，这几个字节的内容独立于进行查询的处理器，并且独立于文件的剩余内容。ELF header的初始字节对应于e_ident成员，从上面ELF Header的描述来看，e_ident是一个长度为16字节的数组。图1-4展示了该数组的各个索引的名称和数组中该位置的用途。

![图5](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图5.png)

这些索引访问包含以下值的字节。

#### EI_MAG0到EI_MAG3

文件的前4个字节组合起来表示文件的“magicnumber”，将该文件标识为ELF对象文件。

![图7](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图7.png)

 

#### EI_CLASS

下一个字节e_ident [EI_CLASS]标识文件的类或容量。

![图8](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图8.png)

## Sections

object file的section header table（段头表）允许定位该文件所有的section段。section header table（段头表）是如下所述的Elf32_Shdr结构的数组，sectionheader table的索引是这个数组的下标。ELF header的e_shoff成员给出从文件开头到section header table的字节偏移; e_shnum告诉section header table包含多少条目; e_shentsize给出每个条目的大小（以字节为单位）。

![图11](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图11.png)

### SHN_UNDEF

### SHN_LORESERVE

此值指定保留索引范围的下限值。

### SHN_LOPROC through SHN_HIPROC

在SHN_LOPROC到SHN_HIPROC范围中的值为处理器特定的语义所保留。

### SHN_ABS

此值指定相应引用的绝对值。例如，相对于section号SHN_ABS定义的符号具有绝对值，并且不受重定位的影响。

### SHN_COMMON

相对于此section定义的symbols符号是common symbols,常用符号，例如FORTRAN 语言中的COMMON或C语言中未分配的外部变量。

 

### SHN_HIRESERVE

此值指定reserved indexes保留索引范围的上限。系统保留SHN_LORESERVE和SHN_HIRESERVE之间的索引，包括; 这些值不被section header table段头表引用。也就是说，段头表不包含保留索引的条目。

 

在目标文件中，除了ELF头，program header table程序头表和section header table段头表，其它节的所有信息包含在section中。此外，目标文件段满足几个条件。

l  对象文件中的每个节都有一个描述它的section header节头。可能存在没有section的section header。

l  每个section占据文件中的一个连续（可能为空）字节序列。

l  文件中的section不能重叠。 文件中没有字节驻留在多个section中。

l  对象文件可能具有inactivespace未使用的空间。各种header头和section可能不会“覆盖”目标文件中的每个字节。未使用的空间的数据的内容是未指定的。

 

 

### Section header的结构如下：

![图12](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图12.png)

#### sh_name

此成员指定section的名称。它的值是section header string table section的索引[见下面的“字符串表”），给出一个以null结束的字符串的位置。

#### sh_type

此成员对section的content内容和semantic语义进行分类。Section类型及其说明如下所示。

![图13](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图13.png)

###Special Sections

![图14](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图14.png)

#### String Table

本节介绍string table字符串表。string table字符串表段保存以空字符终止的字符序列，通常称为string字符串。object file使用这些string字符串来表示symbol和section name。通过string table section的下标来引用一个将字符串。

第一个字节，即索引为零，定义为保存一个空字符。同样，string table字符串表的最后一个字节被定义为保持一个空字符，确保所有字符串的以空字符终止。索引为零的**字符串**指定无名称或空名称，具体取决于上下文。允许使用空的string table section字符串表部分; 它的section header段头的sh_size成员将为零。非零索引对于空string table section无效。

section header的sh_name成员表示该section的名称，它的值是一个索引，表示该section的名称在section name string table中的索引值，section namestring table在section header的索引值（位置）由ELF头部的e_shstrndx成员指定。下图显示了具有25个字节的字符串表以及与各种索引关联的字符串。

![图15](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图15.png)

![图16](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图16.png)



如示例所示，string table index字符串表索引可以引用section段中的任何字节。字符串可能出现多次; 可能存在对子字符的引用; 并且单个字符串可以被引用多次。还允许未被引用的字符串。

在程序中定义的函数名称，变量名称就包含在此section中，symbol table是对这些字符串的解释。其他section是通过index来引用string section中的 字符串的。



#### Symbol Table

object file的symbol table包含需要被定位和重定位的信息（程序符号定义和引用），一个符号表索引是这个数组的下标。索引0指定了表的第一个入口，充当未定义符号索引。这个初始化入口的内容会在本节后面部分指定。

![图18](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图18.png)



符号表条目的格式如下：

![图19](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图19.png)



##### st_name

此成员的值是在object file的symbol string table中的索引，symbol string table保存了symbol的字符表示。

##### st_value

该成员给出了相关联的symbol的值。一个symbol的值可以是是absolute value，地址等等，它的值取决于上下文。 关于symbol的值详细信息会在下面进行解释。

##### st_size

许多symbol具有大小。例如，数据对象的大小是对象中包含的字节数。如果符号没有大小或未知大小，则此成员保留0。

##### st_info

此成员指定符号的type类型和binding attributes绑定属性。下面显示了值和含义的列表。以下代码显示如何处理值。

![图20](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图20.png)



#####st_shndx

每个symbol table entry符号表条目都是相对于某个section段“定义”的;这个成员表示相关联的section在section header table节头表的索引值。如图1-7和相关文本所述，一些段索引表示特殊含义。

A symbol's binding determines the linkage visibility and behavior.符号的绑定决定了链接的可见性和行为。

### symbol binding

![图21](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图21.png)

#### STB_LOCAL

Local symbols are not visible outside the object file containing their
definition在包含此symbol定义的object file之外的object file中此symbol是不可见的. Local symbols of the same name may exist in multiple files without interfering with each other显然在不同的object file中是可以存在相同名字的local symbol的。

#### STB_GLOBAL

Global symbols are visible to all object files being combined global symbol是全局可见的. One file's definition of a global symbol will satisfy another file's undefined reference to the same global symbol.

#### STB_WEAK

Weak symbols resemble <!--类似-->global symbols, but their definitions have lower precedence <!--优先级低一些-->.

####STB_LOPROC through STB_HIPROC

Values in this inclusive range are reserved for processor-specific semantics.



In each symbol table, all symbols with  STB_LOCAL binding precede the weak and global
symbols<!--在每个symbol table中，local symbol的binding是优先于weak symbol和global symbol的-->. A symbol's type provides a general classification for the associated entity.

### symbol type

![图23](D:\mydoc\others\ELF\ELF参考文档翻译翻译\图23.png)

####STT_NOTYPE 

The symbol's type is not specified.

####STT_OBJECT 

The symbol is associated with a data object, such as a variable<!--变量-->, an array<!--数组-->,and so on.

####STT_FUNC

 The symbol is associated with a function<!--函数--> or other executable code<!--可执行代码-->.

####STT_SECTION 

The symbol is associated with a section<!--这种类型的符号通常和一个section相关联-->. Symbol table entries of this type exist primarily for relocation and normally have  STB_LOCAL binding<!--这种类型的符号用于relocation并且有STB_LOCAL binding-->.

####STT_LOPROC through STT_HIPROC

Values in this inclusive range are reserved for processor-specific semantics. If a symbol's value refers to a specific location within a section, its section index member,  st_shndx , holds an index into the section header table.As the section moves during relocation, the symbol's value changes as well,and references to the symbol continue to "point'' to the same location in the
program. Some special section index values give other semantics.

####STT_FILE 

A file symbol has  STB_LOCAL binding, its section index is  SHN_ABS , and
it precedes the other  STB_LOCAL symbols for the file, if it is present.

The symbols in ELF object files convey specific information to the linker and loader. See the
operating system sections for a description of the actual linking model used in the system.<!--ELF对象文件中的符号传达特定信息给linker链接器和loader加载器。在操作系统章节中有系统实际使用的链接模型的描述。-->

####SHN_ABS 

The symbol has an absolute value that will not change because of relocation.<!--此symbol的值不会因为relocation而改变-->
SHN_COMMON The symbol labels a common block that has not yet been allocated. The
symbol's value gives alignment constraints, similar to a section's
sh_addralign member. That is, the link editor will allocate the storage
for the symbol at an address that is a multiple of  st_value . The symbol's
size tells how many bytes are required.
SHN_UNDEF This section table index means the symbol is undefined. When the link
editor combines this object file with another that defines the indicated
symbol, this file's references to the symbol will be linked to the actual
definition.