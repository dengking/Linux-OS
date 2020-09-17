# [7 Recording Inferior’s Execution and Replaying It](https://sourceware.org/gdb/onlinedocs/gdb/Process-Record-and-Replay.html#Process-Record-and-Replay)

> NOTE: 
>
> 参见: wikipedia [Record and replay debugging](https://en.wikipedia.org/wiki/Record_and_replay_debugging)
>
> 这种record log and replay的做法在很多地方都用到了：
>
> - Redis: [Append only file persistence](https://redislabs.com/ebook/part-2-core-concepts/chapter-4-keeping-data-safe-and-ensuring-performance/4-1-persistence-options/4-1-2-append-only-file-persistence/)
> - wikipedia [database transaction log](https://en.wikipedia.org/wiki/Transaction_log)
> - [The Log: What every software engineer should know about real-time data's unifying abstraction](https://engineering.linkedin.com/distributed-systems/log-what-every-software-engineer-should-know-about-real-time-datas-unifying#:~:text=A%20log%20is%20perhaps%20the,proceed%20left%2Dto%2Dright.)
> - DistributedLog: [A Technical Review of Kafka and DistributedLog](http://bookkeeper.apache.org/distributedlog/technical-review/2016/09/19/kafka-vs-distributedlog.html)

