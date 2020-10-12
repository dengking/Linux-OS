#Introduction

This chapter describes the object file information and system actions that create running
programs. Executable and shared object files statically represent programs. To execute such
programs, the system uses the files to create dynamic program representations, or process
images. A process image has segments that hold its text, data, stack, and so on. This section
describes the program header and complements Chapter 1, by describing object file structures
that relate directly to program execution. The primary data structure, a program header table,
locates segment images within the file and contains other information necessary to create the
memory image for the program.

一个process image使用segment来装载text，data，stack等等。

Given an object file, the system must load it into memory for the program to run. After the
system loads the program, it must complete the process image by resolving symbolic references
among the object files that compose the process.

给定一个object file，操作系统必须把它装载到内存中才能够执行此程序。在操作系统将程序装载完成后，它必须解析symbolic reference，这样才能够完成进程的创建。

#Program Header

An executable or shared object file's program header table is an array of structures, each
describing a segment or other information the system needs to prepare the program for
execution. An object file segment contains one or more sections. Program headers are
meaningful only for executable and shared object files. A file specifies its own program header
size with the ELF header's  e_phentsize and e_phnum members [see "ELF Header'' in
Chapter 1].

program header table是一个数组，数组的元素类型是如下定义的Program Header，通过Program Header来描述一个segment或其他操作系统需要用来执行程序的信息。一个object file的segment包含一个或多个section。

Figure 2-1. Program Header

```c
typedef struct {
Elf32_Word p_type;
Elf32_Off p_offset;
Elf32_Addr p_vaddr;
Elf32_Addr p_paddr;
Elf32_Word p_filesz;
Elf32_Word p_memsz;
Elf32_Word p_flags;
Elf32_Word p_align;
} Elf32_Phdr
```

p_type 

This member tells what kind of segment this array element describes or how to
interpret the array element's information. Type values and their meanings appear
below.
p_offset 

This member gives the offset from the beginning of the file at which the first byte
of the segment resides.

此变量给出的是segment在file image中的位置

p_vaddr

 This member gives the virtual address at which the first byte of the segment resides
in memory.

此变量给出的是segment在process image中的位置

p_paddr 

On systems for which physical addressing is relevant, this member is reserved for
the segment's physical address. This member requires operating system specific
information, which is described in the appendix at the end of Book III.

此变量给出的是segment在process image中的位置

p_filesz 

This member gives the number of bytes in the file image of the segment; it may be
zero.

此变量给出的是segment在file image中的大小

p_memsz

 This member gives the number of bytes in the memory image of the segment; it
may be zero.

此变量给出的是segment在process image中的大小