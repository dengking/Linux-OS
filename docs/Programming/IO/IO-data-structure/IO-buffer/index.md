# Buffer、queue in IO

无论是file IO、network IO，OS在实现的时候，都会使用buffer。如果用OOP的方式来进行描述的话:

```C++
class File
{
private:
    char buffer[BUFFER_SIZE];
};
```

最最典型的是socket，它有:

1、send buffer

2、recv buffer



## 控制buffer的system call

对于buffered、queued message，OS提供了控制它们的system call，比如:

1、file IO

`Book-APUE\3-File-IO\3.13-sync-fsync-and-fdatasync-Functions`

2、network IO

[socket(7)](https://man7.org/linux/man-pages/man7/socket.7.html)  # `SO_LINGER`	



## 相关章节

1、`Book-APUE\3-File-IO\3.13-sync-fsync-and-fdatasync-Functions`

2、[socket(7)](https://man7.org/linux/man-pages/man7/socket.7.html)  # `SO_LINGER`	

3、`Network\Programming\Socket\Buffer`
