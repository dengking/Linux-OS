# [mmap(2) — Linux manual page](https://man7.org/linux/man-pages/man2/mmap.2.html)



`mmap()` creates a new mapping in the virtual address space of the calling process.  The starting address for the new mapping is specified in `addr`.  The length argument specifies the length of the mapping (which must be greater than 0).

> NOTE: 
>
> 它不仅仅只有这种用法，它还可以用于dynamic allocation

If `addr` is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.

## The `flags` argument

### `MAP_ANONYMOUS`

The mapping is not backed by any file; its contents are initialized to zero.  The `fd` argument is ignored; however, some implementations require `fd` to be `-1` if `MAP_ANONYMOUS` (or `MAP_ANON`) is specified, and portable applications should ensure this.  The `offset` argument should be zero. The use of `MAP_ANONYMOUS` in conjunction with `MAP_SHARED` is supported on Linux only since kernel 2.4.

> NOTE: 
>
> 用于dynamic allocation，在 [clone(2)](https://man7.org/linux/man-pages/man2/clone.2.html) 中，展示了这种用法
>
> 