# Chapter 3. Processes

The concept of a ***process*** is fundamental to any ***multiprogramming*** operating system. A process is usually defined as an instance of a program in execution; thus, if 16 users are running vi at once, there are 16 separate processes (although they can share the same executable code). Processes are often called *tasks* or *threads* in the Linux source code.

In this chapter, we discuss static properties of processes and then describe how ***process switching*** is performed by the kernel. The last two sections describe how processes can be created and destroyed. We also describe how Linux supports multithreaded applications as mentioned in Chapter 1, it relies on so-called *lightweight processes (LWP)*.