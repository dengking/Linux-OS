# linuxjournal [Thinking Concurrently: How Modern Network Applications Handle Multiple Connections](https://www.linuxjournal.com/content/thinking-concurrently)

Reuven explores different types of multiprocessing and looks at the advantages and disadvantages of each.

When I first started consulting, and my clients were small organizations just getting started on the web, they inevitably would ask me what kind of high-powered server they would need. My clients were all convinced that they were going to be incredibly popular and important, and that they would have lots of visitors coming to their websites—and it was important that their sites would be able to stand up under this load.

I would remind them that each day has 86,400 seconds. This means that if one new person visits their site each second, the server will need to handle 86,400 requests per day—a trivial number, for most modern computers, especially if you're just serving up static files.

I would then ask, do they really expect to get more than 86,000 visitors per day? The client would almost inevitably answer, somewhat sheepishly, "No, definitely not."

Now, I knew that my clients didn't need to worry about the size or speed of their servers; I really did have their best interests at heart, and I was trying to convince them, in a somewhat dramatic way, that they didn't need to spend money on a new server. But I did take certain liberties with the truth when I presented those numbers—for example:

- There's a difference between 86,400 visitors in one day, spread out evenly across the entire day, and a spike during lunch hour, when many people do their shopping and leisure reading.
- Web pages that contain CSS, JavaScript and images—which is all of them, in the modern era—require more than one HTTP request for each page load. Even if you have 10,000 visitors, you might well have more than 100,000 HTTP requests to your server.
- When a simple web site becomes a web application, you need to start worrying about the speed of back-end databases and third-party services, as well as the time it takes to compute certain things.

So, what do you in such cases? If you can handle precisely one request per second, what happens if more than one person visits your site at the same time? You could make one of them wait until the other is finished and then service the next one, but if you have 10 or 15 simultaneous requests, that tactic eventually will backfire on you.

In most modern systems, the solution has been to take advantage of multiprocessing: have the computer do more than one thing at a time. If a computer can do two things each second, and if your visitors are spread out precisely over the course of a day, then you can handle 172,800 visitors. And if you can do three things at a time, you suddenly can handle 259,200 visitors—and so forth.

How can a computer do more than one thing at a time? With a single CPU, each process gets a "time slice", meaning one fraction of the time that the CPU is working. If you have ten processes, and each gets an equal time slice, then each will run once per second for 0.1 seconds. As you increase the number of processes, the time allocated to each process goes down.

Modern computers come with multiple CPUs (aka "cores"), which means that they actually can do things in parallel, rather than simply give each process a time slice on the system's single processor. In theory, a dual-core system with ten processes will run each process once per second for 0.2 seconds, divided across the processors.

Scaling is never perfectly linear, so you can't really predict things in that way, but it's not a bad way to think about this.

Processes, as described here, are a great way for the computer to do more than one thing at a time. And yet, many applications have other ways of dealing with concurrency. Two of the most popular alternatives to processes are threads and the reactor pattern, especially popular and well known in node.js and the nginx HTTP server.

So in this article, I explore the different types of multiprocessing that exist, looking at the advantages and disadvantages of each one. Even if you're not interested in switching, it's useful to know what is out there.

### Processes

The idea behind a process is fairly simple. A running program consists of not only executing code, but also data and some context. Because the code, data and context all exist in memory, the operating system can switch from one process to another very quickly. This combination of code + data + context is known as a "process", and it's the basis for how Linux systems work.

When you start your Linux box, it has a single process. That process then "forks" itself, such that two identical processes are running. The second ("child") process reads new code, data and context ("exec"), and thus starts running a new process. This continues throughout the time that a system is running. When you execute a new program on the command line with & at the end of the line, you're forking the shell process and then exec'ing your desired program in its place.

The Apache httpd server, which is extremely popular and standard on many Linux systems, works by default on a process model. You might think that when a new request comes in, Apache will start up a new process to handle it. But starting it up takes some time, and no one wants to wait for it to happen. The solution is, thus, to "prefork" a bunch of servers. This way, when a new request arrives, Apache can hand off that request to a process. When Apache sees that you're running low on processes, it will add a bunch to the pool, ensuring that there are always enough spare servers. If you reach the limit, things start to cause problems for users,

In many cases, the **process model** is great. Linux is great at launching processes; it's a fairly low-cost operation, and one that a typical system does hundreds or even thousands of times every hour. Moreover, the kernel developers have learned through the years how to do things intelligently, such that a forked process uses (and writes to) its own memory only when it needs to; until that time, it continues to use memory from its parent process.

Moreover, processes are extremely stable and secure. Memory owned by one process is typically not visible to other processes, let alone writable by other processes. And if a process goes down, it shouldn't take the entire system down with it.

So, what's not to like? Processes are great, no?

Yes, but they also require a fair amount of overhead. If all you're doing is serving up some files, or doing a tiny amount of processing, using a full process for that might seem excessive.

