# 20190126linux内核是如何来组织process的

今天在阅读[Separation Anxiety: A Tutorial for Isolating Your System with Linux Namespaces](https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces)这篇文章的时候，其中一段话：

> Historically, the Linux kernel has maintained a single process tree. The tree contains a reference to every process currently running in a parent-child hierarchy. A process, given it has sufficient privileges and satisfies certain conditions, can inspect another process by attaching a tracer to it or may even be able to kill it.

这段话引起了我的思考：在linux的内核中，是使用tree来按照parent-child关系来组织process的吗？

刚开始的时候，我觉得应该是这样的，因为[ptree](https://en.wikipedia.org/wiki/Pstree)，显然按照parent-child关系是可以按照tree结构来组织process的，但是实际的实现要远比这复杂，因为除此之外，还需要考虑的问题有：

- schedule，即调度问题，内核需要进行高效地调度，所以对process的组织就非常重要



下面是一些参考内容：

- [The Linux Kernel/Processing](https://en.wikibooks.org/wiki/The_Linux_Kernel/Processing)
- [Traverse the Process Tree](https://unix.stackexchange.com/questions/200402/traverse-the-process-tree)
- [Process management](https://myaut.github.io/dtrace-stap-book/kernel/proc.html)
- [Scheduling (computing)](https://en.wikipedia.org/wiki/Scheduling_(computing))
- [Completely Fair Scheduler](https://en.wikipedia.org/wiki/Completely_Fair_Scheduler)
- [The Linux process tree](https://www.usenix.org/legacy/publications/library/proceedings/usenix03/tech/freenix03/full_papers/appavoo/appavoo_html/node8.html)

