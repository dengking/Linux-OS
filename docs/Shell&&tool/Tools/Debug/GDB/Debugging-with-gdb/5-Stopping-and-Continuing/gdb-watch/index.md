# GDB-watch：监控变量值的变化
在阅读 zhihu [用std::once_flag来std::call_once，运行时却执行了2次？](https://zhuanlan.zhihu.com/p/408838350) 时，其中介绍了

> **其次单步调试，重点关注静态变量的初始化**
>
> 1、在`gInitFlag`上打断点，添加监视，观察值第一次改变的时机。
>
> 2、在`gInitFlag`值第一次被修改后，设置改变时自动触发中断。
>
> 3、继续运行，触发断点，查看调用堆栈，提示执行了dynamic initializer。
>
> ![img](https://pic3.zhimg.com/80/v2-f2f1be7ff121ffb03432b9465b6774e2_720w.jpg)
>
> ![img](https://pic4.zhimg.com/80/v2-aaf7b3d4cd97c976aecacb3fd878fbdf_720w.jpg)
>
> ![img](https://pic3.zhimg.com/80/v2-6d28f3010c07881476db3374029f8b76_720w.jpg)

显然这是非常典型的一种使用GDB watch的场景。

## biancheng [GDB watch命令：监控变量值的变化](http://m.biancheng.net/view/8191.html)



要知道，GDB 调试器支持在程序中打 3 种断点，分别为

1、普通断点

2、观察断点

3、捕捉断点。

其中 break 命令打的就是普通断点，而 watch 命令打的为观察断点，关于捕捉断点，后续章节会做详细讲解。

> NOTE: 
>
> 本质上都是让程序在特定情况下停止下来

使用 GDB 调试程序的过程中，借助观察断点可以监控程序中某个变量或者表达式的值，只要发生改变，程序就会停止执行。相比普通断点，观察断点不需要我们预测变量（表达式）值发生改变的具体位置。