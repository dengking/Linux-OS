# `SO_REUSEADDR` and `SO_REUSEPORT` 

发展历程:

`SO_REUSEADDR` 早于 `SO_REUSEPORT` ，关于这一点，参见 lwn [The SO_REUSEPORT socket option](https://lwn.net/Articles/542629/) 

参考文章:

一、lwn [The SO_REUSEPORT socket option](https://lwn.net/Articles/542629/) 

其中从发展的角度描述了引入 `SO_REUSEPORT`  的原因:

1、避免 port hijacking(劫持)

2、均衡分布、负载均衡

二、idea.popcoun [Bind before connect](https://idea.popcount.org/2014-04-03-bind-before-connect/)



下面是我的一些总结:

`SO_REUSEADDR` 作用于 TCP connection

`SO_REUSEPORT` 作用于 port



