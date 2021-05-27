# Linux kernel thread



## stackoverflow [How to bind certain kernel threads to a given core?](https://stackoverflow.com/questions/25450223/how-to-bind-certain-kernel-threads-to-a-given-core)



**A**

Several kernel threads are tied to a specific core, in order to effect capabilities needed by the SMP infrastructure, such as synchronization, interrupt handling and so on. The `kworker`, `migration` and `ksoftirqd` threads, for example, usually have one instance per virtual processor (e.g. 8 threads on a 4-core 8-thread CPU).

You cannot (and should not be able to) move those threads - without them that processor would not be fully usable by the system any more.

Why *exactly* do you want to move those threads anyway?