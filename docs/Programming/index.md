# 关于本章

本章主要讨论programming in Linux OS，所以主要关注的是Linux OS提供的interface。



## Interface

在理论部分，我们已经学习了Linux OS的各个层次，Linux OS在各个层次都提供了丰富的、功能完备的interface，甚至有些层次的interface的名称完全相同，这增加了用户使用的便利、降低了学习成本。

对interface的学习是掌握Linux OS的关键，在本工程中，会将command line interface放到`Tools`目录下。

| interface              | man page                                                     | 说明                                                         |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| system call            | [man(2)](http://man7.org/linux/man-pages/man2/intro.2.html)、[man(3)](http://man7.org/linux/man-pages/man3/intro.3.html) |                                                              |
| library function       |                                                              | `pthread`                                                    |
| command line interface | [man(1)](http://man7.org/linux/man-pages/man1/intro.1.html)、[man(8)](http://man7.org/linux/man-pages/man8/intro.8.html) | Linux的CLI非常强大 <br>command line interface其实也是kernel的interface |



## man

TODO: 对Linux OS的man进行介绍