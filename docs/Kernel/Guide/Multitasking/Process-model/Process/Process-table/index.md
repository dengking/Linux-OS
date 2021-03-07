# Process table



## stackoverflow [What is the linux process table ? What does it consist of?](https://stackoverflow.com/questions/4880555/what-is-the-linux-process-table-what-does-it-consist-of)

This term keeps appearing in my Operating System notes, and I'm not entirely sure what it is/where it's stored and how or why.



### [A](https://stackoverflow.com/a/4880715)

The **process table** in Linux (such as in nearly every other operating system) is simply a **data structure** in the RAM of a computer. It holds information about the processes that are currently handled by the OS.

This information includes general information about each process

- process id
- process owner
- process priority
- environment variables for each process
- the parent process
- pointers to the executable machine code of a process.

A very important information in the **process table** is the state in that each process currently is. This information is essential for the OS, because it enables the so called multiprocessing, i.e. the possibility to virtually run several processes on only one processing unit (CPU).

The information whether a process is currently ACTIVE, SLEEPING, RUNNING, etc. is used by the OS in order to handle the execution of processes.

Furthermore there is statistical information such as when was the process RUNNING the last time in order to enable the schedulr of the OS to decide which process should be running next.

So in summary the process table is the central organizational element for the OS to handle all the started processes.

A short introduction can be found in this thread:

<http://www.linuxforums.org/forum/kernel/42062-use-process-table.html>

And wikipedia also has nice information about processes:

<http://en.wikipedia.org/wiki/Process_management_(computing)#Process_description_and_control>

<http://en.wikipedia.org/wiki/Process_table>







## opensourceforu [The Life of a Process](https://opensourceforu.com/2016/03/the-life-of-a-process/)

在这篇文章中，从内核源码的角度描述了process table，在本地的`process-lifetime/Unix-process-lifetime.md`中收录了这篇文章；



## cs.unc.edu [Process Table](http://www.cs.unc.edu/~dewan/242/s07/notes/pm/node3.html)

The **process table** is a data structure maintained by the operating system to facilitate **context switching** and **scheduling**, and other activities discussed later. Each **entry** in the table, often called a **context block**, contains information about a process such as process name and state (discussed below), priority (discussed below), registers, and a semaphore it may be waiting on (discussed later). The exact contents of a context block depends on the operating system. For instance, if the OS supports paging, then the context block contains an entry to the page table.

In Xinu, the index of a process table entry associated with a process serves to identify the process, and is known as the **process id** of the process. 



## wikipedia [Process table](https://en.wikipedia.org/wiki/Process_table)