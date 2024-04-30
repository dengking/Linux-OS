# [Brendan D. Gregg](http://www.brendangregg.com/index.html)

关于他的一些介绍:

[zhihu-BPF 拓荒者 —— Brendan Gregg 与 Netflix 的故事](https://zhuanlan.zhihu.com/p/516548884) 



内容分类:

- methodology 方法论

- visualization  可视化



## [The USE Method](https://www.brendangregg.com/usemethod.html) 

> NOTE:
>
> 一、下面文章对USE的介绍也非常好:
>
> 1. thenewstack [Monitoring Methodologies: RED and USE](https://thenewstack.io/monitoring-methodologies-red-and-use/) 
> 2. orangematter [Monitoring and Observability With USE and RED](https://orangematter.solarwinds.com/2017/10/05/monitoring-and-observability-with-use-and-red/) 

The **Utilization Saturation and Errors (USE) Method** is a methodology for analyzing the performance of any system. It directs the construction of a checklist, which for server analysis can be used for quickly identifying **resource bottlenecks** or **errors**. It begins by posing questions, and then seeks answers, instead of beginning with given metrics (partial answers) and trying to work backwards.

> NOTE:
>
> 一、
>
> Utilization 利用率
>
> Saturation 饱和度
>
> Error 误差
>
> 二、完整翻译如下:
>
> 利用饱和度和误差(USE)方法是一种分析任何系统性能的方法。它指导了检查表的构造，用于服务器分析的检查表可用于快速识别资源瓶颈或错误。它从提出问题开始，然后寻求答案，而不是从给定的指标(部分答案)开始，然后试图向后工作。
>
> 三、寻找出资源瓶颈，这就取决于如何解释这些指标，在"Suggested Interpretations"章节中进行了介绍。



### Intro

Getting started can be the hardest part. I developed the USE Method to teach others how to solve common performance issues quickly, without overlooking(忽视掉) important areas.



### Summary

The USE Method can be summarized as:

> **For every resource, check utilization, saturation, and errors.**

It's intended to be used early in a performance investigation, to identify systemic bottlenecks.

Terminology definitions:

**resource**: 

all physical server functional components (CPUs, disks, busses, ...) [1]

> NOTE:
>
> 一、物理服务器的功能性组件，其实就是hardware resource。

[1] It can be useful to consider some **software resources** as well, or **software imposed limits** (resource controls), and see which metrics are possible.

> NOTE:
>
> 一、上面这段话提到了 software resources，显然software resource是相对于hardware resource而言的，在后面的"Software Resources"章节对此进行了详细的说明。
>
> 比如JVM的最大memory limit: `-Xmx30g`

**utilization**: 

the average time that the resource was busy servicing work [2]

[2] There is another definition where utilization describes the proportion of a resource that is used, and so 100% utilization means no more work can be accepted, unlike with the "busy" definition above.

> NOTE:
>
> 一、注释中的解释是更加容易理解的

The metric is usually expressed in the following terms:

> as a percent over a time interval. eg, "one disk is running at 90% utilization".

**saturation**: 

the degree to which the resource has extra work which it can't service, often queued

> NOTE:
>
> 一、表面意思: "资源有无法服务的额外工作的程度，通常是排队的"，下面给出两个其它的描述来揭示它的含义:
>
> 1. 在"Does Low Utilization Mean No Saturation?"章节中，使用 latency 来进行描述
>
> 2. 在 orangematter [Monitoring and Observability With USE and RED](https://orangematter.solarwinds.com/2017/10/05/monitoring-and-observability-with-use-and-red/) 中:
>
>    > This disambiguates **utilization** and **saturation**, making it clear utilization is “busy time %” and saturation is “backlog.”(积压的工作) These terms are very different from things a person might confuse with them, such as “disk utilization” as an expression of how much disk space is left.
>
>    显然，queue意味着backlog
>
> 3. utilization VS saturation
>
>    在 thenewstack [Monitoring Methodologies: RED and USE](https://thenewstack.io/monitoring-methodologies-red-and-use/) 中，有如下描述:
>
>    > ### **Utilization**
>    >
>    > Utilization refers to the number of resources a system is using to process work. This could be CPU, memory, network bandwidth or even software metrics like process capacity and thread pools. Having visibility into your system architecture is important when monitoring utilization. Each step in a service flow requires and uses system resources; if these resources are unavailable, your applications could stop running or encounter problems.
>    >
>    > ### **Saturation**
>    >
>    > Saturation is the amount of work that cannot be processed by the system due to a lack of available resources, similar to a backlog. Saturation can often be observed as queuing or latency and can lead to work erroring out. Ideally, your system has high utilization and low saturation, allowing for new work to be accepted and processed.
>
> 4. 理想状态？
>
>    thenewstack [Monitoring Methodologies: RED and USE](https://thenewstack.io/monitoring-methodologies-red-and-use/) 
>
>    > Ideally, your system has high utilization and low saturation

The metric is usually expressed in the following terms:

> as a queue length. eg, "the CPUs have an average run queue length of four".

**errors**: 

the count of error events

The metric is usually expressed in the following terms:

> scalar counts. eg, "this network interface has had fifty late collisions".



### Does Low Utilization Mean No Saturation?

> NOTE:
>
> 一、标题的含义是: 是否低利用率意味着不饱和？但是是否，作者列举的一种case是: 
>
> "A burst of high utilization can cause saturation and performance issues, even though utilization is *low* when averaged over a long interval. "
>
> 是否只需要看 saturation？

A burst of high utilization can cause saturation and performance issues, even though utilization is *low* when averaged over a long interval. This may be counter-intuitive!

I had an example where a customer had problems with **CPU saturation** (latency) even though their monitoring tools showed CPU utilization was never higher than 80%. The monitoring tool was reporting five minute averages, during which CPU utilization hit 100% for seconds at a time.



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

|                                                              | Full name                                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [CPU](https://www.brendangregg.com/FlameGraphs/cpuflamegraphs.html) | [CPU Flame Graphs](https://www.brendangregg.com/FlameGraphs/cpuflamegraphs.html) |
| [Memory](https://www.brendangregg.com/FlameGraphs/memoryflamegraphs.html) | [Memory Leak (and Growth) Flame Graphs](https://www.brendangregg.com/FlameGraphs/memoryflamegraphs.html) |
| [Off-CPU](https://www.brendangregg.com/FlameGraphs/offcpuflamegraphs.html) | [Off-CPU Flame Graphs](https://www.brendangregg.com/FlameGraphs/offcpuflamegraphs.html) |
| [Hot/Cold](https://www.brendangregg.com/FlameGraphs/hotcoldflamegraphs.html) | [Hot/Cold Flame Graphs](https://www.brendangregg.com/FlameGraphs/hotcoldflamegraphs.html) |
| [Differential](https://www.brendangregg.com/blog/2014-11-09/differential-flame-graphs.html) | [Differential Flame Graphs](https://www.brendangregg.com/blog/2014-11-09/differential-flame-graphs.html) |



## [Heat Maps](https://www.brendangregg.com/heatmaps.html)

Heat maps allow three dimensions of data to be visualized, similar to weather radar maps where color is used as a dimension. As data is quantized into buckets, they are practical for handling large datasets, such as performance monitoring metrics across thousands of servers.

> NOTE:
>
> 一、heap map能够在two  dimensions中展示three dimensions of data，它的手段是: "color is used as a dimension"