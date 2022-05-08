# 1.7 Error Handling

When an error occurs in one of the UNIX System functions, a negative value is often returned, and the integer errno is usually set to a value that tells why.



But in an environment that supports threads, the process address space is shared among multiple threads, and each thread needs its own local copy of `errno` to prevent one thread from interfering with another. Linux, for example, supports multithreaded access to `errno` by defining it as

```C++
extern int *_ _errno_location(void); // 这个函数返回error no地址
#define errno (*_ _errno_location()) // errno其实是一个macro
```

> NOTE: tag-per-thread private私有-errno



## Error Recovery

> NOTE: 
>
> 对error handling的总结非常好

The errors defined in `<errno.h>` can be divided into two categories: fatal and nonfatal.

A **fatal error** has no recovery action. The best we can do is print an error message on the user ’s screen or to a log file, and then exit. 

Nonfatal errors, on the other hand, can sometimes be dealt with more robustly. Most nonfatal errors are temporary, such as a resource shortage(不足), and might not occur when there is less activity on the system. Resource-related nonfatal errors include `EAGAIN`, `ENFILE`, `ENOBUFS`, `ENOLCK`, `ENOSPC`, `EWOULDBLOCK`, and sometimes `ENOMEM`. `EBUSY` can be treated as nonfatal when it indicates that a shared resource is in use. Sometimes, `EINTR` can be treated as a nonfatal error when it interrupts a slow system call (more on this in Section 10.5).

The typical recovery action for a resource-related nonfatal error is to delay and retry later. This technique can be applied in other circumstances. For example, if an `error` indicates that a network connection is no longer functioning, it might be possible for the application to delay a short time and then reestablish the connection. Some applications use an exponential backoff algorithm, waiting a longer period of time in each subsequent iteration.

Ultimately, it is up to the application developer to determine the cases where an application can recover from an error. If a reasonable recovery strategy can be used, we can improve the robustness of our application by avoiding an abnormal exit.

> NOTE: 
>
> 相关内容
>
> APUE 12.6 Thread-Specific Data
>
> APUE 10.6 Reentrant Functions
>
> APUE 12.5 Reentrancy
>
> APUE 8.9  Race Conditions



