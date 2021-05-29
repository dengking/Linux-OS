# man7 [brk(2) — Linux manual page](https://man7.org/linux/man-pages/man2/brk.2.html)

`brk()` and `sbrk()` change the location of the program break, which defines the end of the process's data segment (i.e., the program break is the first location after the end of the **uninitialized data segment**).  Increasing the program break has the effect of allocating memory to the process; decreasing the break      deallocates memory.



## NOTES

Avoid using `brk()` and `sbrk()`: the `malloc(3)` memory allocation package is the portable and comfortable way of allocating memory.