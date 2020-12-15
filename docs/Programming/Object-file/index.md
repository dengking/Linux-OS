# 关于本章

本章讨论Linux OS对object file的支持，这对于一个OS而言，是非常重要的一个功能。

## Object file in Linux OS

我们常常以多种形式来提供我们的程序文件，Linux OS支持的Object file:

1) object file

2) executable file(可执行程序文件)

3) shared library(动态链接库文件)

### ELF

Linux OS定义的Object file的格式；

### Interface

|                 | load api |      |
| --------------- | -------- | ---- |
| executable file | `exec`   |      |
| shared library  | `dlopen` |      |



