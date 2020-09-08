# Function

## cnblogs [gdb命令调试技巧](https://www.cnblogs.com/Forever-Kenlen-Ja/p/8631663.html)

1、列出函数的名字`(gdb) info functions`

2、是否进入待调试信息的函数(gdb)step s
3、进入不带调试信息的函数(gdb)set step-mode on
4、退出正在调试的函数(gdb)return expression 或者 (gdb)finish
5、直接执行函数(gdb)start 函数名 call函数名
6、打印函数堆栈帧信息(gdb)info frame or i frame
7、查看函数寄存器信息(gdb)i registers
8、查看函数反汇编代码(gdb)disassemble func
9、打印尾调用堆栈帧信息(gdb)set debug entry-values 1
10、选择函数堆栈帧(gdb)frame n
11、向上或向下切换函数堆栈帧(gdb)up n down n

## gdb onlinedocs [17 Altering Execution](https://sourceware.org/gdb/onlinedocs/gdb/Altering.html#Altering)



## Call function in gdb

- stackoverflow [How to evaluate functions in GDB?](https://stackoverflow.com/questions/1354731/how-to-evaluate-functions-in-gdb)
- aixxe [Loading, unloading & reloading shared libraries.](https://aixxe.net/2016/09/shared-library-injection) Using dynamic linker functions to load, unload and reload our code into a process.