# what is terminal

理解chapter9.2 Terminal Logins的一个关键是知道what is terminal；在chapter 9.2中有一段话点到了关键所在：

> A host had a fixed number of these terminal devices, so there was a known upper limit on the number of simultaneous logins.



显然，标题中的***terminal***的含义是terminal device，即终端设备；显然此设备就如同computer中的很多其他设备如keyboard一般；在文章[The TTY demystified](http://www.linusakesson.net/programming/tty/index.php)对此有非常好的解释；

一个直观的理解就是：每次我们使用我们的笔记本电脑，开机后屏幕中都能够显示登录界面，我们在此登录界面中输入用户名很密码；此即terminal login；Unix中的terminal login和此是相同的；

## terminal 和 shell之间的关系？

shell将它的标准输入和标准输出都连到terminal；

