# File descriptor



## New file descriptor

一、gnu libc [13.14 File Descriptor Flags](https://www.gnu.org/software/libc/manual//html_node/Descriptor-Flags.html#Descriptor-Flags)

1、man 2 `open`

2、man 2 `dup`

### man 2 `open` VS man 2 `dup`

`dup` 仅仅 copy file descriptor(不copy file descriptor flag)

`open` 会新建 file table entry、file descriptor

## Pass file descriptor

参见 `Pass-file-descriptor` 章节
