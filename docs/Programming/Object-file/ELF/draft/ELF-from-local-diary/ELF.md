# [可执行文件（ELF）格式的理解](http://www.cnblogs.com/xmphoenix/archive/2011/10/23/2221879.html) 

ELF(Executable and Linking Format)是一种对象文件的格式，用于定义不同类型的对象文件(Object files)中都放了什么东西、以及都以什么样的格式去放这些东西。它自最早在 System V 系统上出现后，被 xNIX 世界所广泛接受，作为缺省的二进制文件格式来使用。可以说，ELF是构成众多xNIX系统的基础之一，所以作为嵌入式Linux系统乃至内核驱动程序开发人员，你最好熟悉并掌握它。

其实，关于ELF这个主题，网络上已经有相当多的文章存在，但是其介绍的内容比较分散，使得初学者不太容易从中得到一个系统性的认识。为了帮助大家学习，我这里打算写一系列连贯的文章来介绍ELF以及相关的应用。这是这个系列中的第一篇文章，主要是通过不同工具的使用来熟悉ELF文件的内部结构以及相关的基本概念。后面的文章，我们会介绍很多高级的概念和应用，比方动态链接和加载，动态库的开发，C语言Main函数是被谁以及如何被调用的，ELF格式在内核中的支持，Linux内核中对ELF section的扩展使用等等。

好的，开始我们的第一篇文章。在详细进入正题之前，先给大家介绍一点ELF文件格式的参考资料。在ELF格式出来之后，TISC(Tool Interface Standard Committee)委员会定义了一套ELF标准。你可以从这里(http://refspecs.freestandards.org/elf/)找到详细的标准文档。TISC委员会前后出了两个版本，v1.1和v1.2。两个版本内容上差不多，但就可读性上来讲，我还是推荐你读 v1.2的。因为在v1.2版本中，TISC重新组织原本在v1.1版本中的内容，将它们分成为三个部分(books)：

a) Book I

介绍了通用的适用于所有32位架构处理器的ELF相关内容

b) Book II

介绍了处理器特定的ELF相关内容，这里是以Intel x86 架构处理器作为例子介绍

c) Book III

介绍了操作系统特定的ELF相关内容，这里是以运行在x86上面的 UNIX System V.4 作为例子介绍

值得一说的是，虽然TISC是以x86为例子介绍ELF规范的，但是如果你是想知道非x86下面的ELF实现情况，那也可以在http://refspecs.freestandards.org/elf/中找到特定处理器相关的Supplment文档。比方ARM相关的，或者MIPS相关的等等。另外，相比较UNIX系统的另外一个分支BSD Unix，Linux系统更靠近 System V 系统。所以关于操作系统特定的ELF内容，你可以直接参考v1.2标准中的内容。

这里多说些废话：别忘了 Linus 在实现Linux的第一个版本的时候，就是看了介绍Unix内部细节的书：《The of the Unix Operating System》，得到很多启发。这本书对应的操作系统是System V 的第二个Release。这本书介绍了操作系统的很多设计观念，并且行文简单易懂。所以虽然现在的Linux也吸取了其他很多Unix变种的设计理念，但是如果你想研究学习Linux内核，那还是以看这本书作为开始为好。这本书也是我在接触Linux内核之前所看的第一本介绍操作系统的书，所以我极力向大家推荐。

好了，还是回来开始我们第一篇ELF主题相关的文章吧。这篇文章主要是通过使用不同的工具来分析对象文件，来使你掌握ELF文件的基本格式，以及了解相关的基本概念。你在读这篇文章的时候，希望你在电脑上已经打开了那个 v1.2 版本的ELF规范，并对照着文章内容看规范里的文字。

## Object files分类

首先，你需要知道的是所谓对象文件(Object files)有三个种类：

### Relocatable file

这是由**汇编器**汇编生成的 .o 文件（参见[linux下编译的步骤](https://github.com/dengking/learn-cpp/blob/master/compile-and-link-error/step-of-compile/step-of-compile-in-linux.md) ）。后面的链接器(link editor)拿一个或一些 Relocatable object files 作为输入，经链接处理后，生成一个**可执行的对象文件 (Executable file)** 或者一个**可被共享的对象文件(Shared object  file)**。我们可以使用 **ar 工具**将众多的 .o Relocatable object files 归档(archive)成 .a 静态库文件。如何产生 Relocatable file，你应该很熟悉了。另外，可以预先告诉大家的是我们的内核可加载模块 .ko 文件也是 Relocatable object file。

### Executable file

可执行的对象文件，这我们见的多了。文本编辑器vi、调式用的工具gdb、播放mp3歌曲的软件mplayer等等都是Executable object file。你应该已经知道，在我们的 Linux 系统里面，存在两种可执行的东西。除了这里说的 Executable object file，另外一种就是可执行的脚本(如shell脚本)。注意这些脚本不是 Executable object file，它们只是文本文件，但是执行这些脚本所用的解释器就是 Executable object file，比如 bash shell 程序。

### Shared object file

可被共享的对象文件就是所谓的**动态库文件**，也即 .so 文件。如果拿前面的**静态库**来生成可执行程序，那每个生成的**可执行程序**中都会有一份库代码的拷贝。如果在磁盘中存储这些可执行程序，那就会占用额外的磁盘空间；另外如果拿它们放到Linux系统上一起运行，也会浪费掉宝贵的物理内存。如果将静态库换成动态库，那么这些问题都不会出现。动态库在发挥作用的过程中，必须经过两个步骤：

a) 链接编辑器(link editor，即linux中的ld程序)拿它和其他Relocatable object file以及其他shared object file作为输入，经链接处理后，生存另外的 shared object file 或者 executable file。

b) 在运行时，动态链接器(dynamic linker)拿它和一个Executable file以及另外一些 Shared object file 来一起处理，在Linux系统里面创建一个进程映像。