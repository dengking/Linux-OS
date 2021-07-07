# `TIME_WAIT` state

一、2 `*` MSL 正好是一个来回，参见:

1、coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)

2、miami [TCP in a nutshell](https://www.cs.miami.edu/home/burt/learning/Csc524.032/notes/tcp_nutshell.html) 

二、这是一个比较特殊的状态，在下面的文章中，对它进行了描述:

1、coolshell [TCP 的那些事儿（上）](https://coolshell.cn/articles/11564.html)

其中介绍了为什么需要`TIME_WAIT` state。

三、和`TIME_WAIT`相关的socket option

1、`SO_REUSEADDR`

2、`SO_LINGER`

四、如何避免`TIME_WAIT` state过多的问题

这在 `解决TIME_WAIT过多问题` 章节中进行了讨论。

