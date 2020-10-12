# bss

.bss

 This section holds uninitialized data that contribute to the program's memory image. By definition, the system initializes the data with zeros when the program begins to run. The section occupies no file space, as indicated by the section type,  SHT_NOBITS .

我的疑惑是：

1. 在程序中，我们会在全局定义全局变量，在函数内定义局部变量，是否所有这些未初始化的变量都保存在这个section中。同样的，对于data段也是如此。

#data

.data and  .data1 

These sections hold initialized data that contribute to the program's memory image.

我的疑问是：

1. 这些初始化过的变量，在这个section中是如何保存的

   ​