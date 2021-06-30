# Edge-trigger VS level-trigger

在下面文章中，讨论了"edge-trigger VS level-trigger":

1、wikipedia [epoll](https://en.wikipedia.org/wiki/Epoll) 

2、[epoll(7) — Linux manual page](http://man7.org/linux/man-pages/man7/epoll.7.html) 

3、zhihu [epoll的边沿触发模式(ET)真的比水平触发模式(LT)快吗？(当然LT模式也使用非阻塞IO，重点是要求ET模式下的代码不能造成饥饿)](https://www.zhihu.com/question/20502870)

我的一些总结:

1、Edge-trigger只有在状态变更的时候，才会触发

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