

# UNIX standardization and implementations

本节梳理[Unix operating system](https://en.wikipedia.org/wiki/Unix)和[Unix-like operating system](https://en.wikipedia.org/wiki/Unix-like)之间的标准、演进、关系等。对于这些标准有必要了解一下，因为在很多书籍，文章中都会见到这些标准。本节的内容主要源自于[Advanced Programming in the UNIX® Environment, Third Edition](http://www.apuebook.com/cover3e.html)的chapter 2 UNIX Standardization and Implementations

## Introduction

Much work has gone into standardizing the UNIX programming environment and the C programming language.

In this chapter we first look at the various standardization efforts that have been under way over the past two and a half decades. We then discuss the effects of these UNIX programming standards on the operating system implementations that are described in this book. An important part of all the standardization efforts is the specification of various limits that each implementation must define, so we look at these limits and the various ways to determine their values.

## UNIX Standardization

### ISO C

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



### IEEE POSIX

> NOTE: 本节介绍了IEEE POSIX standard的演进过程，这些历史可以pass掉。下面关于IEEE POSIX的一些网站链接：
>
> - [wikipedia POSIX](https://en.wikipedia.org/wiki/POSIX)
> - [POSIX official site](http://get.posixcertified.ieee.org/)

POSIX is a family of standards initially developed by the IEEE (Institute of Electrical and Electronics Engineers). POSIX stands for Portable Operating System Interface. It originally referred only to the IEEE Standard 1003.1-1988 — the operating system interface — but was later extended to include many of the standards and draft standards with the 1003 designation, including the shell and utilities (1003.2).

Because the 1003.1 standard specifies an *interface* and not an *implementation*, no distinction is made between **system calls** and **library functions**. All the routines in the standard are called *functions*.

#### POSIX Threads

[POSIX Threads](https://en.wikipedia.org/wiki/POSIX_Threads)

[The Open Group Base Specifications Issue 7, IEEE Std 1003.1](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)



#### C POSIX library header files

[C POSIX library](https://en.wikipedia.org/wiki/C_POSIX_library)

[C POSIX library header files](https://en.wikipedia.org/wiki/C_POSIX_library)

[Official List of headers in the POSIX library on opengroup.org](http://www.opengroup.org/onlinepubs/9699919799/idx/head.html)



### The Single UNIX Specification

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



## UNIX System Implementations

The previous section described ISO C, IEEE POSIX, and the Single UNIX Specification — three standards originally created by independent organizations. Standards, however, are interface specifications. How do these standards relate to the real world? These standards are taken by vendors and turned into actual
implementations. In this book, we are interested in both these standards and their implementation.

### UNIX System V Release 4

UNIX System V Release 4 (SVR4) was a product of AT&T’s UNIX System Laboratories (USL, formerly AT&T’s UNIX Software Operation). SVR4 merged functionality from AT&T UNIX System V Release 3.2 (SVR3.2), the SunOS operating system from Sun Microsystems, the 4.3BSD release from the University of California, and the Xenix system from Microsoft into one coherent operating system. (Xenix was originally developed from Version 7, with many features later taken from System V.) The SVR4 source code was released in late 1989, with the first end-user copies becoming available during 1990. SVR4 conformed to both the POSIX 1003.1 standard and the X/Open Portability Guide, Issue 3 (XPG3).

### 4.4BSD

### FreeBSD

### Linux

### Mac OS X

### Solaris



## Relationship of Standards and Implementations

The standards that we’ve mentioned define a **subset** of any actual system. The focus of this book is on four real systems: FreeBSD 8.0, Linux 3.2.0, Mac OS X 10.6.8, and Solaris Although only Mac OS X and Solaris can call themselves UNIX systems, all four provide a similar programming environment. Because all four are POSIX compliant to varying degrees, we will also concentrate on the features required by the POSIX.1 standard, noting any differences between POSIX and the actual implementations of these four systems. Those features and routines that are specific to only a particular implementation are clearly marked. We’ll also note any features that are required on UNIX systems but are optional on other POSIX-conforming systems.

Be aware that the implementations provide backward compatibility for features in earlier releases, such as SVR3.2 and 4.3BSD. For example, Solaris supports both the POSIX.1 specification for nonblocking I/O (O_NONBLOCK) and the traditional System V method (`O_NDELAY`). In this text, we’ll use only the POSIX.1 feature, although we’ll mention the nonstandard feature that it replaces. Similarly, both SVR3.2 and 4.3BSD
provided reliable signals in a way that differs from the POSIX.1 standard. In Chapter 10 we describe only the POSIX.1 signal mechanism.



## [man STANDARDS(7)](http://man7.org/linux/man-pages/man7/standards.7.html)

> NOTE: 这是linux文档中对standard的介绍。