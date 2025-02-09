# [why-discord-is-switching-from-go-to-rust](https://discord.com/blog/why-discord-is-switching-from-go-to-rust)

Rust is becoming a first class language in a variety of domains. At Discord, we’ve seen success with Rust on the client side and server side. For example, we use it on the client side for our video encoding pipeline for Go Live and on the server side for [Elixir NIFs](https://blog.discordapp.com/using-rust-to-scale-elixir-for-11-million-concurrent-users-c6f19fc029d3). Most recently, we drastically improved the performance of a service by switching its implementation from Go to Rust. This post explains why it made sense for us to reimplement the service, how it was done, and the resulting **performance improvements**.

### The Read States service

Discord is a product focused company, so we’ll start with some product context(Discord是一家专注于产品的公司，所以我们将从一些产品背景开始). The service we switched from Go to Rust is the “Read States” service. Its sole purpose is to keep track of which channels and messages you have read. **Read States** is accessed every time you connect to Discord, every time a message is sent and every time a message is read. In short, **Read States** is in the **hot path**. We want to make sure Discord feels super snappy(爽快的) all the time, so we need to make sure **Read States** is quick.

With the Go implementation, the **Read States service** was not supporting its product requirements. It was fast most of the time, but every few minutes we saw large latency spikes(骤增) that were bad for user experience. After investigating, we determined the spikes were due to core Go features: its **memory model** and **garbage collector (GC)**.

### Why Go did not meet our performance targets

The data structure we use to store read state information is conveniently called “Read State”. Discord has billions of **Read States**. There is one **Read State** per User per Channel. Each **Read State** has several **counters** that need to be updated atomically and often reset to 0. For example, one of the counters is how many @mentions you have in a channel.

In order to get quick **atomic counter** updates, each **Read States server** has a **Least Recently Used (LRU) cache** of **Read States**. There are millions of Users in each cache. There are tens of millions of Read States in each cache. There are hundreds of thousands of cache updates per second.

For persistence, we back the cache with a Cassandra database cluster. On cache key eviction, we commit your Read States to the database. We also schedule a database commit for 30 seconds in the future whenever a Read State is updated. There are tens of thousands of database writes per second.

In the picture below, you can see the **response time** and **system cpu** for a peak sample time frame for the Go service.¹ As you might notice, there are latency(延时) and CPU spikes roughly every 2 minutes.

> 翻译: 在下面的图片中，您可以看到Go服务的峰值示例时间框架的响应时间和系统cpu

![img](https://cdn.prod.website-files.com/5f9072399b2640f14d6a2bf4/611ed6f4d7cd20ec6f590cce_1*3v779KSfo2OkxUPfPptq_Q.png)

### So why 2 minute spikes?

In Go, on **cache key** eviction(逐出、赶出), memory is not immediately freed. Instead, the **garbage collector** runs every so often to find any memory that has no references and then frees it. In other words, instead of freeing immediately after the memory is **out of use**(不再使用), memory **hangs out**(挂起一段时间) for a bit until the **garbage collector** can determine if it’s truly **out of use**(不再使用). During **garbage collection**, Go has to do a lot of work to determine what memory is free, which can slow the program down.

These **latency spikes** definitely smelled like **garbage collection** performance impact, but we had written the Go code very efficiently and had very few allocations. We were not creating a lot of garbage.

> 翻译: 这些延迟峰值确实像是垃圾收集对性能的影响，但我们编写的Go代码非常高效，并且分配很少。我们没有制造很多垃圾。

After digging through the Go source code, we learned that Go will force a **garbage collection** run every [2 minutes at minimum](https://github.com/golang/go/blob/895b7c85addfffe19b66d8ca71c31799d6e55990/src/runtime/proc.go#L4481-L4486). In other words, if **garbage collection** has not run for 2 minutes, regardless of heap growth, go will still force a **garbage collection**.

We figured we could tune the **garbage collector** to happen more often in order to prevent large spikes, so we implemented an endpoint on the service to change the garbage collector [GC Percent](https://golang.org/pkg/runtime/debug/#SetGCPercent) on the fly. Unfortunately, no matter how we configured the **GC percent** nothing changed. How could that be? It turns out, it was because we were not allocating memory quickly enough for it to force garbage collection to happen more often.

We kept digging and learned the spikes were huge not because of a massive amount of ready-to-free memory, but because the **garbage collector** needed to scan the entire **LRU cache** in order to determine if the memory was truly free from references. Thus, we figured a smaller **LRU cache** would be faster because the **garbage collector** would have less to scan. So we added another setting to the service to change the size of the **LRU cache** and changed the architecture to have many partitioned **LRU caches** per server.

We were right. With the **LRU cache** smaller, **garbage collection** resulted in smaller spikes.

Unfortunately, the trade off of making the **LRU cache** smaller resulted in higher 99th latency times. This is because if the cache is smaller it’s less likely for a user’s **Read State** to be in the cache. If it’s not in the cache then we have to do a database load.

After a significant amount of load testing different cache capacities, we found a setting that seemed okay. Not completely satisfied, but satisfied enough and with bigger fish to fry, we left the service running like this for quite some time.

During that time we were seeing more and more success with Rust in other parts of Discord and we collectively decided we wanted to create the frameworks and libraries needed to build new services fully in Rust. This service was a great candidate to port to Rust since it was small and self-contained, but we also hoped that Rust would fix these **latency spikes**. So we took on the task of porting Read States to Rust, hoping to prove out Rust as a service language and improve the user experience.²

### Implementation, load testing, and launch

When we started load testing, we were instantly pleased with the results. The latency of the Rust version was just as good as Go’s and **had no latency spikes!**

Remarkably, we had only put very basic thought into optimization as the Rust version was written. **Even with just basic optimization, Rust was able to outperform the hyper hand-tuned Go version.** This is a huge testament(证明) to how easy it is to write efficient programs with Rust compared to the deep dive we had to do with Go.

Below are the results.

Go is purple(紫色的), Rust is blue.



![img](https://cdn.prod.website-files.com/5f9072399b2640f14d6a2bf4/611ed6f4b2a3766fbb9964c1_1*-q1B4t622mnxoV8kvT9RwA.png)



### Raising the cache capacity

After the service ran successfully for a few days, we decided it was time to re-raise the **LRU cache capacity**. In the Go version, as mentioned above, raising the cap of the LRU cache resulted in longer garbage collections. We no longer had to deal with garbage collection, so we figured we could raise the cap of the cache and get even better performance. We increased the memory capacity for the boxes, optimized the data structure to use even less memory (for fun), and increased the cache capacity to 8 million Read States.

The results below speak for themselves. **Notice the average time is now measured in microseconds and max @mention is measured in milliseconds.**

![img](https://cdn.prod.website-files.com/5f9072399b2640f14d6a2bf4/611ed6f470390c9ef1cd8fc7_1*DkLOxc-PzkqgXUj_nnOPpA.png)