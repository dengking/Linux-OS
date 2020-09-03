# race condition  and how to avoid it

APUE的下列章节包含了race condition相关的内容：

- 8.9  Race Conditions
- 11.6 Thread Synchronization
- 3.10 File Sharing
- 3.11 Atomic Operations
- 3.3 `open` and `openat` Functions  time-of-check-to-time-of-use 

- 12.5 Reentrancy
- 10.6 Reentrant Functions



Wikipedia中关于[Race condition](https://en.wikipedia.org/wiki/Race_condition)的介绍是非常好的，显然它的核心在于race，即竞争，race的本质在于many-to-one，many **share** the one and   system's  substantive behavior is dependent on the sequence or timing of the many operate the one；

***SUMMARY*** : 刚开始的时候，我是这样定义的：many **share** the one and operate the one at the same time；后来想到[time of checker to time of use](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use)，显然TOCTTOU中的race并不是operate the one  at the same time，所以operate the one at the same time的这个限制是太过于局限的；后来参考Wikipedia中的内容修改为上述形式；除了TOCTTOU，还有一种情况就是在APUE的10.6 Reentrant Functions中提及的，这种情况中，many也没有operate the one at the same time，但是依然发生了race；

many可能是many threads，many process，也可能是 [different ends of the same network](https://en.wikipedia.org/wiki/Race_condition#Networking)，是一切可以operate the one的computing entity；

the one是many 可以 operate的target，它可能是一个variable，file，也可能是一种抽象的[privilege](https://en.wikipedia.org/wiki/Race_condition#Networking)；

需要注意的是：many对the one的operate可能at the same time，也可能前后发生；

通过上述总结可以看出，会出现race condition的情况是非常之多的；

race condition可能发生于application内部：

- application内部的多个computing entity operate the one in a uncontrollable sequence or time；如在application内部使用了thread pool，process pool；
- 在APUE 的10.6 Reentrant Functions章节介绍的；在这种情况下，application并没有使用thread pool，process pool，但是依然存在race，在这种情况下， many所指为对async-signal unsafe function（或者称之为**unreentrant** function，注意它不是只的signal handler）的[re-enter](https://en.wikipedia.org/wiki/Reentrancy_(computing))（重入），the one则指async-signal unsafe function中使用到的data structure；

也可能发生于application与OS 中的其他application之间，即OS中的多个不同computing entity operate the one in a uncontrollable sequence or time，这种情况最最典型的就是[time of checker to time of use](https://en.wikipedia.org/wiki/Time_of_check_to_time_of_use) ；

也可能发生于network的不同end之间，这种情况在Wikipedia的[Race condition](https://en.wikipedia.org/wiki/Race_condition) 的[Networking](https://en.wikipedia.org/wiki/Race_condition#Networking)章节中有一个非常好的例子；



为避免race condition可能造成的不良后果，computer science中有各种各样的应对方法；programmer应该根据avoid race 发生的范围采取合适的方法 to avoid it；现在看来，avoid race condition的各种方法的本质是避免many对the one的以uncontrollable sequence进行operate，而是让many对the one的operate以controllable sequence；比如在[Wikipedia Race condition](https://en.wikipedia.org/wiki/Race_condition)的[example](https://en.wikipedia.org/wiki/Race_condition#Example)中，通过 [mutually exclusive](https://en.wikipedia.org/wiki/Mutually_exclusive) 来避免这种会造成错误的操作方式；当然有些情况下的race condition是通过OS提供的各种方法是无法avoid，比如在APUE 的10.6 Reentrant Functions章节介绍的情况，这种情况下，就只有不使用这些async-signal unsafe function才能够彻底规避；

思考:原子操作有哪些优良性质



哪些情况下会出现重入？
– 调用signal handler，而中断正在执行的函数，在signal handler中调用与被中断函数相同的函数，这就是重入
– 多个线程在相同的时刻，调用同一个函数

12.5节对线程安全函数和异步信号安全函数进行了非常好的比较。显然两种安全的定义都和重入有关，都是指在发生重入的时候





## race condition and reentrant function



## reentrant  and async-signal safe and thread-safe

APUE 12.5 Reentrancy给出的definition如下：

> If a function is **reentrant** with respect to multiple threads, we say that it is ***thread-safe***. This doesn’t tell us, however, whether the function is reentrant with respect to signal handlers. We say that a function that is safe to be reentered from an asynchronous signal handler is ***async-signal safe***. We saw the async-signal safe functions in Figure 10.4 when we discussed reentrant functions in Section 10.6.



APUE 10.6 Reentrant Functions给出的definition如下：

> The Single UNIX Specification specifies the functions that are guaranteed to be safe to call from within a signal handler. These functions are reentrant and are called ***async-signal safe*** by the Single UNIX Specification. Besides being reentrant, they block any signals during operation if delivery of a signal might cause inconsistencies.



在Wikipedia的[Reentrancy (computing)](https://en.wikipedia.org/wiki/Reentrancy_(computing))中讨论了Reentrancy 和 [thread-safety](https://en.wikipedia.org/wiki/Thread-safety) 