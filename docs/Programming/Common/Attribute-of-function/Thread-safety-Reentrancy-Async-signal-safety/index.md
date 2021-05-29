# Reentrant and async-signal safe and thread-safe

哪些情况下会出现重入？

– 调用signal handler，而中断正在执行的函数，在signal handler中调用与被中断函数相同的函数，这就是重入

– 多个线程在相同的时刻，调用同一个函数



APUE 12.5 Reentrancy给出的definition如下：

> If a function is **reentrant** with respect to multiple threads, we say that it is ***thread-safe***. This doesn’t tell us, however, whether the function is reentrant with respect to signal handlers. We say that a function that is safe to be reentered from an asynchronous signal handler is ***async-signal safe***. We saw the async-signal safe functions in Figure 10.4 when we discussed reentrant functions in Section 10.6.



APUE 10.6 Reentrant Functions给出的definition如下：

> The Single UNIX Specification specifies the functions that are guaranteed to be safe to call from within a signal handler. These functions are reentrant and are called ***async-signal safe*** by the Single UNIX Specification. Besides being reentrant, they block any signals during operation if delivery of a signal might cause inconsistencies.





## draft

### 不使用async-signal unsafe function

当然有些情况下的race condition是通过OS提供的各种方法是无法avoid，比如在APUE 的10.6 Reentrant Functions章节介绍的情况，这种情况下，就只有不使用这些async-signal unsafe function才能够彻底规避；

> 思考:原子操作有哪些优良性质



