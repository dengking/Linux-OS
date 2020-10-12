# `ldd`



## `ldd`



https://en.wikipedia.org/wiki/Ldd_(Unix)

https://linux.die.net/man/1/ldd



## stackexchange [How to find out the dynamic libraries executables loads when run?](https://unix.stackexchange.com/questions/120015/how-to-find-out-the-dynamic-libraries-executables-loads-when-run)

### [A1](https://unix.stackexchange.com/a/120017)

`ldd` 



### [A2](https://unix.stackexchange.com/a/220110)

```shell
readelf -d $executable | grep 'NEEDED'
```



Can be used if you can't run the executable, e.g. if it was cross compiled, or if you don't trust it:

> In the usual case, ldd invokes the standard dynamic linker (see ld.so(8)) with the LD_TRACE_LOADED_OBJECTS environment variable set to 1, which causes the linker to display the library dependencies. Be aware, however, that in some circumstances, some versions of ldd may attempt to obtain the dependency information by directly executing the program. Thus, you should never employ ldd on an untrusted executable, since this may result in the execution of arbitrary code.

总结：上面这段话指出了`readelf`和`ldd`在这种场景下的使用差异所在；

Example:

```shell
readelf -d /bin/ls | grep 'NEEDED'
```

Sample ouptut:

```
 0x0000000000000001 (NEEDED)             Shared library: [libselinux.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libacl.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
```

Note that libraries can depend on other libraries, so now you need to find the dependencies.

A naive approach that often works is:

```
$ locate libselinux.so.1
/lib/i386-linux-gnu/libselinux.so.1
/lib/x86_64-linux-gnu/libselinux.so.1
/mnt/debootstrap/lib/x86_64-linux-gnu/libselinux.so.1
```

but the more precise method is to understand the `ldd` search path / cache. I think `ldconfig` is the way to go.

Choose one, and repeat:

```
readelf -d /lib/x86_64-linux-gnu/libselinux.so.1 | grep 'NEEDED'
```

Sample output:

```
0x0000000000000001 (NEEDED)             Shared library: [libpcre.so.3]
0x0000000000000001 (NEEDED)             Shared library: [libdl.so.2]
0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
0x0000000000000001 (NEEDED)             Shared library: [ld-linux-x86-64.so.2]
```

And so on.

See also:

- [Determine direct shared object dependencies of a Linux binary? | Stack Overflow](https://stackoverflow.com/questions/6242761/how-do-i-find-the-direct-shared-object-dependencies-of-a-linux-elf-binary)
- [How can I find the dynamic libraries required by an ELF Binary in C++? | Stack Overflow](https://stackoverflow.com/questions/22612735/how-can-i-find-the-dynamic-libraries-required-by-an-elf-binary-in-c)
- [How to know which dynamic libraries are needed by an ELF? | Stack Overflow](https://stackoverflow.com/questions/1172649/how-to-know-which-dynamic-libraries-are-needed-by-an-elf)

**`/proc/<pid>/maps` for running processes**

[Mentioned by Basile](https://unix.stackexchange.com/a/373184/32558), this is useful to find all the libraries currently being used by **running executables**. E.g.:

```shell
sudo awk '/\.so/{print $6}' /proc/1/maps | sort -u
```

shows all currently loaded dynamic dependencies of `init` (PID `1`):

```
/lib/x86_64-linux-gnu/ld-2.23.so
/lib/x86_64-linux-gnu/libapparmor.so.1.4.0
/lib/x86_64-linux-gnu/libaudit.so.1.0.0
/lib/x86_64-linux-gnu/libblkid.so.1.1.0
/lib/x86_64-linux-gnu/libc-2.23.so
/lib/x86_64-linux-gnu/libcap.so.2.24
/lib/x86_64-linux-gnu/libdl-2.23.so
/lib/x86_64-linux-gnu/libkmod.so.2.3.0
/lib/x86_64-linux-gnu/libmount.so.1.1.0
/lib/x86_64-linux-gnu/libpam.so.0.83.1
/lib/x86_64-linux-gnu/libpcre.so.3.13.2
/lib/x86_64-linux-gnu/libpthread-2.23.so
/lib/x86_64-linux-gnu/librt-2.23.so
/lib/x86_64-linux-gnu/libseccomp.so.2.2.3
/lib/x86_64-linux-gnu/libselinux.so.1
/lib/x86_64-linux-gnu/libuuid.so.1.3.0
```

This method also shows libraries opened with `dlopen`, tested with [this minimal setup](https://github.com/cirosantilli/cpp-cheat/blob/71ab01c5de024d9d97f0e2f0698cbee6c6a9c87a/shared-library/basic/dlopen.c#L16) hacked up with a `sleep(1000)` on Ubuntu 18.04.

See also: [How to see the currently loaded shared objects in Linux? | Super User](https://superuser.com/questions/310199/see-currently-loaded-shared-objects-in-linux/1243089)





