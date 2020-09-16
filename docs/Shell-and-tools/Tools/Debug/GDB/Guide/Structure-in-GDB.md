# Structure in GDB

使用**结构化思维**来分析GDB。

## contain关系

一个gdb session可以 **contain** 多个 inferior；

一个inferior可以 **contain** 多个 thread；

一个thread有一个call stack，call stack **contain** 多个 stack frame；

通过上面的描述可知：整体形成了一个tree structure

```
                              
              
              inferior1


session
```



## 一对多关系

在使用gdb的时候，我们只有一个session，但是可能有多个inferior、多个thread、多个stack frame，显然这是一种 **一对多** 关系；

由于只有一个session，所以在使用gdb的时候，就需要涉及到current、switch and select、apply to all。

### Current 

Current inferior: [4.9 Debugging Multiple Inferiors Connections and Programs](https://sourceware.org/gdb/current/onlinedocs/gdb/Inferiors-Connections-and-Programs.html#Inferiors-Connections-and-Programs)

Current thread: [4.10 Debugging Programs with Multiple Threads](https://sourceware.org/gdb/current/onlinedocs/gdb/Threads.html#Threads)

Current stack frame: [8 Examining the Stack](https://sourceware.org/gdb/current/onlinedocs/gdb/Stack.html#Stack)

### Switch and select

Select a inferior:  [`inferior infno`](https://sourceware.org/gdb/current/onlinedocs/gdb/Inferiors-Connections-and-Programs.html#Inferiors-Connections-and-Programs) 

Select a thread: [`thread thread-id`](https://sourceware.org/gdb/current/onlinedocs/gdb/Threads.html#Threads) 

Select a frame: [8.3 Selecting a Frame](https://sourceware.org/gdb/current/onlinedocs/gdb/Selection.html#Selection)

### Apply to all

Thread: [`thread apply`](https://sourceware.org/gdb/current/onlinedocs/gdb/Threads.html#Threads)  

Stack frame: [8.5 Applying a Command to Several Frames.](https://sourceware.org/gdb/current/onlinedocs/gdb/Frame-Apply.html#Frame-Apply)