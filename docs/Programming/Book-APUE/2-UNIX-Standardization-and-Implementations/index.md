# 2 UNIX Standardization and Implementations

## 2.1 Introduction

Much work has gone into standardizing the UNIX programming environment and the C programming language.

In this chapter we first look at the various standardization efforts that have been under way over the past two and a half decades. We then discuss the effects of these UNIX programming standards on the operating system implementations that are described in this book. An important part of all the standardization efforts is the specification of various limits that each implementation must define, so we look at these limits and the various ways to determine their values.

## 2.2 UNIX Standardization

### 2.2.1 ISO C

> NOTE: 本节介绍了ISO C standard的演进过程，这些历史可以pass掉。下面关于ISO C standard的一些网站链接：
>
> - [wikipedia C (programming language)](https://en.wikipedia.org/wiki/C_(programming_language))
> - [The Standard](http://www.iso-9899.info/wiki/The_Standard)
> - [wikipedia ANSI C](https://en.wikipedia.org/wiki/ANSI_C)

This standard defines not only the **syntax** and **semantics** of the programming language but also a **standard library**.

The ISO C library can be divided into 24 areas, based on the headers defined by the standard (see Figure 2.1). The **POSIX.1 standard** includes these headers, as well as others. As Figure 2.1 shows, all of these headers are supported by the four implementations (FreeBSD 8.0, Linux 3.2.0, Mac OS X 10.6.8, and Solaris 10) that are described later in this chapter.

> NOTE: **POSIX.1 standard**是ISO C standard的超集。

> The ISO C headers depend on which version of the C compiler is used with the operating system. FreeBSD 8.0 ships with version 4.2.1 of gcc, Solaris 10 ships with version 3.4.3 of gcc (in addition to its own C compiler in Sun Studio), Ubuntu 12.04 (Linux 3.2.0) ships with version 4.6.3 of gcc, and Mac OS X 10.6.8 ships with both versions 4.0.1 and 4.2.1 of gcc.

#### Headers defined by the ISO C standard

[C standard library](https://en.wikipedia.org/wiki/C_standard_library)



### 2.2.2 IEEE POSIX

> NOTE: 本节介绍了IEEE POSIX standard的演进过程，这些历史可以pass掉。下面关于IEEE POSIX的一些网站链接：
>
> - [wikipedia POSIX](https://en.wikipedia.org/wiki/POSIX)
> - [POSIX official site](http://get.posixcertified.ieee.org/)

POSIX is a family of standards initially developed by the IEEE (Institute of Electrical and Electronics Engineers). POSIX stands for Portable Operating System Interface. It originally referred only to the IEEE Standard 1003.1-1988 — the operating system interface — but was later extended to include many of the standards and draft standards with the 1003 designation, including the shell and utilities (1003.2).

Because the 1003.1 standard specifies an *interface* and not an *implementation*, no distinction is made between **system calls** and **library functions**. All the routines in the standard are called *functions*.



In this text we describe the 2008 edition of POSIX.1. Its interfaces are divided into **required ones** and **optional ones**. The optional interfaces are further divided into 40 sections, based on functionality. The sections containing nonobsolete programming interfaces are summarized in Figure 2.5 with their respective **option codes**. **Option codes** are two- to three-character abbreviations that **identify** the interfaces that belong to each functional area and **highlight** text describing aspects of the standard that depend on the support of a particular option(highlight 和identify并列). Many **options** deal with real-time extensions.

> NOTE: : 上面这段话中的option所指为optional interface in the POSIX.1

| Code |      | Symbolic constant                    | Description                                      |
| ---- | ---- | ------------------------------------ | ------------------------------------------------ |
| ADV  |      | `_POSIX_ADVISORY_INFO `              | advisory information (real-time)                 |
| CPT  |      | `_POSIX_CPUTIME `                    | process CPU time clocks (real-time)              |
| FSC  | •    | `_POSIX_FSYNC `                      | file synchronization                             |
| IP6  |      | `_POSIX_IPV6 `                       | IPv6 interfaces                                  |
| ML   |      | `_POSIX_MEMLOCK `                    | process memory locking (real-time)               |
| MLR  |      | `_POSIX_MEMLOCK_RANGE `              | memory range locking (real-time)                 |
| MON  |      | `_POSIX_MONOTONIC_CLOCK `            | monotonic clock (real-time)                      |
| MSG  |      | `_POSIX_MESSAGE_PASSING `            | message passing (real-time)                      |
| MX   |      | `__STDC_IEC_559_ `_                  | IEC 60559 floating-point option                  |
| PIO  |      | `_POSIX_PRIORITIZED_IO `             | prioritized input and output                     |
| PS   |      | `_POSIX_PRIORITY_SCHEDULING `        | process scheduling (real-time)                   |
| RPI  |      | `_POSIX_THREAD_ROBUST_PRIO_INHERIT ` | robust mutex priority inheritance (real-time)    |
| RPP  |      | `_POSIX_THREAD_ROBUST_PRIO_PROTECT ` | robust mutex priority protection (real-time)     |
| RS   |      | `_POSIX_RAW_SOCKETS `                | raw sockets                                      |
| SHM  |      | `_POSIX_SHARED_MEMORY_OBJECTS `      | shared memory objects (real-time)                |
| SIO  |      | `_POSIX_SYNCHRONIZED_IO `            | synchronized input and output (real-time)        |
| SPN  |      | `_POSIX_SPAWN `                      | spawn (real-time)                                |
| SS   |      | `_POSIX_SPORADIC_SERVER `            | process sporadic server (real-time)              |
| TCT  |      | `_POSIX_THREAD_CPUTIME `             | thread CPU time clocks (real-time)               |
| TPI  |      | `_POSIX_THREAD_PRIO_INHERIT `        | nonrobust mutex priority inheritance (real-time) |
| TPP  |      | `_POSIX_THREAD_PRIO_PROTECT `        | nonrobust mutex priority protection (real-time)  |
| TPS  |      | `_POSIX_THREAD_PRIORITY_SCHEDULING ` | thread execution scheduling (real-time)          |
| TSA  | •    | `_POSIX_THREAD_ATTR_STACKADDR `      | thread stack address attribute                   |
| TSH  | •    | `_POSIX_THREAD_PROCESS_SHARED `      | thread process-shared synchronization            |
| TSP  |      | `_POSIX_THREAD_SPORADIC_SERVER `     | thread sporadic server (real-time)               |
| TSS  | •    | `_POSIX_THREAD_ATTR_STACKSIZE `      | thread stack size address                        |
| TYM  |      | `_POSIX_TYPED_MEMORY_OBJECTS `       | typed memory objects (real-time)                 |
| XSI  | •    | `_XOPEN_UNIX `                       | X/Open interfaces                                |

Figure 2.5 POSIX.1 optional interface groups and codes



> NOTE: : 看了上述表格，不禁想**Symbolic constant**有什么用呢？通过在APUE的PDF版中查找`_POSIX_THREAD_ATTR_STACKADDR`，我得到了下面的一段描述，根据它就可以推测出这些**Symbolic constant**的作用了：

以`_POSIX_THREAD_ATTR_STACKADDR` （在上面的Figure 2.5中也介绍了这个constant）为例来进行说明。在APUE 12.3 Thread Attributes中有下面这样的一段话：

> Support for **thread stack attributes** is optional for a **POSIX-conforming operating system**, but is required if the system supports the **XSI option** in the **Single UNIX Specification**. At compile time, you can check whether your system supports each thread stack attribute by using the `_POSIX_THREAD_ATTR_STACKADDR` and `_POSIX_THREAD_ATTR_STACKSIZE` symbols. If one of these symbols is defined, then the system supports the corresponding **thread stack attribute**. Alternatively, you can check for support at runtime, by using the `_SC_THREAD_ATTR_STACKADDR` and
> `_SC_THREAD_ATTR_STACKSIZE` parameters to the `sysconf` function.

> NOTE: 
>
> 显然，可以根据这些**Symbolic constant**来确定所在系统是否支持改**Symbolic constant**所表示的功能；

#### POSIX Threads

[POSIX Threads](https://en.wikipedia.org/wiki/POSIX_Threads)

[The Open Group Base Specifications Issue 7, IEEE Std 1003.1](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)



#### C POSIX library header files

[C POSIX library](https://en.wikipedia.org/wiki/C_POSIX_library)

[C POSIX library header files](https://en.wikipedia.org/wiki/C_POSIX_library)

[Official List of headers in the POSIX library on opengroup.org](http://www.opengroup.org/onlinepubs/9699919799/idx/head.html)



### 2.2.3 The Single UNIX Specification

The Single UNIX Specification, a superset of the POSIX.1 standard, specifies additional interfaces that extend the functionality provided by the POSIX.1 specification. POSIX.1 is equivalent to the Base Specifications portion of the Single UNIX Specification.

> NOTE:
>
> [wikipedia The Open Group](https://en.wikipedia.org/wiki/The_Open_Group)
>
> [wikipedia Single UNIX Specification](https://en.wikipedia.org/wiki/Single_UNIX_Specification)

The *X/Open System Interfaces* (XSI) option in POSIX.1 describes optional interfaces and defines which optional portions of POSIX.1 must be supported for an implementation to be deemed *XSI conforming*. These include file synchronization, thread stack address and size attributes, thread process-shared synchronization, and the `_XOPEN_UNIX` symbolic constant (marked ‘‘SUS mandatory’’ in Figure 2.5). Only **XSI-conforming** implementations can be called **UNIX systems**.

> NOTE:
>
> [X/Open](https://en.wikipedia.org/wiki/X/Open)

The Single UNIX Specification is a publication of The Open Group, which was formed in 1996 as a merger of X/Open and the Open Software Foundation (OSF), both industry consortia. X/Open used to publish the X/Open Portability Guide, which adopted specific standards and filled in the gaps where functionality was missing. The goal of these guides was to improve application portability beyond what was possible by merely conforming to published standards.

> NOTE: 下面解释一些简称的含义

SUSv3： the third version of the Single UNIX Specification 

SUSv4： the forth version of the Single UNIX Specification 



## 2.3 UNIX System Implementations

The previous section described ISO C, IEEE POSIX, and the Single UNIX Specification — three standards originally created by independent organizations. Standards, however, are interface specifications. How do these standards relate to the real world? These standards are taken by vendors and turned into actual
implementations. In this book, we are interested in both these standards and their implementation.

### 2.3.1 UNIX System V Release 4

UNIX System V Release 4 (SVR4) was a product of AT&T’s UNIX System Laboratories (USL, formerly AT&T’s UNIX Software Operation). SVR4 merged functionality from AT&T UNIX System V Release 3.2 (SVR3.2), the SunOS operating system from Sun Microsystems, the 4.3BSD release from the University of California, and the Xenix system from Microsoft into one coherent operating system. (Xenix was originally developed from Version 7, with many features later taken from System V.) The SVR4 source code was released in late 1989, with the first end-user copies becoming available during 1990. SVR4 conformed to both the POSIX 1003.1 standard and the X/Open Portability Guide, Issue 3 (XPG3).

### 2.3.2 4.4BSD

### 2.3.3 FreeBSD

### 2.3.4 Linux

### 2.3.5 Mac OS X

### 2.3.6 Solaris



## 2.4 Relationship of Standards and Implementations

The standards that we’ve mentioned define a **subset** of any actual system. The focus of this book is on four real systems: FreeBSD 8.0, Linux 3.2.0, Mac OS X 10.6.8, and Solaris Although only Mac OS X and Solaris can call themselves UNIX systems, all four provide a similar programming environment. Because all four are POSIX compliant to varying degrees, we will also concentrate on the features required by the POSIX.1 standard, noting any differences between POSIX and the actual implementations of these four systems. Those features and routines that are specific to only a particular implementation are clearly marked. We’ll also note any features that are required on UNIX systems but are optional on other POSIX-conforming systems.

Be aware that the implementations provide backward compatibility for features in earlier releases, such as SVR3.2 and 4.3BSD. For example, Solaris supports both the POSIX.1 specification for nonblocking I/O (O_NONBLOCK) and the traditional System V method (`O_NDELAY`). In this text, we’ll use only the POSIX.1 feature, although we’ll mention the nonstandard feature that it replaces. Similarly, both SVR3.2 and 4.3BSD
provided reliable signals in a way that differs from the POSIX.1 standard. In Chapter 10 we describe only the POSIX.1 signal mechanism.



## 2.5  Limits

The implementations define many **magic numbers** and **constants**. Many of these have been hard coded into programs or were determined using ad hoc techniques. With the various standardization efforts that we’ve described, more portable methods are now provided to determine these **magic numbers** and **implementation-defined limits**, greatly improving the portability of software written for the UNIX environment.

Two types of limits are needed:

1、Compile-time limits (e.g., what’s the largest value of a short integer?)

2、Runtime limits (e.g., how many bytes in a filename?)





