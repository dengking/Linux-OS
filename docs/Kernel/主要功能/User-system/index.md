# Linux user system

linux OS中有user、group的概念，这两个概念是linux OS中非常非常基础的概念，因为linux OS中的很多概念都是建立在这两个重要的概念之上，我们将它们称为“user system”，我目前在官方文档中还没有找到对linux OS的user system的专门介绍的文章。

linux OS中的很多其它的概念都是建立user system之上的，直接的体现就是它们都具备表示其user信息的属性，比如file、process。file的user信息表示它的所属，process的user 信息表示它是哪个user的活动。

linux OS在user system上建立起了permission system（权限系统），即表示哪些用户具备哪些permission（权限），典型的就是linux OS中的file会记录下它的permission信息，即哪些用户可以对它执行怎样的操作，具体可以参见[man 1 chmod](https://linux.die.net/man/1/chmod)，这仅仅是一个简单的例子，linux OS的permission system会涉及到非常多的内容。

> TODO: 下面记录了一些与permission system相关的内容：
>
> wikipedia [File system permissions](https://en.wikipedia.org/wiki/File_system_permissions)
>
> wikipedia [Access-control list](https://en.wikipedia.org/wiki/Access-control_list)
>
> [man 5 acl](https://linux.die.net/man/5/acl)

linux OS在user system上建立起了resource management system，即对OS中的user所占用的OS resource进行限制。

linux的user system就像是人类社会的户籍簿。

## Process and user

process可以看做是user的活动、看做是user对OS使用。



## Operation of user system

只有root用户具备操作user system的权限：

- 添加用户：[useradd(8)](https://linux.die.net/man/8/useradd)