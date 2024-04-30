# [Brendan D. Gregg](http://www.brendangregg.com/index.html)



## Flame Graphs

> NOTE:
>
> 一、火焰图
>
> 往宽泛地说，flame graph可以用于展示hierarchical data(典型的例子: file system、call tree，它对应的是contain relation)，理解flame graph的原理的最好的例子是: [Where has my disk space gone? Flame graphs for file systems](https://www.brendangregg.com/blog/2017-02-05/file-system-flame-graph.html):
>
> - 使用flame graph非常好地实现了"a big picture view of space by directories, subdirectories, and so on"
> - In this case, width corresponds to total size ==> 不同类型(file size、memory、CPU)的flame graph，显然它的width的含义就不同不同
> - flame graph中，底部对应的是parent，顶部对应的是children
> - flame graph是对一个rooted tree的一种可视化方式，每个tree node的value对应着一个指标，value决定了width
>
> call tree是非常典型的hierarchical data，显然它可以使用flame graph来进行展示、分析。
>
> call tree: 
>
> stack trace: 堆栈跟踪
>
> codepath: 代码路径
>
> 显然它就可以展示stack trace。
>
> stack trace
>
> 越宽，则出现指标越高
>
> 有不同类型的flame graph，显然profiler
>
> 函数调用次数，还是
>
> 绘制、统计方法？
>
> 



### Summary

The x-axis shows the stack profile population, sorted alphabetically(按照字母排序地) (it is not the passage(流逝) of time), and the y-axis shows stack depth, counting from zero at the bottom. Each rectangle represents a stack frame. The wider a frame is is, the more often it was present in the stacks. The top edge shows what is on-CPU, and beneath it is its ancestry(祖先). Original flame graphs use random colors to help visually differentiate adjacent frames. Variations include inverting the y-axis (an "icicle graph"(冰柱图)), changing the hue(色调) to indicate code type, and using a color spectrum to convey an additional dimension.

> NOTE:
>
> 一、"population"如何理解？
>
> 二、The wider a frame is is, the more often it was present in the stacks.