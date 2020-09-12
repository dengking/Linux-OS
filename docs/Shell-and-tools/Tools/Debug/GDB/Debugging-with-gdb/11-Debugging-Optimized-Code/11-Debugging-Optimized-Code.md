# Debugging Optimized Code

在使用gdb调试一个C++ member function的时候，按照`GDB\Guide\Cpp.md#Breakpoint for member functions`中描述的方法，竟然无法找到对应的member function。这让我感到奇怪，于是Google: why an existing member function can not be break in gdb，文章stackoverflow [Set breakpoint for class member function not successful](https://stackoverflow.com/questions/6892395/set-breakpoint-for-class-member-function-not-successful)描述的情况与我们的情况相同，原来是compiler optimization的缘故，compiler inline了这个函数，所以无法找到对应的definition，后来我核实了我的Makefile：

```makefile
EXTRA_CFLAGS := -g -pthread -c -fPIC -O2 
```

确实开启了`O2`优化，后来我将optimization关闭，再次进行调试，可以能够找到对应的function。

## gdb onlinedocs[11 Debugging Optimized Code](https://sourceware.org/gdb/current/onlinedocs/gdb/Optimized-Code.html#Optimized-Code)

### [11.1 Inline Functions](https://sourceware.org/gdb/current/onlinedocs/gdb/Inline-Functions.html)

`info frame`

TO READ:

- stackoverflow [Set breakpoint for class member function not successful](https://stackoverflow.com/questions/6892395/set-breakpoint-for-class-member-function-not-successful)

  