# [FORK(2)](http://man7.org/linux/man-pages/man2/fork.2.html)



fork - create a child process



## SYNOPSIS

```C++
       #include <unistd.h>

       pid_t fork(void);
```

## What child process does not inherit from parent

The child process is an exact duplicate of the parent process except for the following points:

> NOTE: 
>
> 原文介绍了各种child process不会从parent继承的"process attribute"
>
> 

The **process attributes** in the preceding list are all specified in POSIX.1.  The parent and child also differ with respect to the following Linux-specific process attributes:

> NOTE: 
>
> 下面都是"Linux-specific process attributes"

## Details

> NOTE:
>
> 一些细节

Note the following further points:



## RETURN VALUE 

On success, the `PID` of the child process is returned in the parent, and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, and `errno` is set to indicate the error.



## ERRORS



## NOTES 

Under Linux, `fork()` is implemented using copy-on-write pages.