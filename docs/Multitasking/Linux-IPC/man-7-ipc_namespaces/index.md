# [ipc_namespaces(7)](https://man7.org/linux/man-pages/man7/ipc_namespaces.7.html)

IPC namespaces isolate certain IPC resources, namely, System V IPC objects (see [sysvipc(7)](https://man7.org/linux/man-pages/man7/sysvipc.7.html)) and (since Linux 2.6.30) POSIX message queues (see [mq_overview(7)](https://man7.org/linux/man-pages/man7/mq_overview.7.html)).  The common characteristic of these IPC mechanisms is that IPC objects are identified by mechanisms other than filesystem pathnames.

> NOTE: 
>
> 通过上述描述可知，[ipc_namespaces(7)](https://man7.org/linux/man-pages/man7/ipc_namespaces.7.html) 其实本质上还是用于实现名称隔离的，和其他的namespace无异。