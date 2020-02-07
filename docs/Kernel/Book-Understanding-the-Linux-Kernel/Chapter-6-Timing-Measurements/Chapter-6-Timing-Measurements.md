[TOC]



# Chapter 6. Timing Measurements

Countless computerized activities are driven by **timing measurements** , often behind the user's back. For instance, if the screen is automatically switched off after you have stopped using the computer's console, it is due to a timer that allows the kernel to keep track of how much time has elapsed since you pushed a key or moved the mouse. If you receive a warning from the system asking you to remove a set of unused files, it is the outcome of a program that identifies all user files that have not been accessed for a long time. To do these things, programs must be able to retrieve a `timestamp` identifying its last access time from each file. Such a timestamp must be automatically written by the **kernel**. More significantly, **timing drives process switches** along with even more visible kernel activities such as checking for time-outs.

***SUMMARY*** : CPU的控制器也是受时钟控制的：clock generator；

We can distinguish two main kinds of **timing measurement** that must be performed by the Linux kernel:

- Keeping the current time and date so they can be returned to user programs through the  `time()` ,  `ftime( )` , and  `gettimeofday( )` APIs (see the section "The `time( )` and `gettimeofday( )`  System Calls" later in this chapter) and used by the kernel itself as timestamps for files and network packets
- Maintaining timers mechanisms that are able to notify the **kernel** (see the later section "Software Timers and Delay Functions") or a user program (see the later sections "The `setitimer( )` and `alarm( )` System Calls" and "System Calls for POSIX Timers") that a certain interval of time has elapsed

**Timing measurements** are performed by several hardware circuits based on fixed-frequency oscillators and counters. This chapter consists of four different parts. The first two sections describe the hardware devices that underly timing and give an overall picture of **Linux timekeeping architecture**. The following sections describe the main time-related duties of the kernel: implementing **CPU time sharing**, updating system time and resource usage statistics, and maintaining **software timers**. The last section discusses the system calls related to timing measurements and the corresponding service routines.

