# 关于本章

本章讨论reentrancy，在下面章节中，也对这个topic进行了讨论:

1、`programming-language\docs\C++\Resource-management\Memory\Dynamic-allocation\new-operator\Thread-safety-Reentrancy`

2、`programming-language\docs\C++\Resource-management\Memory\Dynamic-allocation\malloc\Thread-safety-Reentrancy`



## Reentrancy is a form of concurrency-race condition

典型的例子是：函数在执行过程中，以不可预知的方式被interrupt，然后该函数又再次被执行，这样就可能发生race。

参见: 

1、`Parallel-computing\docs\Concurrent-computing\Multithread\Thread-safety\What-cause-unsafety\Race`

2、drdobbs [Use Lock Hierarchies to Avoid Deadlock](https://www.drdobbs.com/parallel/use-lock-hierarchies-to-avoid-deadlock/204801163)  

## TODO

microchip [Sharing global variables with multiple Interrupt Service Routines](https://www.microchip.com/forums/m921817.aspx)

https://www.gnu.org/software/libc/manual/html_node/Nonreentrancy.html