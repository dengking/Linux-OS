# timer

timer interrupt对系统非常重要，它就相当于系统的heartbeat，从这个角度来看的话，timer就相当于相同的heart。因为它它触发这系统的运转，它就相当于相同的系统的[Electric motor](https://en.wikipedia.org/wiki/Electric_motor)，比如内燃机运转带动整个系统运转起来。

需要融会贯通本书中的内容，建立起operating system的运行图。



## 原来OS也是event-driven的

[Event-driven architecture](https://en.wikipedia.org/wiki/Event-driven_architecture)

[Event-driven programming](https://en.wikipedia.org/wiki/Event-driven_programming)

[Event loop](https://en.wikipedia.org/wiki/Event_loop)

[Event (computing)](https://en.wikipedia.org/wiki/Event_(computing))

各种interrupt就是所谓的event，OS中的主要event是timer event，当然除此之外还有其他的event。

这不仅让我想起了redis的event loop。



# dose kernel have main function

[Linux Kernel And Its Functions](http://www.linuxandubuntu.com/home/linux-kernel-and-its-functions)

[Does the kernel have a main() function? [closed\]](https://unix.stackexchange.com/questions/86955/does-the-kernel-have-a-main-function)

[Does kernel have main function?](https://stackoverflow.com/questions/18266063/does-kernel-have-main-function)





# operating system的中断源

IO device

timer