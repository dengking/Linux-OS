# 3.14 fcntl Function

> NOTE: 
>
> 一、这个system call应该是功能最最齐全的函数
>
> 二、
>
> `FD` 的含义是file descriptor flag
>
> `FL` 的含义是 file flag

\1. Duplicate an existing descriptor (*cmd* = `F_DUPFD` or `F_DUPFD_CLOEXEC`)

\2. Get/set fifile descriptor flflags (*cmd* = F_GETFD or F_SETFD)

\3. Get/set fifile status flflags (*cmd* = F_GETFL or F_SETFL)

\4. Get/set asynchronous I/O ownership (*cmd* = F_GETOWN or F_SETOWN)

\5. Get/set record locks (*cmd* = F_GETLK, F_SETLK, or F_SETLKW)

