# 8.3 `fork` Function



## File Sharing

When we redirect the standard output of the parent from the program in Figure 8.1, the child’s standard output is also redirected. Indeed, one characteristic of fork is that all **file descriptors** that are open in the parent are duplicated in the child. We say ‘‘duplicated’’ because it’s as if the `dup` function had been called for each descriptor. The parent and the child share a file table entry for every open descriptor (recall Figure 3.9).



![](./APUE-Figure-8.2-Sharing-of-open-files-between-parent-and-child-after-fork.png)