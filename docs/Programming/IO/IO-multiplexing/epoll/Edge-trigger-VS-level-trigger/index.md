# Edge-trigger VS level-trigger

在下面文章中，讨论了"edge-trigger VS level-trigger":

1、wikipedia [epoll](https://en.wikipedia.org/wiki/Epoll) 

2、[epoll(7) — Linux manual page](http://man7.org/linux/man-pages/man7/epoll.7.html) 





## stackoverflow [What is the purpose of epoll's edge triggered option?](https://stackoverflow.com/questions/9162712/what-is-the-purpose-of-epolls-edge-triggered-option)



### [A](https://stackoverflow.com/a/9162805)



When an FD becomes read or write ready, you might not necessarily want to read (or write) all the data immediately.

Level-triggered epoll will keep nagging you as long as the FD remains ready, whereas edge-triggered won't bother you again until the next time you get an [`EAGAIN`](https://stackoverflow.com/questions/4058368/what-does-eagain-mean) (so it's more complicated to code around, but can be more efficient depending on what you need to do).

Say you're writing from a resource to an FD. If you register your interest for that FD becoming write ready as level-triggered, you'll get constant notification that the FD is still ready for writing. If the resource isn't yet available, that's a waste of a wake-up, because you can't write any more anyway.

If you were to add it as edge-triggered instead, you'd get notification that the FD was write ready once, then when the other resource becomes ready you write as much as you can. Then if `write(2)`returns `EAGAIN`, you stop writing and wait for the next notification.

The same applies for reading, because you might not want to pull all the data into user-space before you're ready to do whatever you want to do with it (thus having to buffer it, etc etc). With edge-triggered `epoll` you get told when it's ready to read, and then can remember that and do the actual reading "as and when".



## csdn [Epoll水平触发（Level Triggered）工作模式和边缘触发（Edge Triggered）工作模式区别](https://blog.csdn.net/q623702748/article/details/52514392)