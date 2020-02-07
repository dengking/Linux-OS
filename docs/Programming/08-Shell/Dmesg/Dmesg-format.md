[TOC]







# [How do I read the output of `dmesg` to determine how much memory a process is using when oom-killer is invoked?](https://unix.stackexchange.com/questions/103792/how-do-i-read-the-output-of-dmesg-to-determine-how-much-memory-a-process-is-us)











# [How to translate kernel's trap divide error rsp:2b6d2ea40450 to a source location?](https://stackoverflow.com/questions/25450311/how-to-translate-kernels-trap-divide-error-rsp2b6d2ea40450-to-a-source-locatio)

Customer reported an error in one of our programs caused by division by zero. We have only this VLM line:

```
kernel: myprog[16122] trap divide error rip:79dd99 rsp:2b6d2ea40450 error:0 
```

I do not believe there is core file for that.

I searched through the Internet to find how I can tell the line of the program that caused this division by zero, but so far I am failing.

I understand that `16122` is pid of the program, so that will not help me.

I suspect that `rsp:2b6d2ea40450` has something to do with the address of the line that caused the error (`0x2b6d2ea40450`) but is that true?

If it is then how can I translate it to a physical approximate location in the source assuming I can load debug version of myprog into gdb, and then request to show the context around this address...

Any, any help will be greatly appreciated!



## [A](https://stackoverflow.com/a/25450942)

`ip` is the **instruction pointer**, `rsp` is the **stack pointer**. The **stack pointer** is not too useful unless you have a core image or a running process.

You can use either `addr2line` or the `disassemble` command in `gdb` to see the line that got the error, based on the `ip`.

```C
$ cat divtest.c
main()
{
    int a, b;

    a = 1; b = a/0;
}

$ ./divtest
Floating point exception (core dumped)
$ dmesg|tail -1
[ 6827.463256] traps: divtest[3255] trap divide error ip:400504 sp:7fff54e81330
    error:0 in divtest[400000+1000]

$ addr2line -e divtest 400504
./divtest.c:5

$ gdb divtest
(gdb) disass /m 0x400504
Dump of assembler code for function main:
2       {
   0x00000000004004f0 :     push   %rbp
   0x00000000004004f1 :     mov    %rsp,%rbp

3               int a, b;
4       
5               a = 1; b = a/0;
   0x00000000004004f4 :     movl   $0x1,-0x4(%rbp)
   0x00000000004004fb :    mov    -0x4(%rbp),%eax
   0x00000000004004fe :    mov    $0x0,%ecx
   0x0000000000400503 :    cltd   
   0x0000000000400504 :    idiv   %ecx
   0x0000000000400506 :    mov    %eax,-0x8(%rbp)

6       }
   0x0000000000400509 :    pop    %rbp
   0x000000000040050a :    retq   

End of assembler dump.
```



# [How do you read a segfault kernel log message](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message)

This can be a very simple question, I'm am attempting to debug an application which generates the following **segfault error** in the `kern.log`

```
kernel: myapp[15514]: segfault at 794ef0 ip 080513b sp 794ef0 error 6 in myapp[8048000+24000]
```

Here are my questions:

1. Is there any documentation as to what are the diff error numbers on segfault, in this instance it is error 6, but i've seen error 4, 5
2. What is the meaning of the information `at bf794ef0 ip 0805130b sp bf794ef0 and myapp[8048000+24000]`?

So far i was able to compile with symbols, and when i do a `x 0x8048000+24000` it returns a symbol, is that the correct way of doing it? My assumptions thus far are the following:

- sp = stack pointer?
- ip = instruction pointer
- at = ????
- myapp[8048000+24000] = address of symbol?



## [A](https://stackoverflow.com/a/2549593)

## When the report points to a program, not a shared library

Run `addr2line -e myapp 080513b` (and repeat for the other **instruction pointer** values given) to see where the error is happening. Better, get a **debug-instrumented build**, and reproduce the problem under a debugger such as gdb.

## If it's a shared library

