# iproute2

是在阅读wikipedia [netstat](https://en.wikipedia.org/wiki/Netstat)时，发现的iproute2。

## wikipedia [iproute2](https://en.wikipedia.org/wiki/Iproute2)

iproute2 collection contains the following [command-line utilities](https://en.wikipedia.org/wiki/Command-line_utilities): 

*ip*, *ss*, *bridge*, *rtacct*, *rtmon*, *tc*, *ctstat*, *lnstat*, *nstat*, *routef*, *routel*, *rtstat*, *tipc*, *arpd* and *devlink*.[[3\]](https://en.wikipedia.org/wiki/Iproute2#cite_note-3) *[tc](https://en.wikipedia.org/wiki/Tc_(Linux))* is used for [traffic control](https://en.wikipedia.org/wiki/Network_traffic_control). 

iproute2 utilities communicate with the Linux kernel using the [netlink](https://en.wikipedia.org/wiki/Netlink) protocol. 

Some of the iproute2 utilities are often recommended over now-obsolete *net-tools* utilities that provide the same functionality.[[4\]](https://en.wikipedia.org/wiki/Iproute2#cite_note-4)[[5\]](https://en.wikipedia.org/wiki/Iproute2#cite_note-5) 



## `ss`



### [ss(8) - Linux man page](https://linux.die.net/man/8/ss)



**ss** is used to dump socket statistics. It allows showing information similar to *netstat*. It can display more TCP and **state** informations than other tools.

> NOTE: 看了一下，这个command的一个优势它能够让我们查看TCP的底层实现信息，比如state、socket table等。





### Example

TODO tecmint [12 ss Command Examples to Monitor Network Connections](https://www.tecmint.com/ss-command-examples-in-linux/)