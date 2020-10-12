#Segment Permissions

A program to be loaded by the system must have at least one loadable segment (although this
is not required by the file format). When the system creates loadable segments' memory images,
it gives access permissions as specified in the  p_flags  member.

一个程序至少有一个loadable segment才能够被操作系统装载。当操作系统创建loadable segment的memory image的时候，它会按照p_flags成员来设置这个已经装载到内存中的segment的访问权限。

Figure 2-2. Segment Flag Bits, p_flags

|    Name     |   Value    |   Meaning   |
| :---------: | :--------: | :---------: |
|    PF_X     |    0x1     |   Execute   |
|    PF_W     |    0x2     |    Write    |
|    PF_R     |    0x4     |    Read     |
| PF_MASKPROC | 0xf0000000 | Unspecified |

All bits included in the  PF_MASKPROC  mask are reserved for processor-specific semantics. If
meanings are specified, the processor supplement explains them.

If a permission bit is 0, that type of access is denied. Actual memory permissions depend on the memory management unit, which may vary from one system to another. Although all flag combinations are valid, the system may grant more access than requested. In no case, however,will a segment have write permission unless it is specified explicitly. The following table shows both the exact flag interpretation and the allowable flag interpretation. TIS-conforming systems may provide either.

如果一个permission bit设置为0，那么它对应的access type是被拒绝的。除非显式地给一个segment指定write permission，否则它是不会有write permission的。

Figure 2-3. Segment Permissions

![segment permission tab](D:\mydoc\others\ELF\diary\segment permission tab.png)

For example, typical text segments have read and execute —but not write —permissions. Data
segments normally have read, write, and execute permissions.

可用看到segment permission的取值为从0到7，其实这些取值正式PF_X，PF_W，PF_R的组合。

其实关于 Segment Permissions和Segment Flag 我有一个疑问：

在program header中保存的到底是0到7，还是PF_X，PF_W，PF_R？？