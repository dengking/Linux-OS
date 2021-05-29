# [CAPABILITIES(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html)

capabilities - overview of Linux capabilities

> NOTE: 
>
> 需要阅读前面的内容再来阅读本文，否则难以掌握

For the purpose of performing permission checks, traditional UNIX implementations distinguish two categories of processes:

1、privileged processes (whose effective user ID is 0, referred to as superuser or root), and 

2、unprivileged processes (whose effective UID is nonzero).  

Privileged processes bypass all kernel permission checks, while unprivileged processes are subject to full permission checking based on the process's  credentials (usually: effective UID, effective GID, and   supplementary group list).

> NOTE: 
>
> 在 linuxjournal [Taking Advantage of Linux Capabilities](https://www.linuxjournal.com/article/5737) 中，有类似的分析



Starting with kernel 2.2, Linux divides the privileges traditionally associated with superuser into distinct units, known as **capabilities**, which can be independently enabled and disabled.  Capabilities are a per-thread attribute.



## Capabilities list



## Past and current implementation



## Notes to kernel developers



## Thread capability sets



## File capabilities



### File capability extended attribute versioning



## Transformation of capabilities during `execve()`



## Safety checking for capability-dumb binaries



## Capabilities and execution of programs by root



## Set-user-ID-root programs that have file capabilities



## Capability bounding set



## Effect of user ID changes on capabilities



## Programmatically adjusting capability sets



## The securebits flags: establishing a capabilities-only environment



## Per-user-namespace "set-user-ID-root" programs



## Namespaced file capabilities



## Interaction with user namespaces
