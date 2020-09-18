现在谈起section和segment之间的关系，我的大脑中有如下印象：

1. 一个segment是由若干个section构成的，section是ELF中保存数据的最小单元
2. loadable segment是会装入到内存中的

关于它们两者的关系，可以从segment的内容谈起。

## Segment Contents

An object file segment comprises<!--包含--> one or more sections, though this fact is transparent to the program header. Whether the file segment holds one or many sections also is immaterial to
program loading. Nonetheless<!--尽管如此-->, various data must be present for program execution, dynamic linking, and so on. 

虽然说file image中的segment所包含的section的个数对program loading来说并不重要，但是，在程序执行，动态链接时候所需要的数据file image是必须要提供的。

The diagrams below illustrate segment contents in general terms. The order and membership of sections within a segment may vary; moreover, processor-specific constraints may alter the examples below.

Text segments contain read-only<!--只读--> instructions and data, typically including the following sections. Other sections may also reside in loadable segments<!--其他的section可能处于其他loadable segment中-->; these examples are not meant to give complete and exclusive segment contents.

Figure 2-4. Text Segment
![text segment](D:\mydoc\others\ELF\diary\text segment.png)

Figure 2-5. Data Segment

![data segment](D:\mydoc\others\ELF\diary\data segment.png)

A  PT_DYNAMIC  program header element points at<!--指向--> the  **.dynamic** **section**, explained in
"Dynamic Section" below. The  **.got** and  **.plt** sections also hold information related to**position-independent code** and **dynamic linking**. Although the  .plt appears in a text segment above, it may reside in a text or a data segment, depending on the processor.

As "Sections" describes, the  .bss section has the type  SHT_NOBITS . Although it occupies no
space in the file, it contributes to the segment's memory image. Normally, these uninitialized
data reside at the end of the segment, thereby making  p_memsz  larger than  p_filesz 

虽然bss section在file image中并不占空间，但是它在memory image中是占据空间的，所以p_memsz大于等于p_filesz。

## Q&A

1. 上面提到了一个segment包含一个或多个section，我的问题是，这种包含关系是如何实现的？？