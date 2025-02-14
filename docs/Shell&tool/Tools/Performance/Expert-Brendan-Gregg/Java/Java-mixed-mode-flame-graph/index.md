# Java mixed-mode flame graph

## [netflixtechblog Java in Flames](https://netflixtechblog.com/java-in-flames-e763b3d32166)

**Java mixed-mode flame graphs** provide a complete visualization of CPU usage and have just been made possible by a new JDK option: `-XX:+PreserveFramePointer`. We’ve been developing these at Netflix for everyday **Java performance analysis** as they can identify all CPU consumers and issues, including those that are hidden from other profilers.

### Example

This shows CPU consumption by a Java process, both user- and kernel-level, during a vert.x benchmark:

![](https://miro.medium.com/v2/resize:fit:2000/1*-RGVVUyBIdiQo0vvQJNWTA.png)

Showing all CPU usage with Java context is amazing and useful:

- On the top right you can see a peak of kernel code (colored red) for performing a TCP send (which often leads to a TCP receive while handling the send). Beneath it (colored green) is the Java code responsible. 

- In the middle (colored green) is the Java code that is running on-CPU. 

- In the bottom left, a small yellow tower shows CPU time spent in GC. 

We’ve already used Java flame graphs to quantify **performance improvements** between frameworks (Tomcat vs rxNetty), which included identifying time spent in Java code compilation, the Java code cache, other system libraries, and differences in kernel code execution. All of these CPU consumers were invisible to other Java profilers, which only focus on the execution of Java methods.

### Flame Graph Interpretation

## [youtube Java Mixed-Mode Flame Graphs](https://www.youtube.com/watch?v=BHA65BqlqSk)

[brendangregg Slides Java Mixed-Mode Flame](https://www.brendangregg.com/Slides/JavaOne2015_MixedModeFlameGraphs.pdf)


