# [SVIPC(7)](http://man7.org/linux/man-pages/man7/sysvipc.7.html)

sysvipc - System V interprocess communication mechanisms

## DESCRIPTION

**System V IPC** is the name given to three interprocess communication mechanisms that are widely available on UNIX systems: 

1、message queues, 

2、semaphore, and 

3、shared memory.

> NOTE: 
>
> 一、通过下面的描述可知，POSIX对这三种IPC都进行了标准化
>
> 二、下面对它们的API进行了对比

| Message queues                                               | Semaphore sets                                               | Shared memory segments                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [msgget(2)](https://man7.org/linux/man-pages/man2/msgget.2.html) | [semget(2)](https://man7.org/linux/man-pages/man2/semget.2.html) | [shmget(2)](https://man7.org/linux/man-pages/man2/shmget.2.html) |
| [msgctl(2)](https://man7.org/linux/man-pages/man2/msgctl.2.html) | [semctl(2)](https://man7.org/linux/man-pages/man2/semctl.2.html) | [shmctl(2)](https://man7.org/linux/man-pages/man2/shmctl.2.html) |



## Message queues

System V message queues allow data to be exchanged in units called messages.  Each messages can have an associated priority, POSIX message queues provide an alternative API for achieving the same result; see [mq_overview(7)](https://man7.org/linux/man-pages/man7/mq_overview.7.html).

> NOTE: 
>
> [mq_overview(7)](https://man7.org/linux/man-pages/man7/mq_overview.7.html) 是 "overview of POSIX message queues"

## Semaphore sets

System V semaphores allow processes to synchronize their actions System V semaphores are allocated in groups called sets; each semaphore in a set is a counting semaphore.  POSIX semaphores provide an alternative API for achieving the same result; see [sem_overview(7)](https://man7.org/linux/man-pages/man7/sem_overview.7.html).



## Shared memory segments

System V shared memory allows processes to share a region a memory (a "segment").  POSIX shared memory is an alternative API for achieving the same result; see [shm_overview(7)](https://man7.org/linux/man-pages/man7/shm_overview.7.html).



## IPC namespaces

For a discussion of the interaction of System V IPC objects and IPC namespaces, see [ ](https://man7.org/linux/man-pages/man7/ipc_namespaces.7.html).