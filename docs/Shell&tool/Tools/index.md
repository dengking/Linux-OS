# 关于本章

本章总结Linux中的常见工具。

## Command总览

查询process、thread

查询file：

- open files 动态
- file 静态

process 与 file 之间的映射关系：

- fuser
- lsof



### `**`stat

vmstat

netstat

在[**`sysstat`**](https://en.wikipedia.org/wiki/Sysstat)中，包含了一系列performance monitor tools，这些tools一般都以`**`stat命名：

- [iostat](https://en.wikipedia.org/wiki/Iostat) (1) reports basic CPU statistics and input/output statistics for devices, partitions and network filesystems.
- [mpstat](https://en.wikipedia.org/wiki/Mpstat)(1) reports individual or combined processor related statistics.
- [pidstat](https://en.wikipedia.org/w/index.php?title=Pidstat&action=edit&redlink=1)(1) reports statistics for Linux tasks (processes) : I/O, CPU, memory, etc.
- [nfsiostat](https://en.wikipedia.org/w/index.php?title=Nfsiostat&action=edit&redlink=1)(1) reports input/output statistics for network filesystems (NFS).
- [cifsiostat](https://en.wikipedia.org/w/index.php?title=Cifsiostat&action=edit&redlink=1)(1) reports I/O statistics for CIFS resources.