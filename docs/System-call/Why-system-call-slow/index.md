# Why system call slow?

1、从user space到kernel space，链路比较长

2、context change

参见modernescpp [The Atomic Flag](https://www.modernescpp.com/index.php/the-atomic-flag): 

> The interface of a std::atomic_flag is sufficient to build a spinlock. With a spinlock, you can protect a [critical section](https://www.modernescpp.com/index.php/component/content/article?id=157:threads-sharing-data&catid=35:c&Itemid=239#CriticalSection) similar to a mutex. But the spinlock will not passively wait in opposite to a mutex until it gets it mutex. It will eagerly ask for the critical section. So it saves the expensive context change in the wait state but it fully utilises the CPU: