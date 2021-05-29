# `clone`





## [clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html)

### The `clone()` wrapper function

When the child process is created with the `clone()` wrapper function, it commences(开始) execution by calling the function pointed to by the argument `fn`.  (This differs from `fork(2)`, where execution continues in the child from the point of the `fork(2)` call.)  The `arg` argument is passed as the argument of the  function `fn`.

> NOTE: 
>
> 和`pthread_create`

### `clone3()`



### The child termination signal





## thegreenplace [Launching Linux threads and processes with clone](https://eli.thegreenplace.net/2018/launching-linux-threads-and-processes-with-clone/)

> NOTE: 非常好的文章，能够帮助我们理解Linux kernel的实现


