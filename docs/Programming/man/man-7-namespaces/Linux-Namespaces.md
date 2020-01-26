# [Linux namespaces](https://en.wikipedia.org/wiki/Linux_namespaces)



# [Separation Anxiety: A Tutorial for Isolating Your System with Linux Namespaces](https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces)

With the advent of tools like [Docker](https://www.docker.com/), [Linux Containers](https://linuxcontainers.org/), and others, it has become super easy to isolate Linux processes into their own little system environments. This makes it possible to run a whole range of applications on a single real Linux machine and ensure no two of them can interfere with each other, without having to resort to using **virtual machines**. These tools have been a huge boon to [PaaS](https://en.wikipedia.org/wiki/Platform_as_a_service) providers. But what exactly happens under the hood?

These tools rely on a number of features and components of the Linux kernel. Some of these features were introduced fairly recently, while others still require you to patch the kernel itself. But one of the key components, using Linux namespaces, has been a feature of Linux since version 2.6.24 was released in 2008.

Anyone familiar with [`chroot`](https://en.wikipedia.org/wiki/Chroot) already has a basic idea of what Linux namespaces can do and how to use namespace generally. Just as `chroot` allows processes to see any arbitrary directory as the root of the system (independent of the rest of the processes), Linux namespaces allow other aspects of the operating system to be independently modified as well. This includes the **process tree**, **networking interfaces, mount points**, **inter-process communication resources** and more.



## Why Use Namespaces for Process Isolation?

In a single-user computer, a single system environment may be fine. But on a server, where you want to run multiple services, it is essential to security and stability that the services are as isolated from each other as possible. Imagine a server running multiple services, one of which gets compromised by an intruder. In such a case, the intruder may be able to exploit that service and work his way to the other services, and may even be able compromise the entire server. **Namespace isolation** can provide a secure environment to eliminate this risk.

For example, using namespacing, it is possible to safely execute arbitrary or unknown programs on your server. Recently, there has been a growing number of programming contest and “hackathon” platforms, such as [HackerRank](https://www.hackerrank.com/), [TopCoder](http://www.topcoder.com/), [Codeforces](http://codeforces.com/), and many more. A lot of them utilize automated pipelines to run and validate programs that are submitted by the contestants. It is often impossible to know in advance the true nature of contestants’ programs, and some may even contain malicious elements. By running these programs namespaced in complete isolation from the rest of the system, the software can be tested and validated without putting the rest of the machine at risk. Similarly, online continuous integration services, such as [Drone.io](https://drone.io/), automatically fetch your code repository and execute the test scripts on their own servers. Again, **namespace isolation** is what makes it possible to provide these services safely.

Namespacing tools like Docker also allow better control over processes’ use of system resources, making such tools extremely popular for use by PaaS providers. Services like [Heroku](https://www.heroku.com/) and [Google App Engine](https://cloud.google.com/appengine/docs) use such tools to isolate and run multiple web server applications on the same real hardware. These tools allow them to run each application (which may have been deployed by any of a number of different users) without worrying about one of them using too many system resources, or interfering and/or conflicting with other deployed services on the same machine. With such process isolation, it is even possible to have entirely different stacks of dependency softwares (and versions) for each isolated environment!

If you’ve used tools like Docker, you already know that these tools are capable of isolating processes in small “containers”. Running processes in Docker containers is like running them in virtual machines, only these containers are significantly lighter than virtual machines. 

## Process Namespace

Historically, the Linux kernel has maintained a single **process tree**. The tree contains a reference to every process currently running in a **parent-child hierarchy**. A process, given it has sufficient privileges and satisfies certain conditions, can inspect another process by attaching a tracer to it or may even be able to kill it.

With the introduction of **Linux namespaces**, it became possible to have multiple “nested” process trees. Each **process tree** can have an entirely isolated set of processes. This can ensure that processes belonging to one **process tree** cannot inspect or kill - in fact cannot even know of the existence of - processes in other **sibling** or parent process trees.

Every time a computer with Linux boots up, it starts with just one process, with process identifier (PID) 1. This process is the **root** of the **process tree**, and it initiates the rest of the system by performing the appropriate maintenance work and starting the correct daemons/services. All the other processes start below this process in the tree. The **PID namespace** allows one to spin off a new tree, with its own **PID 1 process**. The process that does this remains in the **parent namespace**, in the original tree, but makes the child the root of its own **process tree**.

With **PID namespace isolation**, processes in the **child namespace** have no way of knowing of the parent process’s existence. However, processes in the **parent namespace** have a complete view of processes in the **child namespace**, as if they were any other process in the **parent namespace**.

![This namespace tutorial outlines the separation of various process trees using namespace systems in Linux.](https://uploads.toptal.io/blog/image/674/toptal-blog-image-1416487554032.png)

It is possible to create a nested set of child namespaces: one process starts a child process in a new PID namespace, and that child process spawns yet another process in a new PID namespace, and so on.