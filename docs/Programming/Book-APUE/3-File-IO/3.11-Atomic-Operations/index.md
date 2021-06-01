# 3.11 Atomic Operations



## Appending to a File

The problem here is that our logical operation of ‘‘position to the end of file and write’’ requires two separate function calls (as we’ve shown it). The solution is to have the positioning to the current end of file and the write be an atomic operation with regard to other processes. Any operation that requires more than one function call cannot be atomic, as there is always the possibility that the kernel might temporarily
suspend the process between the two function calls (as we assumed previously).

The UNIX System provides an atomic way to do this operation if we set the `O_APPEND` flag when a file is opened. As we described in the previous section, this causes the kernel to position the file to its current end of file before each write. We no longer have to call `lseek` before each write.

> NOTE: 
>
> tag-file status flag-O_APPEND-atomic

## `pread` and `pwrite` Functions

The Single UNIX Specification includes two functions that allow applications to seek and perform I/O atomically: `pread` and `pwrite`.



## Creating a File

We saw another example of an atomic operation when we described the `O_CREAT` and `O_EXCL` options for the `open` function. When both of these options are specified, the `open` will fail if the file already exists.



## atomic operation

In general, the term atomic operation refers to an operation that might be composed of multiple steps. If the operation is performed atomically, either all the steps are performed (on success) or none are performed (on failure). It must not be possible for only a subset of the steps to be performed. We’ll return to the topic of atomic operations when we describe the link function (Section 4.15) and record locking (Section 14.3).

> NOTE: 
>
> tag-assemble-as-atomic-primitive原语