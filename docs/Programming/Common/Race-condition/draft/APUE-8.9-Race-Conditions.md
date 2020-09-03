# 8.9  Race Conditions

For our purposes, a **race condition** occurs when multiple processes are trying to do something with **shared data** and the final outcome depends on the order in which the processes run. The `fork` function is a lively breeding ground for **race conditions**, if any of the logic after the `fork` either explicitly or implicitly depends on whether the parent or child runs first after the `fork`. In general, we cannot predict which process runs first. Even if we knew which process would run first, what happens after that process starts running depends on the system **load** and the kernel’s **scheduling algorithm**.




# 相关

## wikipedia race condition
在本地的：
`youdao note/computer science/Computer-errors-and-security/race-condition`转换后有收录此文章 

