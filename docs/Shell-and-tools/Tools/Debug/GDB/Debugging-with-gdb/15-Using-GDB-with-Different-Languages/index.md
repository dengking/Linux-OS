# [15 Using GDB with Different Languages](https://sourceware.org/gdb/onlinedocs/gdb/Languages.html#Languages)

Language-specific information is built into GDB for some languages, allowing you to express operations like the above in your program’s native language, and allowing GDB to output values in a manner consistent with the syntax of your program’s native language. 

> NOTE: gdb的这个特性是非常有价值的，它让我们能够实现类似于python的interactively-programming的效果，即在gdb中输入expression，然后gdb能够evaluate、output。

