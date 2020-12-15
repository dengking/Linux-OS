# Symbol of shared library



## Symbol exported by a shared library

1) stackoverflow [How do I view the list of functions a Linux shared library is exporting?](https://stackoverflow.com/questions/4514745/how-do-i-view-the-list-of-functions-a-linux-shared-library-is-exporting)



[A](https://stackoverflow.com/a/4514781)

What you need is `nm` and its `-D` option:

```shell
$ nm -D /usr/lib/libopenal.so.1
.
.
.
00012ea0 T alcSetThreadContext
000140f0 T alcSuspendContext
         U atanf
         U calloc
.
.
.
```

Exported sumbols are indicated by a `T`. Required symbols that must be loaded from other shared objects have a `U`. Note that the symbol table does not include just functions, but exported variables as well.

See the `nm` [manual page](http://linux.die.net/man/1/nm) for more information.

[A](https://stackoverflow.com/a/31210206)

On a MAC, you need to use `nm *.o | c++filt`, as there is no `-C` option in `nm`.

2) stackoverflow [How do i find out what all symbols are exported from a shared object?](https://stackoverflow.com/questions/1237575/how-do-i-find-out-what-all-symbols-are-exported-from-a-shared-object)

[A](https://stackoverflow.com/a/1250597)

Do you have a "shared object" (usually a shared library on AIX), a UNIX shared library, or a Windows DLL? These are all different things, and your question conflates them all :-(

- For an AIX shared object, use `dump -Tv /path/to/foo.o`.
- For an ELF shared library, use `readelf -Ws /path/to/libfoo.so`, or (if you have GNU nm) `nm -D /path/to/libfoo.so`.
- For a non-ELF UNIX shared library, please state *which* UNIX you are interested in.
- For a Windows DLL, use `dumpbin /EXPORTS foo.dll`.



## TODO: Find where a shared library symbol defined on a live system

### stackexchange [Find where is a shared library symbol defined on a live system / list all symbols exported on a system](https://unix.stackexchange.com/questions/103744/find-where-is-a-shared-library-symbol-defined-on-a-live-system-list-all-symbol)