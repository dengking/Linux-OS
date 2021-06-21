# [`select`](https://www.man7.org/linux/man-pages/man2/select.2.html) VS [`poll`](https://www.man7.org/linux/man-pages/man2/poll.2.html) VS [`epoll`](https://man7.org/linux/man-pages/man7/epoll.7.html) 

## 比较

### 时间

`select` -> `poll` -> `epoll` 

### file descriptor数量限制



### portability 



`poll` is a POSIX standard interface

`epoll` is Linux-specific



### data structure of file descriptors





## select VS poll

### stackoverflow [What are the differences between poll and select?](https://stackoverflow.com/questions/970979/what-are-the-differences-between-poll-and-select)

#### [A](https://stackoverflow.com/a/3951845)

The `select()` call has you create three bitmasks to mark which sockets and file descriptors you want to watch for reading, writing, and errors, and then the operating system marks which ones in fact have had some kind of activity; `poll()` has you create a list of descriptor IDs, and the operating system marks each of them with the *kind* of event that occurred.

The `select()` method is rather clunky and inefficient.

1、There are typically more than a thousand potential file descriptors available to a process. If a long-running process has only a few descriptors open, but at least one of them has been assigned a high number, then the bitmask passed to `select()` has to be large enough to accomodate that highest descriptor — so whole ranges of hundreds of bits will be unset that the operating system has to loop across on every `select()` call just to discover that they are unset.

> NOTE: 

2、Once `select()` returns, the caller has to loop over all three bitmasks to determine what events took place. In very many typical applications only one or two file descriptors will get new traffic at any given moment, yet all three bitmasks must be read all the way to the end to discover which descriptors those are.

> NOTE: 
>
> 意思是需要监控的file descriptor非常多，但是实际只有"a few descriptors open"，也就是说，只有几个file descriptor上有event，但是不得不遍历所有的file descriptor，来找到这几个有event的file descriptor，显然算法复杂度是O(N)

3、Because the operating system signals you about activity by rewriting the bitmasks, they are ruined and are no longer marked with the list of file descriptors you want to listen to. You either have to rebuild the whole bitmask from some other list that you keep in memory, or you have to keep a duplicate copy of each bitmask and `memcpy()` the block of data over on top of the ruined bitmasks after each `select()` call.

So the `poll()` approach works much better because you can keep re-using the same data structure.

In fact, `poll()` has inspired yet another mechanism in modern Linux kernels: `epoll()` which improves even more upon the mechanism to allow yet another leap in scalability, as today's servers often want to handle tens of thousands of connections at once. This is a good introduction to the effort:

http://scotdoyle.com/python-epoll-howto.html

While this link has some nice graphs showing the benefits of `epoll()` (you will note that `select()` is by this point considered so inefficient and old-fashioned that it does not even get a line on these graphs!):

http://lse.sourceforge.net/epoll/index.html

------

**Update:** Here is another Stack Overflow question, whose answer gives even more detail about the differences:

[Caveats of select/poll vs. epoll reactors in Twisted](https://stackoverflow.com/questions/2032598/caveats-of-select-poll-vs-epoll-reactors-in-twisted)

## poll VS epoll 

[epoll(7)](https://man7.org/linux/man-pages/man7/epoll.7.html)

The epoll API performs a similar task to poll(2): monitoring multiple file descriptors to see if I/O is possible on any of them.  The epoll API can be used either as an edge-triggered or a level-triggered interface and scales well to large numbers of watched file descriptors.

> NOTE:
>
> 上面已经总结了epoll相比于poll的优势:
>
> 1、支持 "edge-triggered"
>
> 2、scales well to large numbers of watched file descriptors

stackoverflow [poll vs. epoll insight [duplicate]](https://stackoverflow.com/questions/8858328/poll-vs-epoll-insight)



### stackoverflow [Why is epoll faster than select?](https://stackoverflow.com/questions/17355593/why-is-epoll-faster-than-select)

