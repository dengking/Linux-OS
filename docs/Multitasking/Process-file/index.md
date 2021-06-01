# Process file resource

1、本文讨论process占用的file resource

2、由于Linux使用"everything is a file"，因此，本文描述的file还包括:

a、[network socket](https://en.wikipedia.org/wiki/Network_socket)

b、[pipe](https://en.wikipedia.org/wiki/Pipe_(Unix)) 

c、......

> NOTE: 关于此，参见wikipedia [File descriptor](https://en.wikipedia.org/wiki/File_descriptor) 

3、由于Linux使用"everything is a file"，因此，本文描述的"**data structures** used by the kernel for all I/O"

> NOTE: 
>
> 1、"**data structures** used by the kernel for all I/O" 是源自 APUE3.10 File Sharing



