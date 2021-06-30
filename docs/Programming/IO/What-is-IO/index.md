# Input output

什么是IO，看看维基百科[Input/output](https://en.wikipedia.org/wiki/Input/output)的解释吧。

## wikipedia [Input/output](https://en.wikipedia.org/wiki/Input/output)

In [computing](https://en.wikipedia.org/wiki/Computing), **input/output** or **I/O** (or, informally, **io** or **IO**) is the communication between an [information processing system](https://en.wikipedia.org/wiki/Information_processing_system), such as a [computer](https://en.wikipedia.org/wiki/Computer), and the outside world, possibly a human or another [information processing system](https://en.wikipedia.org/wiki/Information_processor). [Inputs](https://en.wikipedia.org/wiki/Information) are the signals or data received by the system and outputs are the signals or [data](https://en.wikipedia.org/wiki/Data_(computing)) sent from it. The term can also be used as part of an action; to "perform I/O" is to perform an [input or output operation](https://en.wikipedia.org/wiki/I/O_scheduling).



**I/O devices** are the pieces of [hardware](https://en.wikipedia.org/wiki/Hardware_(computing)) used by a human (or other system) to communicate with a computer. For instance, a [keyboard](https://en.wikipedia.org/wiki/Computer_keyboard) or [computer mouse](https://en.wikipedia.org/wiki/Computer_mouse) is an [input device](https://en.wikipedia.org/wiki/Input_device) for a computer, while [monitors](https://en.wikipedia.org/wiki/Computer_monitor) and [printers](https://en.wikipedia.org/wiki/Computer_printer) are output devices. Devices for communication between computers, such as [modems](https://en.wikipedia.org/wiki/Modem) and [network cards](https://en.wikipedia.org/wiki/Network_card), typically perform both input and output operations.



In computer architecture, the combination of the [CPU](https://en.wikipedia.org/wiki/Central_processing_unit) and [main memory](https://en.wikipedia.org/wiki/Main_memory), to which the CPU can read or write directly using individual [instructions](https://en.wikipedia.org/wiki/Instruction_(computer_science)), is considered the brain of a computer. Any transfer of information to or from the CPU/memory combo, for example by reading data from a [disk drive](https://en.wikipedia.org/wiki/Disk_drive), is considered I/O. The CPU and its supporting circuitry may provide [memory-mapped I/O](https://en.wikipedia.org/wiki/Memory-mapped_I/O) that is used in low-level [computer programming](https://en.wikipedia.org/wiki/Computer_programming), such as in the implementation of [device drivers](https://en.wikipedia.org/wiki/Device_driver), or may provide access to [I/O channels](https://en.wikipedia.org/wiki/Channel_I/O). An [I/O algorithm](https://en.wikipedia.org/wiki/External_memory_algorithm) is one designed to exploit locality and perform efficiently when exchanging data with a secondary storage device, such as a disk drive.

> NOTE: 这就是我们平时所说的IO。

### Interface

#### Higher-level implementation

Higher-level [operating system](https://en.wikipedia.org/wiki/Operating_system) and programming facilities employ separate, more abstract I/O concepts and [primitives](https://en.wikipedia.org/wiki/Primitive_(computer_science)). For example, most operating systems provide application programs with the concept of [files](https://en.wikipedia.org/wiki/Computer_file). The [C](https://en.wikipedia.org/wiki/C_(programming_language)) and [C++](https://en.wikipedia.org/wiki/C%2B%2B) programming languages, and operating systems in the [Unix](https://en.wikipedia.org/wiki/Unix) family, traditionally abstract files and devices as [streams](https://en.wikipedia.org/wiki/Stream_(computing)), which can be read or written, or sometimes both. The [C standard library](https://en.wikipedia.org/wiki/C_standard_library) provides [functions for manipulating streams](https://en.wikipedia.org/wiki/C_file_input/output) for input and output.

> NOTE: 抽象为[stream](https://en.wikipedia.org/wiki/Stream_(computing))是非常重要，下篇会对此进行详细描述。

An alternative to special primitive functions is the [I/O monad](https://en.wikipedia.org/wiki/I/O_monad), which permits programs to just describe I/O, and the actions are carried out outside the program. This is notable because the I/O functions would introduce [side-effects](https://en.wikipedia.org/wiki/Side-effect_(computer_science)) to any programming language, but this allows [purely functional programming](https://en.wikipedia.org/wiki/Purely_functional_programming) to be practical.



## IO可以看做是data exchange

本节标题的含义是IO可以看做是一种data exchange，即双方**交换数据**，关于data exchange，参见:

wikipedia [Data exchange](https://en.wikipedia.org/wiki/Data_exchange)

## IO可以看做是一种通信

IO也可以看做是一种通信，因此，双方需要约定好协议。



## IO mechanism 

本节总结IO的原理，下面是一些素材:

### stackoverflow [What are the advantages of memory-mapped files?](https://stackoverflow.com/questions/192527/what-are-the-advantages-of-memory-mapped-files) # [A](https://stackoverflow.com/a/192854)

> if you use a system call (e.g. Linux's `pread()` ) then that typically involves the kernel copying the data from its own buffers into user space. This extra copying not only takes time, but decreases the effectiveness of the CPU's caches by accessing this extra copy of the data.

### UNP 6.1 I/O Multiplexing: The `select` and `poll` Functions[¶](https://notes.shichao.io/unp/ch6/#chapter-6-io-multiplexing-the-select-and-poll-functions)c

As we show in all the examples in this section, there are normally two distinct phases for an input operation:

1、Waiting for the data to be ready

> NOTE: 
>
> 等待数据就绪

2、Copying the data from the kernel to the process

> NOTE: 将数据从kernel拷贝到用户态

