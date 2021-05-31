# Race condition 

APUE的下列章节包含了race condition相关的内容：

- 8.9  Race Conditions
- 11.6 Thread Synchronization
- 3.10 File Sharing
- 3.11 Atomic Operations
- 3.3 `open` and `openat` Functions  time-of-check-to-time-of-use 

- 12.5 Reentrancy
- 10.6 Reentrant Functions



## 8.9  Race Conditions

For our purposes, a **race condition** occurs when multiple processes are trying to do something with **shared data** and the final outcome depends on the order in which the processes run. The `fork` function is a lively breeding ground for **race conditions**, if any of the logic after the `fork` either explicitly or implicitly depends on whether the parent or child runs first after the `fork`. In general, we cannot predict which process runs first. Even if we knew which process would run first, what happens after that process starts running depends on the system **load** and the kernel’s **scheduling algorithm**.







首先需要把握race condition的本质：many to one。在multiple thread环境中，显然many所指为many thread，而the one所指则是全局变量。

posix和std c++的thread library中，使用thread的时候需要传入`start_rtn`函数，然后thread来执行这个`start_rtn`函数。每个thread都是有自己的stack的，是彼此分隔的，所以thread的stack是不存在竞争的，也就是在thread的stack上的variable是安全的，这意味着，如果`start_rtn`中定义了local variable `i`，并且执行了`++i`操作，这是不存在race condition的。但是，如果在`start_rtn`中对全局变量执行了`++i`操作，则这是存在race condition的。
