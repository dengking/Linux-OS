# Barrier



## 维基百科[Barrier (computer science)](https://en.wikipedia.org/wiki/Barrier_(computer_science))



## Oracle [Using Barrier Synchronization](https://docs.oracle.com/cd/E19253-01/816-5137/gfwek/index.html)



## System call

### [pthread_barrier_init(3)](https://linux.die.net/man/3/pthread_barrier_init)

### [pthread_barrier_destroy(3)](http://man7.org/linux/man-pages/man3/pthread_barrier_destroy.3p.html)

### [pthread_barrier_wait(3)](https://linux.die.net/man/3/pthread_barrier_wait)

这篇讲解地不错。

关于`PTHREAD_BARRIER_SERIAL_THREAD`的用途，参见APUE chapter 11.6.8.

## Exmaple

http://man7.org/tlpi/code/online/dist/threads/pthread_barrier_demo.c.html



### APUE 11.6.8 Barriers

在APUE 11.6.8 Barriers给出了一个使用排序的非常好的例子，在本节的目录下有改例子的可执行程序。



#### 编译问题

使用`pthread_barrier_t`时，如果使用如下编译指令：
```
gcc -std=gnu99 barrier.c -lpthread
```
需要注意的是，如果使用如下编译指令：
```
gcc -std=c99 barrier.c -lpthread
```
则会报如下错误：
```
未知的类型名‘pthread_barrier_t’
```

具体参考：https://stackoverflow.com/questions/15673492/gcc-compile-fails-with-pthread-and-option-std-c99