# `addr2line`



## [addr2line(1) - Linux man page](https://linux.die.net/man/1/addr2line)





## stackoverflow [How to use the addr2line command in Linux?](https://stackoverflow.com/questions/7648642/how-to-use-the-addr2line-command-in-linux)



## `addr2line` shared library

### dedoimedo [**Linux cool hacks - Compilation 4**](https://www.dedoimedo.com/computers/linux-cool-hacks-4.html)

The one last extra tip is about translating addresses into file names and line numbers. [addr2line](http://linux.die.net/man/1/addr2line) translates addresses into file names and line numbers. Given an address in an executable or an offset in a section of a relocatable object, it uses the debugging information to figure out which file name and line number are associated with it.

```sh
addr2line <addr> -e <executable>
```

A geeky example; say you have a misbehaving program. And then you run it under a debugger and get a backtrace. Now, let's assume we have a problematic frame:

```sh
# C [libz.so.1+0xa910] gzdirect+0x28
```

All right, so we translate (-e tells us the name of the object). Works both ways. You can translate from offsets to functions and line numbers and vice versa. Again, this can be quite handy for debugging, but you must be familiar with the application and its source.

```C++
addr2line 0xa910 -e libz.so.1
/tmp/zlib/zlib-1.2.5/gzread.c:614
```

> NOTE: 
>
> 需要注意上述 `addr2line` 的入参是 `0xa910`，对应的是 `[libz.so.1+0xa910]`

```SH
addr2line -f -e libz.so.1.2.5 0xa910
gzdirect ? function name
/tmp/zlib/zlib-1.2.5/gzread.c:614
```

### narkive [using addr2line](https://comp.unix.programmer.narkive.com/mgToXbYQ/using-addr2line)

> NOTE: 
>
> 这篇文章所讨论的就是 `addr2line` shared library

This might help you or not, but in my memories, the `addr2line` tool wanted me to give the address relative to the base address for code not
in the "main program" ; ie. for a function pointer of a library X, the address would be ( address - dladdr(ptr).dli_saddr ) [pseudo-code]

### stackoverflow [How to map function address to function in *.so files](https://stackoverflow.com/questions/7556045/how-to-map-function-address-to-function-in-so-files)

> NOTE: 
>
> 这篇文章给出了例子，但是并不直观

### groups [addr2line and shared libraries](https://groups.google.com/g/comp.lang.ada/c/H03jssDoADQ)



### yenhuang [Address Sanitizer(Asan) & addr2line](https://yenhuang.gitbooks.io/android-development-note/content/native/address-sanitizer-and-addr2line.html)



## 我的实践

日志信息: 

```
02-15 13:55:59.963 26662 26662 I wrap.sh : SUMMARY: AddressSanitizer: stack-use-after-scope (/data/app/com.netease.lava.nertc.demo-L1N1d3COGQUwTE7FeLnNXw==/lib/arm64/libnertc_sdk.so+0x725613) 
```

使用`addr2line`: 

```shell
.\aarch64-linux-android-addr2line.exe -e D:\NetEase\G2\nertcsdk\src\lite\wrapper\android\build\intermediates\cmake\debug\obj\arm64-v8a\libnertc_sdk.so 0x725613
```

输出如下:

```C++
D:/NetEase/G2/nertcsdk/src/lite/engine/lite_engine.cpp:50
```

