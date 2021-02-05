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