In the `libfoo.so[NNNNNN+YYYY]` part, the `NNNNNN` is where the library was loaded. Subtract this from the instruction pointer (`ip`) and you'll get the offset into the `.so` of the offending instruction. Then you can use `objdump -DCgl libfoo.so` and search for the instruction at that offset. You should easily be able to figure out which function it is from the asm labels. If the `.so` doesn't have optimizations you can also try using `addr2line -e libfoo.so <offset>`.

## What the error means

Here's the breakdown of the fields:

- `address` - the location in memory the code is trying to access (it's likely that `10` and `11` are offsets from a pointer we expect to be set to a valid value but which is instead pointing to `0`)
- `ip` - instruction pointer, ie. where the code which is trying to do this lives
- `sp` - stack pointer
- `error` - Architecture-specific flags; see `arch/*/mm/fault.c` for your platform.



***COMMENTS*** : 

- you gotta be wrong about error – [Dima Tisnek](https://stackoverflow.com/users/705086/dima-tisnek) [Sep 12 '12 at 12:25](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment16643238_2549593)

- 

  much better now – [Dima Tisnek](https://stackoverflow.com/users/705086/dima-tisnek) [Sep 30 '12 at 9:07](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment17080047_2549593)

- 

  Event for a shared lib, the "[8048000+24000]" part should give a hint where the crashing segment of the lib was mapped in memory. "readelf --segments mylib.so" lists these segments, and then you can calculate the EIP offset into the crashing segment and feed that to addr2line (or view it in "objdump -dgS"). – [oliver](https://stackoverflow.com/users/2148773/oliver) [Jun 13 '13 at 17:18](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment24725527_2549593)

- 

  I believe `0x8048000` is (probably) the address where the **text segment** was mapped, so you will want to pass `-j .text` to the `objdump` command. (At least, that is what I needed when diagnosing one of these just now.) – [Nemo](https://stackoverflow.com/users/768469/nemo) [Jun 5 '14 at 16:30](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment37108792_2549593)

- 

  @Charles Duffy If I ever see you I will hug like I never hugged a living soul. – [Baroudi Safwen](https://stackoverflow.com/users/4304746/baroudi-safwen) [Jan 11 '18 at 18:47](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment83409521_2549593)



## [A](https://stackoverflow.com/a/2179464)

Based on my limited knowledge, your assumptions are correct.

- `sp` = stack pointer
- `ip` = instruction pointer
- `myapp[8048000+24000]` = address

If I were debugging the problem I would modify the code to produce a core dump or log a [stack backtrace](https://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes/1925461#1925461) on the crash. You might also run the program under (or attach) GDB.

The error code is just the architectural error code for page faults and seems to be architecture specific. They are often documented in `arch/*/mm/fault.c` in the kernel source. My copy of `Linux/arch/i386/mm/fault.c` has the following definition for error_code:

- bit 0 == 0 means no page found, 1 means protection fault
- bit 1 == 0 means read, 1 means write
- bit 2 == 0 means kernel, 1 means user-mode

My copy of `Linux/arch/x86_64/mm/fault.c` adds the following:

- bit 3 == 1 means fault was an instruction fetch



- Beat me to it :) – [David Titarenco](https://stackoverflow.com/users/243613/david-titarenco) [Feb 1 '10 at 19:34](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126180_2179464)

- 

  The issue i have is that: 1) The application is segfaulting in a production environment, where symbols are stripped, all i have is just the logs 2) I'm trying to find that memory location in the development env, so at least i can see where it is crashing. – [Sullenx](https://stackoverflow.com/users/263800/sullenx) [Feb 1 '10 at 19:42](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126236_2179464)

- 1

  If you have the pre-stripped binary, try running it through nm or objdump. – [jschmier](https://stackoverflow.com/users/203667/jschmier) [Feb 1 '10 at 19:52](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126302_2179464) 

- 

  nm is pretty helpful, at least I have an idea where the crash happened. One last thing, what is an error 6? ... is there any table out there? – [Sullenx](https://stackoverflow.com/users/263800/sullenx) [Feb 1 '10 at 20:07](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126457_2179464)

- 

  I updated my answer to include the error code. – [jschmier](https://stackoverflow.com/users/203667/jschmier) [Feb 1 '10 at 20:47](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126777_2179464)

- 3

  segfault at 794ef0 ... sp 794ef0 - stack is obviously corrupted. – [Nikolai Fetissov](https://stackoverflow.com/users/106671/nikolai-fetissov) [Feb 1 '10 at 20:54](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126857_2179464)

- 

  Thank you, this is very helpful – [Sullenx](https://stackoverflow.com/users/263800/sullenx) [Feb 1 '10 at 20:56](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message#comment2126883_2179464)



## [A](https://stackoverflow.com/a/10918932)

> If it's a shared library
>
> **You're hosed, unfortunately; it's not possible to know where the libraries were placed in memory by the dynamic linker after-the-fact**.

Well, there is still a possibility to retrieve the information, not from the binary, but from the object. But you need the base address of the object. And this information still is within the coredump, in the `link_map` structure.

So first you want to import the `struct link_map` into GDB. So lets compile a program with it with debug symbol and add it to the GDB.

**link.c**

```c
#include <link.h>
toto(){struct link_map * s = 0x400;}
```

`get_baseaddr_from_coredump.sh`

```shell
#!/bin/bash

BINARY=$(which myapplication)

IsBinPIE ()
{
    readelf -h $1|grep 'Type' |grep "EXEC">/dev/null || return 0
    return 1
}

Hex2Decimal ()
{
    export number="`echo "$1" | sed -e 's:^0[xX]::' | tr '[a-f]' '[A-F]'`"
    export number=`echo "ibase=16; $number" | bc`
}

GetBinaryLength ()
{
    if [ $# != 1 ]; then
    echo "Error, no argument provided"
    fi
    IsBinPIE $1 || (echo "ET_EXEC file, need a base_address"; exit 0)
    export totalsize=0
    # Get PT_LOAD's size segment out of Program Header Table (ELF format)
    export sizes="$(readelf -l $1 |grep LOAD |awk '{print $6}'|tr '\n' ' ')"
    for size in $sizes
    do Hex2Decimal "$size"; export totalsize=$(expr $number + $totalsize); export totalsize=$(expr $number + $totalsize)
    done
    return $totalsize
}

if [ $# = 1 ]; then
    echo "Using binary $1"
    IsBinPIE $1 && (echo "NOT ET_EXEC, need a base_address..."; exit 0)
    BINARY=$1
fi

gcc -g3 -fPIC -shared link.c -o link.so

GOTADDR=$(readelf -S $BINARY|grep -E '\.got.plt[ \t]'|awk '{print $4}')

echo "First do the following command :"
echo file $BINARY
echo add-symbol-file ./link.so 0x0
read
echo "Now copy/paste the following into your gdb session with attached coredump"
cat <<EOF
set \$linkmapaddr = *(0x$GOTADDR + 4)
set \$mylinkmap = (struct link_map *) \$linkmapaddr
while (\$mylinkmap != 0)
if (\$mylinkmap->l_addr)
printf "add-symbol-file .%s %#.08x\n", \$mylinkmap->l_name, \$mylinkmap->l_addr
end
set \$mylinkmap = \$mylinkmap->l_next
end
```

it will print you the whole `link_map` content, within a set of GDB command.

It itself it might seems unnesseray but with the `base_addr` of the shared object we are about, you might get some more information out of an address by debuging directly the involved shared object in another GDB instance. Keep the first gdb to have an idee of the symbol.

NOTE : the script is rather incomplete i suspect you may **add** to the second parameter of add-symbol-file printed the sum with this value :

```shell
readelf -S $SO_PATH|grep -E '\.text[ \t]'|awk '{print $5}'
```

where `$SO_PATH` is the *first* argument of the add-symbol-file

Hope it helps

