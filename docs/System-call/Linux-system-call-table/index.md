# Linux Syscall table

在 gitbooks [System calls in the Linux kernel. Part 1.](https://0xax.gitbooks.io/linux-insides/content/SysCall/linux-syscall-1.html) 中，介绍了Linux system call的实现，通过其中的内容可知Linux Syscall table: 

[linux](https://github.com/torvalds/linux/tree/16f73eb02d7e1765ccab3d2018e0bd98eb93d973)/[arch](https://github.com/torvalds/linux/tree/16f73eb02d7e1765ccab3d2018e0bd98eb93d973/arch)/[x86](https://github.com/torvalds/linux/tree/16f73eb02d7e1765ccab3d2018e0bd98eb93d973/arch/x86)/[entry](https://github.com/torvalds/linux/tree/16f73eb02d7e1765ccab3d2018e0bd98eb93d973/arch/x86/entry)/[syscalls](https://github.com/torvalds/linux/tree/16f73eb02d7e1765ccab3d2018e0bd98eb93d973/arch/x86/entry/syscalls)/[**syscall_64.tbl**](https://github.com/torvalds/linux/blob/16f73eb02d7e1765ccab3d2018e0bd98eb93d973/arch/x86/entry/syscalls/syscall_64.tbl)

```C
#
# 64-bit system call numbers and entry vectors
#
# The format is:
# <number> <abi> <name> <entry point>
#
# The abi is "common", "64" or "x32" for this file.
#
0	common	read			sys_read
1	common	write			sys_write
2	common	open			sys_open
3	common	close			sys_close
4	common	stat			sys_newstat
5	common	fstat			sys_newfstat
...
```



## linuxhint [List of Linux Syscalls](https://linuxhint.com/list_of_linux_syscalls/)



## cheat-sheets [LINUX System Call Quick Reference](http://www.cheat-sheets.org/saved-copy/Linux_Syscall_quickref.pdf)

```c
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main(void)
{
	long ID1, ID2;
	/*-----------------------------*/
	/* direct system call */
	/* SYS_getpid (func no. is 20) */
	/*-----------------------------*/
	ID1 = 7(SYS_getpid);
	printf("syscall(SYS_getpid)=%ld\n", ID1);
	/*-----------------------------*/
	/* "libc" wrapped system call */
	/* SYS_getpid (Func No. is 20) */
	/*-----------------------------*/
	ID2 = getpid();
	printf("getpid()=%ld\n", ID2);
	return (0);
}

```