Moreover, if you're doing a number of related tasks that are using the same memory, the fact that every process keeps data separate might make things safe, but also more of a memory hog.



### Threads

People coming from a Windows or Java background often scoff at the UNIX tradition of using processes. They say that processes are too heavy for most things, and that you would be better off using threads instead. A thread is similar to a process, except that it exists inside a process.

Just as a computer splits its time across different processes, giving each one a time slice, a process splits its time across different threads, giving each one a time slice.

Because threads exist within an existing process, their startup time is much faster. And because threads share memory with other threads in the process, they consume less memory and are more efficient.

The fact that threads share memory can lead to all sorts of problematic situations. How do you ensure that two different threads aren't modifying the same data at the same time? How do you ensure that your threads execute in the appropriate order—or, how do you make sure that the order isn't actually that important? There are all sorts of issues associated with threading, and people who work with threads know them all too well. The benefits of threads are obvious, but ensuring that they work, and work correctly, can be quite frustrating. Indeed, people who grew up using processes find threads to be fraught with danger and complexity, and they do whatever they can to avoid them.

As a general rule, people with a Microsoft technology background use threads all of the time, starting up a new process only when necessary. By contrast, starting a new process in the Microsoft world takes a long time. People with a UNIX background, meanwhile, think that starting a new process is the easiest and safest thing to do, and they tend to shy away from threads.

Which is the right answer? It all depends. You probably can squeeze more performance out of your computer if you use threads, but at the same time, you can be sure that the code is written in a way that takes advantage of the threads, and it doesn't fall into any of the common traps.

What if you want to use threads, rather than processes, with your Apache server? Years ago, the Apache httpd developers realized that it was foolish for them to push a single model upon their users. For some, and especially for people using Windows, threads were preferable. For many, the traditional processes were preferable. And in some cases, it wasn't obvious which would be better without first doing some benchmarking.

The solution was something known as an MPM (multi-processing module). You can choose the traditional "pre-fork" MPM, typically used on UNIX. You can use the "worker" MPM, which is a combination of processes and threads. If you're on Windows, there's a special "mpm_winnt" MPM, which uses a single process and many threads.

The "worker" MPM is perhaps the most interesting of the bunch, in that it allows you to control the maximum number of processes (with the `MaxClients` directive), but also a number of threads per process (with the `ThreadsPerChild` directive). You then can experiment with the optimal configuration for your server, deciding which mixture of processes and threads is going to give you the best performance.

### An Old-New Idea

During the last few years, a number of network applications have re-discovered a way of writing code that seems counter to all of these ideas. Instead of having multiple processes, or multiple threads, just have a single process, without any threads. That process then can handle all of the incoming network traffic.

At first blush, that sounds a bit crazy. Why keep everything together in a single process?

But, then consider the fact that even on a highly optimized Linux system, there is still some overhead to the "context switch", moving from one process to another. This overhead is repeated at a smaller level within a process, when you switch from thread to thread.

If you handle all of the incoming network requests within a single process, you avoid all of those context switches. You can do that by having an event loop, and then by hanging functions on that event loop. If your event loop contains functions A, B and C, the system gives A a chance to run, then B, then C and then A again. With each opportunity provided by the event loop, you find that A, B and C each progress forward a bit each time.

This actually works quite well, and it has been demonstrated to scale better than processes and threads. What's the problem then?

First of all, the code needs to be written in such a way that it can be divided into functions and put into an event loop. Thinking this way, and writing this style of code, is different from what people typically are used to in the procedural and object-oriented worlds. In many ways, it's like creating a callback function, in that you don't know quite when it'll run.

Among other things, you need to be super careful when working with I/O in this kind of function. That's because disks and networks are extremely slow, and if function B is reading from the disk, then it's waiting idly while neither A nor C has a chance to run. Working with I/O thus requires special handling.

This is part of a bigger issue, namely that modern operating systems use "pre-emptive multitasking", telling each process when its time slice has expired. The reactor pattern uses "cooperative multitasking", in that a rogue function can hog the CPU simply by failing to abide by the rules.

This paradigm is known as the "reactor pattern" and underlies the nginx HTTP server, node.js, Twisted Python and the new asyncio libraries in Python. It has proven itself, but it does require that developers think in new and different ways.

Not to be outdone by nginx, Apache now has an "event" MPM, which handles things using this method. So if you're a fan of Apache and want to try out the reactor pattern without switching to nginx, you can do so. If you're simply using the server and connecting to an external application, rather than writing code that will be embedded within Apache, the MPM will affect performance, but not how you write your application.

### Conclusion

So, where does this leave you? First of all, it means you have a number of options. It also means that when you start to worry about performance—and only then—you can start to run experiments to compare the different paradigms and how they work.

But it also means that in today's highly networked world, you might want to consider one or more of these options right away. At the very least, you should be familiar with them and how they work, and the trade-offs associated with them. In particular, while the reactor pattern can be hard to understand, such understanding will make it easier to design architectures that will scale—especially when you truly need it.