# .symtab
.symtab的全称是`Symbol Table`.
>An object file's symbol table holds information needed to **locate** and **relocate** a program's **symbolic definitions and references**. A symbol table index is a subscript into this array.

看到上面这段话中的**symbolic definitions and references**我不禁想起了之前心中一直思索的“symbol”，已经之前遇到的编译报错“undefined symbol”。

归根到底，我们的程序都是由符号组织而成的，我们人能够理解符号，计算机也能够理解符号。

下面结合源代码来看看relocatable file中的symbol table。

源代码如下：
```
#include<stdio.h>
int i;
int j = 1;
int k = 2;
char a[20] = "hello world";
void test_a()//定义函数test_a
{
     int h = 3;
     int l = 3;
     char b[20] = "hello world";
     printf("%d\n",h);
     return;
}

符号表如下：
```
Symbol table '.symtab' contains 15 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     9: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM i
    10: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 j
    11: 0000000000000004     4 OBJECT  GLOBAL DEFAULT    3 k
    12: 0000000000000010    20 OBJECT  GLOBAL DEFAULT    3 a
    13: 0000000000000000    74 FUNC    GLOBAL DEFAULT    1 test_a
    14: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
```

