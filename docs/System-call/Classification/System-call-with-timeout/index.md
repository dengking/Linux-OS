# System call with timeout

带有max blocking time的system call非常重要，有必要进行总结

`pthread_mutex_timedlock`

`pthread_rwlock_timedrdlock`

`pthread_cond_timedwait`

`select`

`poll`

[`epoll_wait`](http://man7.org/linux/man-pages/man2/epoll_wait.2.html)

## TODO

https://stackoverflow.com/questions/35986107/handling-systemcommand-call-timeout-in-linux

### interrupt一个sleeping中的thread
使用带超时时间的system call来实现interrupt一个sleeping中的thread。

