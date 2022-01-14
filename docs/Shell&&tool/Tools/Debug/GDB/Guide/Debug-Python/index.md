# gdb debug Python



## 通过attach 来实现

在ipython中以交互式的方式来运行。



## 直接调试

```C++
gdb --args python signal_test.py
```

TODO

1、[Debugging: stepping through Python script using gdb?](https://stackoverflow.com/questions/7412708/debugging-stepping-through-python-script-using-gdb) # [A](https://stackoverflow.com/a/7920256/10173843)

奇技淫巧

2、python [DebuggingWithGdb](https://wiki.python.org/moin/DebuggingWithGdb)

## Debugging Python C extensions with GDB

其实可以按照调试shared library的方式来实现

redhat [Debugging Python C extensions with GDB](https://developers.redhat.com/articles/2021/09/08/debugging-python-c-extensions-gdb#)

