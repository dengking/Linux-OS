# Linux OS interrupt and interrupt handler

本书中集中讲述和interrupt的章节如下：

| 章节                                            | 主要内容                                                     |
| ----------------------------------------------- | ------------------------------------------------------------ |
| Chapter 4. Interrupts and Exceptions            | 讲述interrupt的基础知识，是后续相关章节的基础。内容偏硬件。  |
| Chapter 6. Timing Measurements                  | 讲述hardware devices that underly timing、time-related duties of the kernel |
| Chapter 13. I/O Architecture and Device Drivers | 讲述I/O devices                                              |

本文的内容是对这些章节的内容的梳理。

Hardware通过interrupt来通知linux kernel。在Chapter 4. Interrupts and Exceptions中对interrupt进行了分类：

| 来源                                                         |                        | Intel microprocessor manuals |
| ------------------------------------------------------------ | ---------------------- | ---------------------------- |
| CPU control unit                                             | Synchronous interrupt  | exceptions                   |
| Other hardware devices at arbitrary times with respect to the CPU clock signals, such as **interval timers**  and **I/O devices** | Asynchronous interrupt | interrupts                   |

对于hardware的知识，我们不做深入分析，我们重点关注software部分，即由interrupt所触发的kernel control path（是OS层的interrupt handler），我们对一些主要的interrupt和其kernel control path进行总结。

