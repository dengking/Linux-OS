# 时间与空间

时间与空间在计算机科学中是经常需要考虑的问题，在进行系统program的时候，需要从time和space的角度来进行考虑。

space角度的话，就涉及到了race condition。

time角度的话，就涉及到了函数执行的时间，系统调用阻塞的时候。并且很多的系统调用都正常设置max blocked time。

比如在multiple thread环境中进行program的时候，从空间的角度进行考虑的话，就涉及防止thread之间的race condition。就涉及到原子操作。

原子操作的话，有些programming  language提供了原子操作库，OS也提供了原子函数，如APUE的chapter12.10中所提及的`pread`，`pwrite`等。



time-of-check-to-time-of-use就属于time的角度了