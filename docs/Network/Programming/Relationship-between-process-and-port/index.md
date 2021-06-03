# Relationship between process and port

应该从**关系代数**的角度来看待这个问题：

process 和 port，两者之间参与关系的可能方式有：

1、一个process可以有bind多个port

2、一个port可以被多个process bind

这就好比在数据库系统设计中经常出现的：人和爱好的关系：

1、一个人可以有多个爱好

2、一个爱好可以被多个人拥有，或者说多个人同时拥有同一个爱好

这种关系在数据库设计中我们常常会使用一张表来存储这种关系，所以我想，在OS kernel中，也应该有一个专门的data structure来存储这个结构。

## stackexchange [Bind one process to multiple ports?](https://unix.stackexchange.com/questions/128677/bind-one-process-to-multiple-ports)



## stackoverflow [Listen to multiple ports from one server](https://stackoverflow.com/questions/15560336/listen-to-multiple-ports-from-one-server)





## [select(2)](https://linux.die.net/man/2/select)





## stackoverflow [Binding multiple times to the same port](https://stackoverflow.com/questions/3695978/binding-multiple-times-to-the-same-port)



## superuser [Multiple processes listening on the same port; how is it possible?](https://superuser.com/questions/1267192/multiple-processes-listening-on-the-same-port-how-is-it-possible)





## stackoverflow [Can two applications listen to the same port?](https://stackoverflow.com/questions/1694144/can-two-applications-listen-to-the-same-port)