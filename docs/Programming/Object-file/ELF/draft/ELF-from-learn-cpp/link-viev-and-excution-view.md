# 20180318
原文如下:
>Object files participate in program linking (building a program) and program execution (running a program). For convenience and efficiency, the object file format provides parallel
views of a file's contents, reflecting the differing needs of these activities. Figure 1-1 shows an object file's organization.

我现在看到这段话，我的第一想法是：为什么要提供这两种view？是否是生成的relocatable file采用的是linking view，而shared object file和executable file采用的是execution view？

这个问题是需要好好地进行分析的。

还有，如何区分一个文件到底采用的是linking view还是execution view呢？

刚刚参阅了下面这个文章：https://www.cnblogs.com/LiuYanYGZ/p/5574602.html

这篇文章中的这段话就正好解答了我的疑问：
```
所以，基本上，图中左边的部分（linking view）表示的是可重定位对象文件的格式；而右边部分（execution view）表示的则是可执行文件以及可被共享的对象文件的格式。
```

显然，可执行文件和可被共享文件是需要以可重定位文件为基础进行生成的，这个过程是需要搞清楚的，我觉得这个过程是涉及一下关联的：
1. section如何转换为segment
