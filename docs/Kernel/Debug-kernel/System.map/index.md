# System.map

是在阅读docstore [21.7. Hanging Processes: Detection and Diagnostics ](https://docstore.mik.ua/orelly/weblinux2/modperl/ch21_07.htm)时，其中提及了 **kernel symbol table** 、 `wait channel` ，从而让我发现了System.map的。



## wikipedia [System.map](https://en.wikipedia.org/wiki/System.map)





### Filesystem location

- as `/boot/System.map-$(uname -r)`

> NOTE: 下面是我的系统中，system.map文件的位置，显然它是符合上述模式的：
>
> ```
> [ust@localhost ~]$ ls /boot/System.map-3.10.0-327.el7.x86_64 
> /boot/System.map-3.10.0-327.el7.x86_64
> [ust@localhost ~]$ uname -r
> 3.10.0-327.el7.x86_64
> [ust@localhost ~]$ 
> ```
>
> 



## kernelnewbies [System.map](https://kernelnewbies.org/FAQ/System.map)

"System.map". is a file (produced via nm) containing symbol names and addresses of the linux kernel binary, vmlinux.

Its primary use is in debugging.

### Application: `ksymoops` 

If a kernel "oops" message appears, the utility `ksymoops` can be used to decode the message into something useful for developers. 

### Application: `WCHAN ` field of `ps`

`ps l` uses System.map to determine the WCHAN field (you can specify a map file with the PS_SYSTEM_MAP environment variable).



## rlworkman [The system.map File](https://rlworkman.net/system.map/)