SHN_ABS 

This value specifies absolute values for the corresponding reference. For example, **symbols** defined relative to section number  SHN_ABS have absolute values and are not affected by relocation.

相对于这个section定义的symbol是不受relocation影响的

在阅读Symbol Types的介绍中发现有一类symbol是相对于SHN_ABS定义：STT_FILE，它的定义如下：

STT_FILE

A file symbol has  STB_LOCAL binding, its section index is  SHN_ABS , and it precedes the other  STB_LOCAL symbols for the file, if it is present.

SHN_COMMON 

**Symbols** defined relative to this section are common symbols, such as FORTRAN  COMMON or unallocated C external variables.

公共symbol