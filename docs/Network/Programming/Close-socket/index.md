# close socket

Linux 提供了如下system call来关闭一个socket:

1、man 2 close

这是Linux通用的关闭fd 的system call

2、man 2 shutdown

## What do `close` do? 

当使用`close`、`shutdown`来关闭一个socket的时候，它所做的是:

1、本端发送`FIN`，然后进入`FIN-WAIT-1`状态

2、等待FIN ACK，在收到FIN ACK后，进入`FIN-WAIT-2`状态，然后返回

> NOTE: 
>
> 是否是这样的，还有有待确认

3、本端进入`TIME_WAIT` 状态

参考:

1、stackoverflow [When is TCP option SO_LINGER (0) required?](https://stackoverflow.com/questions/3757289/when-is-tcp-option-so-linger-0-required) # [A](https://stackoverflow.com/a/13088864)



## Will `close` block 2MSL？

不会的，测试程序:

1、zhihu [网络编程：SO_REUSEADDR的使用](https://zhuanlan.zhihu.com/p/79999012) 

2、`Linux-TCP-impl`

通过其中的测试程序可知，在当调用`close(fd)`来关闭一个socket时，不会block 2MSL，而是立即返回，但是TCP connection还是会完成TCP FSM，直至完成后，对应的TCP connection才会被释放。



