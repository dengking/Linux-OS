# Classification of system call

1、总结system call的分类法。

2、本文内容还没有整理好

## 从blocking的角度来对system call进行分类

在APUE的10.5 Interrupted System Calls中介绍了slow system call，这提示有必要对linux的system call进行一下总结；

## System call with timeout

带有max blocking time的system call非常重要，有必要进行总结，参见 `System-call-with-timeout` 章节。



## 和阻塞相关问题

- 如何取消阻塞的系统调用（可以使用信号）
- `sleep`是否是阻塞，如果不是，它和阻塞有什么异同？

    

## 非阻塞与异步IO

非阻塞IO参见APUE 14.2

通过设置标志来实现非阻塞

异步IO参见14.5

## socket是如何实现的IO with timeout？





## Polling and non-polling

### Polling and Busy-waiting 

参见: 

1、维基百科[Polling (computer science)](https://en.wikipedia.org/wiki/Polling_(computer_science))

2、维基百科[Busy waiting](https://en.wikipedia.org/wiki/Busy_waiting)



Examples

1、维基百科[Spinlock](https://en.wikipedia.org/wiki/Spinlock)

2、polling sleep

### Non-polling

blocking、waiting、sleep



### TO READ

[what's different between the Blocked and Busy Waiting?](https://stackoverflow.com/questions/26541119/whats-different-between-the-blocked-and-busy-waiting)

