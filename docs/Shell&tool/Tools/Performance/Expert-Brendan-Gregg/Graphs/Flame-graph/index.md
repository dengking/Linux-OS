# Flame graph

## [Flame Graphs](https://www.brendangregg.com/flamegraphs.html)

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
> [activations/ call tree](https://www.eecis.udel.edu/~pollock/672/f15/Classes/18LP-week9-runtime-environ-codegen.pdf): 调用树
> 
> stack trace: 堆栈跟踪
> 
> codepath: 代码路径
> 
> 二、在ACMQ上的文章: ACMQ article [The Flame Graph](http://queue.acm.org/detail.cfm?id=2927301)
> 
> 三、从 这篇文章的内容可知，flame graph是由作者发明的:
> 
> > I invented flame graphs when working on a MySQL performance issue and needed to understand CPU usage quickly and in depth.

The following pages (or posts) introduce different types of flame graphs:

|                                                                                             | Full name                                                                                                |
| ------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| [CPU](https://www.brendangregg.com/FlameGraphs/cpuflamegraphs.html)                         | [CPU Flame Graphs](https://www.brendangregg.com/FlameGraphs/cpuflamegraphs.html)                         |
| [Memory](https://www.brendangregg.com/FlameGraphs/memoryflamegraphs.html)                   | [Memory Leak (and Growth) Flame Graphs](https://www.brendangregg.com/FlameGraphs/memoryflamegraphs.html) |
| [Off-CPU](https://www.brendangregg.com/FlameGraphs/offcpuflamegraphs.html)                  | [Off-CPU Flame Graphs](https://www.brendangregg.com/FlameGraphs/offcpuflamegraphs.html)                  |
| [Hot/Cold](https://www.brendangregg.com/FlameGraphs/hotcoldflamegraphs.html)                | [Hot/Cold Flame Graphs](https://www.brendangregg.com/FlameGraphs/hotcoldflamegraphs.html)                |
| [Differential](https://www.brendangregg.com/blog/2014-11-09/differential-flame-graphs.html) | [Differential Flame Graphs](https://www.brendangregg.com/blog/2014-11-09/differential-flame-graphs.html) |

## Flame graph interpretation

[netflixtechblog Java in Flames](https://netflixtechblog.com/java-in-flames-e763b3d32166)

[youtube Java Mixed-Mode Flame Graphs](https://www.youtube.com/watch?v=BHA65BqlqSk)、[brendangregg Slides Java Mixed-Mode Flame](https://www.brendangregg.com/Slides/JavaOne2015_MixedModeFlameGraphs.pdf)

## Differential Flame Graphs

差分火焰图

[Differential Flame Graphs](https://www.brendangregg.com/blog/2014-11-09/differential-flame-graphs.html)

[tencent 差分火焰图，让你的代码优化验证事半功倍](https://cloud.tencent.com/developer/article/2353831) 
