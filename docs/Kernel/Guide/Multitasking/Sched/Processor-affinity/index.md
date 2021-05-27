# 关于本章



## wikipedia [Processor affinity](https://en.wikipedia.org/wiki/Processor_affinity)



## [man 1 `taskset`](https://www.man7.org/linux/man-pages/man1/taskset.1.html)



## [如何指定进程运行的CPU(命令行 taskset)](https://blog.csdn.net/xluren/article/details/43202201)

同时，因为最近在看redis的相关资料，redis作为单进程模型的程序，为了充分利用多核CPU，常常在一台server上会启动多个实例。而为了减少切换的开销，有必要为每个实例指定其所运行的CPU。

### 显示进程运行的CPU

```shell
taskset -p 21184
```

pid 21184's current affinity mask: `ffffff`，`ffffff`实际上是二进制24个低位均为1的bitmask，每一个1对应于1个CPU，表示该进程在24个CPU上运行。



### 指定进程运行在某个特定的CPU上

```shell
skset -p c 3 21184
```

3表示CPU将只会运行在第4个CPU上（从0开始计数）。

显示结果：

```shell
pid 21184's current affinity list: 0-23
pid 21184's new affinity list: 3
```

### 进程启动时指定CPU

```shell
taskset -c 1 ./redis-server ../redis.conf
```

