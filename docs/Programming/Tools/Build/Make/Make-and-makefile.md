# Make and makefile

## Make

### 维基百科[Make (software)](https://en.wikipedia.org/wiki/Make_(software))



## Makefile

### 维基百科[Makefile](https://en.wikipedia.org/wiki/Makefile)



### Macro in makefile

#### `$@`

`$@` is a macro that refers to the target。其实这个非常好理解，`@`有指向的含义。

#### `"$$?"`

[What does “$$?” mean in this makefile snippet?](https://stackoverflow.com/questions/38591625/what-does-mean-in-this-makefile-snippet)

### makefile and  [dependency graph](https://en.wikipedia.org/wiki/Dependency_graph)

我们使用makefile本质上是描述了一张dependency graph，这张图由多个node组成，这些node之间可能存在中dependency 关系，有可能不存在。应该是可以单独访问每个node的。关于这一点，可以参见https://www.cs.princeton.edu/courses/archive/spr01/cs217/slides/5.make.pdf

另外参见

#### [makefile2graph](https://github.com/lindenb/makefile2graph)

Creates a graph of dependencies from GNU-Make; Output is a graphiz-dot file or a Gexf-XML file.



#### [Is there a tool to analyse makefiles?](https://stackoverflow.com/questions/33920654/is-there-a-tool-to-analyse-makefiles)