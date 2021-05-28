# upenn [CSE 380 Computer Operating Systems # Lecture Note 2: Processes and Threads](http://www.cis.upenn.edu/~lee/03cse380/lectures/ln2-process-v4.pdf)



## Keeping track of processes


Processes (PCBs) are manipulated by two main components of the OS in order to achieve the effects of multiprogramming:
- **Scheduler**: determines the order in which processes will gain access to the CPU. Efficiency and fair-play are issues here.
- **Dispatcher**: actually allocates CPU to the process selected by the **scheduler**.

