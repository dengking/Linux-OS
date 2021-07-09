# [Autotools Mythbuster](https://autotools.io/index.html)

# [Chapter 1. Configuring The Build — autoconf](https://autotools.io/autoconf/index.html)

Configuring the build consists of running a series of tests to identify the **build environment** and the presence of the required tools and libraries. It is a crucial step in allowing portability between different operating systems to detect this build environment system. In the autotools chain, this is done by the **autoconf** tool.

The **autoconf** tool translates a `configure.ac` file, written in a mixture of m4 and shell scripting, into a `configure` POSIX shell script that executes the tests that determines what the build environment is.



## [1. M4sh](https://autotools.io/autoconf/m4sh.html)

The language used to write the `configure.ac` is called *M4sh*, to make clear that it's based off both [sh](https://en.wikipedia.org/wiki/Unix_shell) and the macro language [M4](https://www.gnu.org/software/m4/).

## [2. Canonical Systems](https://autotools.io/autoconf/canonical.html)

When using autoconf, there are three *system definitions* (or *machine definitions*) that are used to identify the “actors” in the build process; each definition relates to a similarly-named variable which will be illustrated in detail later. These three definitions are:

- host (`CHOST`)

  The system that is going to run the software once it is built, which is the main actor. Once the software has been built, it will execute on this particular system.

- build (`CBUILD`)

  The system where the build process is being executed. For most uses this would be the same as the host system, but in case of cross-compilation the two obviously differ.

- target (`CTARGET`)

  The system against which the software being built will run on. This actor only exists, or rather has a meaning, when the software being built may interact specifically with a system that differs from the one it's being executed on (our *host*). This is the case for compilers, debuggers, profilers and analyzers and other tools in general.

To identify the current actors involved in the build process, autoconf provides three macros that take care of finding the so-called “canonical” values (see [Section 2.1, “The System Definition Tuples”](https://autotools.io/autoconf/canonical.html#autoconf.canonical.tuples) for their format): `AC_CANONICAL_HOST`, `AC_CANONICAL_BUILD` and `AC_CANONICAL_TARGET`. These three macros then provide to the configure script the sh variables with the name of the actor (`$host`, `$build` and `$target`), and three parameters with the same name to the `configure` script so that the user can override the default discovered values.

The most basic autoconf based build systems won't need to know any of these values, at least directly. Some other tools, such as libtool, will require discovery of canonical systems by themselves. Since adding these macros unconditionally adds direct and indirect code to the `configure` script (and a dependency on the two support files `config.sub` and `config.guess`); it is recommended not to call them unconditionally.

It is actually quite easy to decide whether canonical system definitions are needed or not. We just have to look for the use of the related actor variable. For instance if the `configure.ac` script uses the `$build` variable, we would need to call `AC_CANONICAL_BUILD` to discover its value. If the system definition variables are used in a macro instead, we should use the `AC_REQUIRE` macro to ensure that they are executed before entering. Don't fear calling them in more than one place. See [Section 6.2, “Once-Expansion”](https://autotools.io/autoconf/macros.html#autoconf.macros.once) for more details.

One common mistake is to “go all the way” and always use the `AC_CANONICAL_TARGET` macro, or its misnamed predecessor `AC_CANONICAL_SYSTEM`. This is particularly a problem; because most of the software will not have a *target* actor at all. This actor is only meaningful when the software that is being built manages data that is specific to a different system than the one it is being executed on (the *host* system).

In practice, the only places where the *target* actor is meaningful are to the parts of a compile toolchain: assemblers, linkers, compilers, debuggers, profilers, analysers, … For the rest of the software, the presence of an extraneous `--target` option to `configure` is likely to just be confusing. Especially for software that processes the output of the script to identify some information about the package being built.

### 2.1. The System Definition Tuples

The *system definitions* used by autoconf (but also by other packages like GCC and Binutils) are simple tuples in the form of strings. These are designed to provide, in a format easy to parse with “glob masks”; the major details that describe a **computer system**.

The number of elements in these tuples is variable, for some uses that only deal with very low-level code, there can be just a single element, the system architecture (`i386`, `x86_64`, `powerpc`, …); others will have two, defining either the operating system or, most often for definition pairs, the executable format (`elf`, `coff`, …). These two formats though are usually, only related to components of the toolchain and not to autoconf directly.

The tuples commonly used with autoconf are triples and quadruples, which define three components: *architecture*, *vendor* and *operating system*. These three components usually map directly into the triples, but for quadruple you have to split the operating system into *kernel* and *userland* (usually the C library).

While the architecture is most obvious; and operating systems differ slightly from one another (still being probably the most important data), the *vendor* value is usually just ignored. It is meant to actually be the vendor of the hardware system, rather than the vendor of the software, although presently it is mostly used by distributions to brand their toolchain (`i386-redhat-linux-gnu`) or their special systems (`i386-gentoo-freebsd7.0`) and by vendors that provide their own specific toolchain (`i686-apple-darwin9`).

Most operating systems don't split their definitions further in kernel and userland because they only work as an “ensemble”: FreeBSD, (Open)Solaris, Darwin, … There are, though, a few operating systems that have a split between kernel and userland, being managed by different projects or even being replaceable independently. This is the case for instance of Linux, which can use (among others) the GNU C Library (GNU/Linux) or uClibc, which become respectively `*-linux-gnu` and `*-linux-uclibc`.

Also, most operating systems using triples also have a single standardised version for both kernel and userland, and thus provide it as a suffix to the element (`*-freebsd7.0`, `*-netbsd4.0`). For a few operating systems, this value might differ from the one that is used as the “product version” used in public. For instance Solaris 10 uses as a definition `*-solaris2.10` and Apple's Mac OS X 10.5 uses `*-darwin9`.

### 2.2. When To Use System Definitions

*To be extended*

## [3. Adding Options](https://autotools.io/autoconf/arguments.html)

## [4. Finding Libraries](https://autotools.io/autoconf/finding.html)

## [5. Custom Autoconf Tests](https://autotools.io/autoconf/custom-tests.html)

## [6. Autoconf Building Blocks: Macros](https://autotools.io/autoconf/macros.html)

## [7. Caching Results](https://autotools.io/autoconf/caching.html)





