# Why system call slow?

一、mode switch: 从user space到kernel space，链路比较长

关于这一点，参见:

1、wikipedia [vDSO](https://en.wikipedia.org/wiki/VDSO)

> incurring the performance penalty of a [mode switch](https://en.wikipedia.org/wiki/Mode_switch) from [user mode](https://en.wikipedia.org/wiki/User_mode) to [kernel mode](https://en.wikipedia.org/wiki/Kernel_mode) that is inherent when calling these same kernel space routines by means of the [system call](https://en.wikipedia.org/wiki/System_call) interface

二、context change

参见modernescpp [The Atomic Flag](https://www.modernescpp.com/index.php/the-atomic-flag): 

> The interface of a `std::atomic_flag` is sufficient to build a spinlock. With a spinlock, you can protect a [critical section](https://www.modernescpp.com/index.php/component/content/article?id=157:threads-sharing-data&catid=35:c&Itemid=239#CriticalSection) similar to a mutex. But the spinlock will not passively wait in opposite to a mutex until it gets it mutex. It will eagerly ask for the critical section. So it saves the expensive context change in the wait state but it fully utilises the CPU:



## 素材

1、wikipedia [vDSO](https://en.wikipedia.org/wiki/VDSO)



## TODO 如何解决？

1、vsystemcall

2、vDSO