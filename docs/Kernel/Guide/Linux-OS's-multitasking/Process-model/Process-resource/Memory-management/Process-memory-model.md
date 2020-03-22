# Process model: memory model

本章的内容是主要源自龙书的[Chapter 7 Run-Time Environments](https://dengking.github.io/compiler-principle/Chapter-7-Run-Time-Environments/)，原文内容是非常好的，为我们清晰地勾画出了process的memory、runtime的concept model。

龙书，OS书、维基百科

逻辑与实现。

龙书正如其名，它所述的是原理，所以它所讲述的是概念模型。

stack是process活动的场所，所以它是memory management的关键所在。



往更加宽泛来所，其实是application binary interface，因为programing language的很多东西最终都需要翻译为指令，而application binary interface则是这类场景的总体描述。


函数调用对应的是JMP指令，那声明一个`int`类型的变量对应的是什么指令呢？与此类似的一个问题是：函数调用的时候，需要分配栈空间，那这是如何实现的？

push 指令就可以实现

process在运行过程中的主要活动其实就是不断地函数调用，所以搞清楚函数调用的过程对理解process是非常重要的。龙书的chapter 7就是介绍此的非常好的内容。这些内容我觉得全部都整理到OS book中去。



## [Program memory](https://en.wikipedia.org/wiki/Data_segment#Program_memory)



## [Data segment](https://en.wikipedia.org/wiki/Data_segment)

## [Code segment](https://en.wikipedia.org/wiki/Code_segment)



# 描述与实现

recursive definition

model