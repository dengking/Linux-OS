# Check if a process is stuck in linux





## docstore [21.7. Hanging Processes: Detection and Diagnostics ](https://docstore.mik.ua/orelly/weblinux2/modperl/ch21_07.htm)

Sometimes an `httpd` process might hang（被挂起） in the middle of processing a request. This may happen because of a bug in the code, such as being stuck in a while loop. Or it may be blocked in a system call, perhaps waiting indefinitely（无期限的） for an unavailable resource. To fix the problem, we need to learn in what circumstances the process hangs, so that we can reproduce the problem, which will allow us to uncover its cause. 

### 21.7.1. Hanging Because of an Operating System Problem

Sometimes you can find a process hanging because of some kind of system problem. 

For example, if the processes was doing some disk I/O operation, it might get stuck in uninterruptible sleep ('`D`' **disk wait** in `ps` report, '`U`' in `top`), which indicates either that something is broken in your kernel or that you're using NFS. Also, usually you find that you cannot `kill -9` this process. 

> NOTE: 参见: 
>
> NFS: [Network File System](http://en.wikipedia.org/wiki/Network_File_System)
>
> `ps`: `Programming\Process\Tools\ps`

Another process that cannot be killed with `kill -9` is a zombie process ('`Z`' disk wait in `ps` report, `<defunc>` in `top`), in which case the process is already dead and Apache didn't wait on it properly (of course, it can be some other process not related to Apache).

 In the case of ***disk wait***, you can actually get the `wait channel` from `ps` and look it up in your **kernel symbol table** to find out what resource it was waiting on. This might point the way to what component of the system is misbehaving, if the problem occurs frequently. docstore.mik.ua/orelly/weblinux2/modperl/ch21_07.htm

> NOTE: 
>
> 关于`wait channel`，参见`Programming\Process\Tools\ps\Wait-channel.md`
>
> 关于kernel symbol table，它其实就是System.map，参见`Kernel\Guide\Debug\System.map`