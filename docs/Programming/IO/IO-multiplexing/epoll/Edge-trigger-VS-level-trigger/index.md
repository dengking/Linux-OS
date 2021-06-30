# Edge-trigger VS level-trigger

在下面文章中，讨论了"edge-trigger VS level-trigger":

1、wikipedia [epoll](https://en.wikipedia.org/wiki/Epoll) 

2、[epoll(7) — Linux manual page](http://man7.org/linux/man-pages/man7/epoll.7.html) 

3、zhihu [epoll的边沿触发模式(ET)真的比水平触发模式(LT)快吗？(当然LT模式也使用非阻塞IO，重点是要求ET模式下的代码不能造成饥饿)](https://www.zhihu.com/question/20502870)

我的一些总结:

一、Edge-trigger只有在状态变更的时候，才会触发

二、Level-trigger只要条件满足就一直触发

三、它们的差异主要体现在"处理`EPOLLOUT`事件"上，在 csdn [epoll LT/ET 深入剖析](https://blog.csdn.net/dongfuye/article/details/50880251) 中进行了非常好的剖析

1、Redis level trigger、响应小、`EPOLLOUT`事件并不频繁

2、Nginx edge trigger、响应大、`EPOLLOUT`事件可能频繁

## zhihu [epoll的边沿触发模式(ET)真的比水平触发模式(LT)快吗？(当然LT模式也使用非阻塞IO，重点是要求ET模式下的代码不能造成饥饿)](https://www.zhihu.com/question/20502870)

### [dong的回答](https://www.zhihu.com/question/20502870/answer/89738959)

ET本身并不会造成饥饿，由于事件只通知一次，开发者一不小心就容易遗漏了待处理的数据，像是饥饿，实质是bug

使用ET模式，特定场景下会比LT更快，因为它可以便捷的处理`EPOLLOUT`事件，省去打开与关闭`EPOLLOUT`的`epoll_ctl（EPOLL_CTL_MOD）`调用。从而有可能让你的性能得到一定的提升。例如你需要写出1M的数据，写出到socket 256k时，返回了`EAGAIN`，ET模式下，当再次epoll返回`EPOLLOUT`事件时，继续写出待写出的数据，当没有数据需要写出时，不处理直接略过即可。而LT模式则需要先打开`EPOLLOUT`，当没有数据需要写出时，再关闭`EPOLLOUT`（否则会一直返回`EPOLLOUT`事件）。

> NOTE: 
>
> 上述是两种的主要差别；
>
> "而LT模式则需要先打开`EPOLLOUT`，当没有数据需要写出时，再关闭`EPOLLOUT`（否则会一直返回`EPOLLOUT`事件）"
>
> 这段话是需要结合具体的案例来进行理解的: 将响应写到fd中，如果返回了`EAGAIN`，则说明socket的send buffer已经被写满了，此时
>
> 

总体来说，ET处理`EPOLLOUT`方便高效些，LT不容易遗漏事件、不易产生bug。

如果server的响应通常较小，不会触发`EPOLLOUT`，那么适合使用LT，例如redis等。而nginx作为高性能的通用服务器，网络流量可以跑满达到1G，这种情况下很容易触发`EPOLLOUT`，则使用ET。

> NOTE: 
>
> 上面这段话中的 "如果server的响应通常较小，不会触发EPOLLOUT" 如何理解？
>
> 它的意思是直接去写，一次就写完了，那么就不需要再注册`EPOLLOUT`了，只有当一次无法写完的情况下，才需要注册`EPOLLOUT`，待下次触发的时候，将剩余的写完。

关于某些场景下ET模式比LT模式效率更好，我有篇文章进行了详细的解释与测试，参看
[epoll LT/ET 深入剖析](https://link.zhihu.com/?target=http%3A//blog.csdn.net/dongfuye/article/details/50880251)

这里有两个例子，分别演示了LT与ET两种工作模式
[handy/epoll-et.cc at master · yedf/handy · GitHub](https://link.zhihu.com/?target=https%3A//github.com/yedf/handy/blob/master/raw-examples/epoll-et.cc)
[handy/epoll.cc at master · yedf/handy · GitHub](https://link.zhihu.com/?target=https%3A//github.com/yedf/handy/blob/master/raw-examples/epoll.cc)



## csdn [epoll LT/ET 深入剖析](https://blog.csdn.net/dongfuye/article/details/50880251)

> NOTE: 
>
> 这篇文章的作者和 zhihu [epoll的边沿触发模式(ET)真的比水平触发模式(LT)快吗？(当然LT模式也使用非阻塞IO，重点是要求ET模式下的代码不能造成饥饿)](https://www.zhihu.com/question/20502870) # [dong的回答](https://www.zhihu.com/question/20502870/answer/89738959) 的作者是同一个人

EPOLL事件有两种模型：

**Level Triggered (LT) 水平触发**

socket接收缓冲区不为空 有数据可读 读事件一直触发

socket发送缓冲区不满 可以继续写入数据 写事件一直触发

> NOTE: 
>
> 刚开始的时候，send buffer是空的，如果刚开始的时候就注册`EPOLLOUT`，则会一直导致触发；

符合思维习惯，`epoll_wait`返回的事件就是socket的状态

**Edge Triggered (ET) 边沿触发**

socket的接收缓冲区状态变化时触发读事件，即空的接收缓冲区刚接收到数据时触发读事件

socket的发送缓冲区状态变化时触发写事件，即**满的缓冲区刚空出空间时触发读事件**

> NOTE: 
>
> 一、"**满的缓冲区刚空出空间时触发读事件**"
>
> 也就是刚开始的时候，是不会触发的

仅在状态变化时触发事件

### ET还是LT?

**LT的处理过程：**

1、`accept`一个连接，添加到`epoll`中监听`EPOLLIN`事件

2、当`EPOLLIN`事件到达时，read fd中的数据并处理

3、当需要写出数据时，把数据write到fd中；如果数据较大，无法一次性写出，那么在epoll中监听`EPOLLOUT`事件

4、当EPOLLOUT事件到达时，继续把数据write到fd中；如果数据写出完毕，那么在epoll中关闭EPOLLOUT事件

> NOTE: 
>
> 由于LT只有send buffer中有空间就一直触发的特性，导致了对它的`EPOLLIN`事件的处理是比较特殊的，遵循: 只有当一次发不完的情况下，才注册`EPOLLIN`事件，并且在发完后，需要注销，下面是对此的分析:
>
> 1、刚开始的时候，send buffer是空的，如果刚开始的时候就注册`EPOLLOUT`，则会一直导致触发，所以刚开始的时候，是不能够注册`EPOLLOUT`事件的；
>
> 2、在write的时候，如果能够发生完成，显然是不需要进行特殊的处理的；如果写不完，则需要注册`EPOLLIN`事件；在写完后，是需要注销的，否则会一直受到消息。

**ET的处理过程：**

1、accept一个一个连接，添加到epoll中监听`EPOLLIN`|`EPOLLOUT`事件

2、当`EPOLLIN`事件到达时，read fd中的数据并处理，read需要一直读，直到返回`EAGAIN`为止

3、当需要写出数据时，把数据write到fd中，直到数据全部写完，或者write返回`EAGAIN`

4、当EPOLLOUT事件到达时，继续把数据write到fd中，直到数据全部写完，或者write返回EAGAIN

> NOTE: 
>
> 由于ET是**满的缓冲区刚空出空间时触发读事件**，因此在刚开始的时候，就需要注册`EPOLLOUT`事件；一直注册`EPOLLOUT`事件并没有问题，因为平时它不会触发；只有当将它写满后，它才会触发；显然它省去了频繁的注册、注销的动作。

从ET的处理过程中可以看到，ET的要求是需要一直读写，直到返回EAGAIN，否则就会遗漏事件。而LT的处理过程中，直到返回EAGAIN不是硬性要求，但通常的处理过程都会读写直到返回EAGAIN，但LT比ET多了一个开关EPOLLOUT事件的步骤

LT的编程与poll/select接近，符合一直以来的习惯，不易出错；

ET的编程可以做到更加简洁，某些场景下更加高效，但另一方面容易遗漏事件，容易产生bug；

这里有两个简单的例子演示了LT与ET的用法(其中epoll-et的代码比epoll要少10行)：
https://github.com/yedf/handy/blob/master/raw-examples/epoll.cc
https://github.com/yedf/handy/blob/master/raw-examples/epoll-et.cc

针对容易触发LT开关EPOLLOUT事件的情景（让服务器返回1M大小的数据），我用ab做了性能测试
测试的结果显示ET的性能稍好，详情如下：
LT 启动命令 ./epoll a
ET 启动命令 ./epoll-et a
ab 命令：ab -n 1000 -k 127.0.0.1/
LT 结果：Requests per second:    42.56 [#/sec] (mean)
ET 结果：Requests per second:    48.55 [#/sec] (mean)

当我把服务器返回的数据大小改为48576时，开关EPOLLOUT更加频繁，性能的差异更大
ab 命令：ab -n 5000 -k 127.0.0.1/
LT 结果：Requests per second:    745.30 [#/sec] (mean)
ET 结果：Requests per second:    927.56 [#/sec] (mean)

对于nginx这种高性能服务器，ET模式是很好的，而其他的通用网络库，更多是使用LT，避免使用的过程中出现bug


## stackoverflow [What is the purpose of epoll's edge triggered option?](https://stackoverflow.com/questions/9162712/what-is-the-purpose-of-epolls-edge-triggered-option)



### [A](https://stackoverflow.com/a/9162805)

> NOTE: 
>
> 简而言之: edge-triggered更加高效，但是也使得编程更加复杂

When an FD becomes read or write ready, you might not necessarily want to read (or write) all the data immediately.

Level-triggered epoll will keep nagging(唠叨) you as long as the FD remains ready, whereas edge-triggered won't bother you again until the next time you get an [`EAGAIN`](https://stackoverflow.com/questions/4058368/what-does-eagain-mean) (so it's more complicated to code around, but can be more efficient depending on what you need to do).

> NOTE: 
>
> "you get an [`EAGAIN`](https://stackoverflow.com/questions/4058368/what-does-eagain-mean) " 说明所有的数据都已经read了

#### Writing from a resource to an FD

Say you're writing from a resource to an FD. If you register your interest for that FD becoming write ready as level-triggered, you'll get constant notification that the FD is still ready for writing. If the resource isn't yet available, that's a waste of a wake-up, because you can't write any more anyway.

> NOTE: 
>
> 假设您正在从一个资源写入一个FD。如果将您感兴趣的FD注册为级别触发的可写状态，那么您将不断得到FD仍可写的通知。如果资源尚未可用，这是一种浪费的唤醒，因为您无论如何都不能编写更多内容。

If you were to add it as edge-triggered instead, you'd get notification that the FD was write ready once, then when the other resource becomes ready you write as much as you can. Then if `write(2)`returns `EAGAIN`, you stop writing and wait for the next notification.

#### Read from FD into user-space 

The same applies for reading, because you might not want to pull all the data into user-space before you're ready to do whatever you want to do with it (thus having to buffer it, etc etc). With edge-triggered `epoll` you get told when it's ready to read, and then can remember that and do the actual reading "as and when".



## csdn [Epoll水平触发（Level Triggered）工作模式和边缘触发（Edge Triggered）工作模式区别](https://blog.csdn.net/q623702748/article/details/52514392)