# epoll nonblocking-IO

提出问题：在使用`epoll`等IO multiplexing system call的时候，是否需要将file descriptor设置为nonblocking？下面是对这个问题的详细讨论；



## stackoverflow [Why having to use non-blocking fd in a edge triggered epoll function?](https://stackoverflow.com/questions/14643249/why-having-to-use-non-blocking-fd-in-a-edge-triggered-epoll-function)



### [A](https://stackoverflow.com/a/14643400)

> NOTE: 
>
> 解释得非常到位

The idea is to try to completely drain(喝光、耗尽) the file descriptor when you have an edge-triggered notification that there is data to be had. So, once `epoll()` returns, you loop over the `read()` or `write()` until it returns `-EAGAIN` when there is no more data to be had.

If the `fd` was opened blocking, then this last `read()` or `write()` would also block, and you wouldn't have the chance to go back to the `epoll()` call to wait on the entire set of `fds`. When opened nonblocking, the last `read()`/`write()` does return, and you do have the chance to go back to polling.

> NOTE: 上面这段话中所描述的情况其实就是在[man EPOLL(7)](http://man7.org/linux/man-pages/man7/epoll.7.html) 中所说的：

> An application that employs the `EPOLLET` flag should use nonblocking file descriptors to avoid having a blocking read or write **starve** a task that is handling multiple file descriptors. 


This is not so much of a concern when using `epoll()` in a level-triggered fashion, since in this case `epoll()` will return immediately if there is *any* data to be had. So a (pseudocode) loop such as:

```C
while (1) {
  epoll();
  do_read_write();
}
```

> NOTE: 
>
> 在这种情况下，只要`epoll();`返回就可以进行read、write，因为此时一定是由数据的；



## eklitzke [Blocking I/O, Nonblocking I/O, And Epoll](https://eklitzke.org/blocking-io-nonblocking-io-and-epoll)



## redis usage

在redis的`listenToPort`中，将用于listen的socket设置成了nonblocking。

在redis的`client *createClient(int fd)`中，将用于于client进行通信的socket设置成了nonblocking。