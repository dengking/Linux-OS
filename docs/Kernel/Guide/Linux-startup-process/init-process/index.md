# init process

1、它有着多种实现，在 `Operating-system-service-management` 章节对这些implementation进行说明

## wikipedia [init](https://en.wikipedia.org/wiki/Init)

In [Unix](https://en.wikipedia.org/wiki/Unix)-based computer [operating systems](https://en.wikipedia.org/wiki/Operating_system), **init** (short for *initialization*) is the first [process](https://en.wikipedia.org/wiki/Process_(computer_science)) started during [booting](https://en.wikipedia.org/wiki/Booting) of the computer system. 

Init is a [daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) process that continues running until the system is shut down. 

It is the direct or indirect [ancestor](https://en.wikipedia.org/wiki/Parent_process) of all other processes and automatically adopts all [orphaned processes](https://en.wikipedia.org/wiki/Orphan_process). 

> NOTE: 
> 1、它会收养"all [orphaned processes](https://en.wikipedia.org/wiki/Orphan_process)"，

Init is started by the [kernel](https://en.wikipedia.org/wiki/Kernel_(computing)) during the [booting](https://en.wikipedia.org/wiki/Booting) process; a [kernel panic](https://en.wikipedia.org/wiki/Kernel_panic) will occur if the kernel is unable to start it. Init is typically assigned [process identifier](https://en.wikipedia.org/wiki/Process_identifier) 1.