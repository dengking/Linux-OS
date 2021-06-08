# Zero copy system call

从 [splice(2)](https://man7.org/linux/man-pages/man2/splice.2.html) 中的描述来看，它是基于reference count完成的

## stackoverflow [Is Linux kernel splice() zero copy?](https://stackoverflow.com/questions/21035237/is-linux-kernel-splice-zero-copy)



## [splice(2)](https://man7.org/linux/man-pages/man2/splice.2.html) 

> NOTE: 
>
> "splice" 的中文意思是 "移接"

```C
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <fcntl.h>

ssize_t splice(int fd_in, off64_t *off_in, int fd_out,
               off64_t *off_out, size_t len, unsigned int flags);
```

`splice()` moves data between two file descriptors without copying between kernel address space and user address space.  It transfers up to `len` bytes of data from the file descriptor `fd_in` to the file descriptor `fd_out`, where one of the file descriptors must refer to a pipe.

> NOTE:
>
> 在两个`fd`之间进行transfer，这些transfer是直接由kernel完成的，因此 "without copying between kernel address space and user address space"

### NOTE

The three system calls `splice()`, `vmsplice(2)`, and `tee(2)`, provide user-space programs with full control over an arbitrary kernel buffer, implemented within the kernel using the same type of buffer that is used for a pipe.  In overview, these system calls perform the following tasks:

1、[splice()](https://man7.org/linux/man-pages/man2/splice.2.html) moves data from the buffer to an arbitrary file descriptor, or vice versa, or from one buffer to another.

2、[tee(2)](https://man7.org/linux/man-pages/man2/tee.2.html) "copies" the data from one buffer to another.

3、[vmsplice(2)](https://man7.org/linux/man-pages/man2/vmsplice.2.html) "copies" data from user space into the buffer.

Though we talk of copying, actual copies are generally avoided. The kernel does this by implementing a **pipe buffer** as a set of reference-counted pointers to pages of kernel memory.  The kernel creates "copies" of pages in a buffer by creating new pointers (for the output buffer) referring to the pages, and increasing the reference counts for the pages: only pointers are copied, not the pages of the buffer.

> NOTE: 显然也是基于reference count的

## [vmsplice(2)](https://man7.org/linux/man-pages/man2/vmsplice.2.html)

```c
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <fcntl.h>
#include <sys/uio.h>

ssize_t vmsplice(int fd, const struct iovec *iov, size_t nr_segs, unsigned int flags);
```

If `fd` is opened for writing, the `vmsplice()` system call maps `nr_segs` ranges of user memory described by `iov` into a pipe.  

If `fd` is opened for reading, the `vmsplice()` system call fills `nr_segs` ranges of user memory described by `iov` from a pipe.  

The file descriptor `fd` must refer to a pipe.



## [tee(2)](https://man7.org/linux/man-pages/man2/tee.2.html)

```C
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <fcntl.h>

ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
```

`tee()` duplicates up to `len` bytes of data from the pipe referred to by the file descriptor `fd_in` to the pipe referred to by the file descriptor `fd_out`.  It does not consume the data that is duplicated from `fd_in`; therefore, that data can be copied by a subsequent splice(2).



Conceptually, `tee()` copies the data between the two pipes.  In reality no real data copying takes place though: under the covers, tee() assigns data to the output by merely grabbing a reference to the input.



```C
#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int
    main(int argc, char *argv[])
{
    int fd;
    int len, slen;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    do {
        /*
                * tee stdin to stdout.
                */
        len = tee(STDIN_FILENO, STDOUT_FILENO,
                  INT_MAX, SPLICE_F_NONBLOCK);

        if (len < 0) {
            if (errno == EAGAIN)
                continue;
            perror("tee");
            exit(EXIT_FAILURE);
        } else
            if (len == 0)
                break;

        /*
                * Consume stdin by splicing it to a file.
                */
        while (len > 0) {
            slen = splice(STDIN_FILENO, NULL, fd, NULL,
                          len, SPLICE_F_MOVE);
            if (slen < 0) {
                perror("splice");
                break;
            }
            len -= slen;
        }
    } while (1);

    close(fd);
    exit(EXIT_SUCCESS);
}
```

