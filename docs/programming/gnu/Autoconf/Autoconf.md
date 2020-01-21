# [Autoconf](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Top)

## [1 Introduction](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Introduction)

Autoconf is a tool for producing shell scripts that automatically configure software source code packages to adapt to many kinds of **Posix-like systems**. The **configuration scripts** produced by **Autoconf** are independent of Autoconf when they are run, so their users do not need to have Autoconf.

The **configuration scripts** produced by Autoconf require no manual user intervention when run; they do not normally even need an argument specifying the system type. Instead, they individually test for the presence of each **feature** that the software package they are for might need. (Before each check, they print a one-line message stating what they are checking for, so the user doesn't get too bored while waiting for the script to finish.) As a result, they deal well with systems that are hybrids or customized from the more common Posix variants. There is no need to maintain files that list the features supported by each release of each variant of Posix.

For each software package that Autoconf is used with, it creates a **configuration script** from a **template file** that lists the **system features** that the package needs or can use. After the shell code to recognize and respond to a **system feature** has been written, Autoconf allows it to be shared by many software packages that can use (or need) that feature. If it later turns out that the shell code needs adjustment for some reason, it needs to be changed in only one place; all of the configuration scripts can be regenerated automatically to take advantage of the updated code.

> NOTE: 
>
> Autoconf 的输入：template file，按照惯例，文件名为`configure.ac`
>
> Autoconf 的输出：configuration script，按照惯例，文件名为`configure`



## [2 The GNU Build System](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#The-GNU-Build-System)

- [2.1 Automake](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Automake)
- [2.2 Gnulib](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Gnulib)
- [2.3 Libtool](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Libtool)
- [2.4 Pointers](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Pointers)



## [3 Making configure Scripts](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Making-configure-Scripts)

The configuration scripts that Autoconf produces are by convention called `configure`. When run, configure creates several files, replacing configuration parameters in them with appropriate values. The files that configure creates are:

- one or more Makefile files, usually one in each subdirectory of the package (see [Makefile Substitutions](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Makefile-Substitutions));
- optionally, a C header file, the name of which is configurable, containing `#define` directives (see [Configuration Headers](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Configuration-Headers));
- a shell script called `config.status` that, when run, recreates the files listed above (see [config.status Invocation](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#config_002estatus-Invocation));
- an optional shell script normally called `config.cache` (created when using ‘`configure --config-cache`’) that saves the results of running many of the tests (see [Cache Files](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Cache-Files));
- a file called `config.log` containing any messages produced by compilers, to help debugging if configure makes a mistake.

To create a **configure script** with Autoconf, you need to write an Autoconf input file `configure.ac` (or `configure.in`) and run autoconf on it. If you write your own feature tests to supplement those that come with Autoconf, you might also write files called `aclocal.m4` and `acsite.m4`. If you use a C header file to contain `#define` directives, you might also run `autoheader`, and you can distribute the generated file `config.h.in` with the package.

Here is a diagram showing how the files that can be used in configuration are produced. Programs that are executed are suffixed by ‘`*`’. Optional files are enclosed in square brackets (‘`[]`’).  `autoconf` and `autoheader` also read the installed Autoconf macro files (by reading `autoconf.m4`).

Files used in preparing a software package for distribution, when using just Autoconf:

```
     your source files --> [autoscan*] --> [configure.scan] --> configure.ac
     
     configure.ac --.
                    |   .------> autoconf* -----> configure
     [aclocal.m4] --+---+
                    |   `-----> [autoheader*] --> [config.h.in]
     [acsite.m4] ---'
     
     Makefile.in
```

Additionally, if you use Automake, the following additional productions come into play:

```
     [acinclude.m4] --.
                      |
     [local macros] --+--> aclocal* --> aclocal.m4
                      |
     configure.ac ----'
     
     configure.ac --.
                    +--> automake* --> Makefile.in
     Makefile.am ---'
```





### [3.1 Writing configure.ac](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Writing-Autoconf-Input)

To produce a **configure script** for a software package, create a file called `configure.ac` that contains invocations of the **Autoconf macros** that test the **system features** your package needs or can use. **Autoconf macros** already exist to check for many features; see [Existing Tests](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Existing-Tests), for their descriptions. For most other features, you can use **Autoconf template macros** to produce **custom checks**; see [Writing Tests](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Writing-Tests), for information about them. For especially tricky or specialized features, `configure.ac` might need to contain some hand-crafted shell commands; see [Portable Shell Programming](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Portable-Shell). The `autoscan` program can give you a good start in writing `configure.ac` (see [autoscan Invocation](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#autoscan-Invocation), for more information).

- [Shell Script Compiler](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Shell-Script-Compiler): Autoconf as solution of a problem
- [Autoconf Language](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Autoconf-Language): Programming in Autoconf
- [Autoconf Input Layout](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Autoconf-Input-Layout): Standard organization of `configure.ac`

#### [3.1.1 A Shell Script Compiler](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Shell-Script-Compiler)

Just as for any other computer language, in order to properly program configure.ac in Autoconf you must understand *what* problem the language tries to address and *how* it does so.

The problem Autoconf addresses is that the world is a mess. After all, you are using Autoconf in order to have your package compile easily on all sorts of different systems, some of them being extremely hostile. Autoconf itself bears the price for these differences: configure must run on all those systems, and thus configure must limit itself to their lowest common denominator of features.

Naturally, you might then think of shell scripts; who needs autoconf? A set of properly written shell functions is enough to make it easy to write configure scripts by hand. Sigh! Unfortunately, even in 2008, where shells without any function support are far and few between, there are pitfalls to avoid when making use of them. Also, finding a Bourne shell that accepts shell functions is not trivial, even though there is almost always one on interesting porting targets.

So, what is really needed is some kind of compiler, `autoconf`, that takes an Autoconf program, `configure.ac`, and transforms it into a portable shell script, `configure`.

How does `autoconf` perform this task?

There are two obvious possibilities: creating a brand new language or extending an existing one. The former option is attractive: all sorts of optimizations could easily be implemented in the compiler and many rigorous checks could be performed on the Autoconf program (e.g., rejecting any non-portable construct). Alternatively, you can extend an existing language, such as the `sh` (Bourne shell) language.

Autoconf does the latter: it is a layer on top of `sh`. It was therefore most convenient to implement `autoconf` as a **macro expander**: a program that repeatedly performs **macro expansions** on text input, replacing macro calls with macro bodies and producing a pure `sh` script in the end. Instead of implementing a dedicated Autoconf **macro expander**, it is natural to use an existing **general-purpose macro language**, such as M4, and implement the extensions as a set of M4 macros.



#### [3.1.2 The Autoconf Language](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Autoconf-Language)

The Autoconf language differs from many other computer languages because it treats actual code the same as plain text. Whereas in C, for instance, data and instructions have different syntactic status, in Autoconf their status is rigorously the same. Therefore, we need a means to distinguish literal strings from text to be expanded: quotation.

When calling **macros** that take arguments, there must not be any white space between the macro name and the open parenthesis.

```
     AC_INIT ([oops], [1.0]) # incorrect
     AC_INIT([hello], [1.0]) # good
```

**Arguments** should be enclosed within the quote characters ‘`[`’ and ‘`]`’, and be separated by commas. Any leading blanks or newlines in arguments are ignored, unless they are quoted. You should always quote an argument that might contain a macro name, comma, parenthesis, or a leading blank or newline. This rule applies recursively for every macro call, including macros called from other macros. For more details on quoting rules, see [Programming in M4](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Programming-in-M4).

For instance:

```
     AC_CHECK_HEADER([stdio.h],
                     [AC_DEFINE([HAVE_STDIO_H], [1],
                        [Define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])
```

is quoted properly. You may safely simplify its quotation to:

```
     AC_CHECK_HEADER([stdio.h],
                     [AC_DEFINE([HAVE_STDIO_H], 1,
                        [Define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])
```

because ‘1’ cannot contain a macro call. Here, the argument of `AC_MSG_ERROR` must be quoted; otherwise, its comma would be interpreted as an argument separator. Also, the second and third arguments of ‘`AC_CHECK_HEADER`’ must be quoted, since they contain macro calls. The three arguments ‘`HAVE_STDIO_H`’, ‘`stdio.h`’, and ‘`Define to 1 if you have <stdio.h>.`’ **do not** need quoting, but if you unwisely defined a macro with a name like ‘`Define`’ or ‘`stdio`’ then they would need quoting. Cautious Autoconf users would keep the quotes, but many Autoconf users find such precautions annoying, and would rewrite the example as follows:

```
     AC_CHECK_HEADER(stdio.h,
                     [AC_DEFINE(HAVE_STDIO_H, 1,
                        [Define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])
```









#### [3.1.3 Standard configure.ac Layout](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Autoconf-Input-Layout)

The order in which `configure.ac` calls the Autoconf macros is not important, with a few exceptions. Every `configure.ac` must contain a call to `AC_INIT` before the checks, and a call to `AC_OUTPUT` at the end (see [Output](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Output)). Additionally, some macros rely on other macros having been called first, because they check previously set values of some variables to decide what to do. These macros are noted in the individual descriptions (see [Existing Tests](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#Existing-Tests)), and they also warn you when configure is created if they are called out of order.

To encourage consistency, here is a suggested order for calling the Autoconf macros. Generally speaking, the things near the end of this list are those that could depend on things earlier in it. For example, library functions could be affected by types and libraries.

```
     Autoconf requirements
     AC_INIT(package, version, bug-report-address)
     information on the package
     checks for programs
     checks for libraries
     checks for header files
     checks for types
     checks for structures
     checks for compiler characteristics
     checks for library functions
     checks for system services
     AC_CONFIG_FILES([file...])
     AC_OUTPUT
```

### [3.2 Using autoscan to Create configure.ac](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#autoscan-Invocation)



### [3.3 Using ifnames to List Conditionals](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#ifnames-Invocation)





- [3.4 Using autoconf to Create configure](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#autoconf-Invocation)
- [3.5 Using autoreconf to Update configure Scripts](https://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/autoconf.html#autoreconf-Invocation)