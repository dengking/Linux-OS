[TOC]



# [What the Linux kernel's messages about segfaulting programs mean on 64-bit x86](https://utcc.utoronto.ca/~cks/space/blog/linux/KernelSegfaultMessageMeaning)

For quite a while the Linux kernel has had [an option to log a kernel message about every faulting user program](https://utcc.utoronto.ca/~cks/space/blog/linux/ShuttingUpSegfaultSyslogs), and it probably defaults to on in your Linux distribution. I've seen these messages fly by for years, but for reasons beyond the scope of this entry I've recently wanted to understand what they mean in some moderate amount of detail.

I'll start with a straightforward and typical example, one that I see every time I build and test `Go` (as this is a test case that is supposed to crash):

> ```
> testp[19288]: segfault at 0 ip 0000000000401271 sp 00007fff2ce4d210 error 4 in testp[400000+98000]
> ```

The meaning of this is:

- '`testp[19288]`' is the faulting program and its PID
- '`segfault at 0`' tells us the memory address (in hex) that caused the segfault when the program tried to access it. Here the address is 0, so we have a **null dereference** of some sort.
- '`ip 0000000000401271`' is the value of the **instruction pointer** at the time of the fault. This should be the instruction that attempted to do the invalid memory access. In 64-bit x86, this will be register `%rip` (useful for inspecting things in GDB and elsewhere).
- '`sp 00007fff2ce4d210`' is the value of the stack pointer. In 64-bit x86, this will be `%rsp`.
- '`error 4`' is the **page fault error code** bits from [traps.h](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/include/asm/traps.h#n148) in hex, as usual, and will almost always be at least 4 (which means 'user-mode access'). A value of 4 means it was **a read of an unmapped area**, such as address 0, while a value of 6 (4+2) means it was **a write of an unmapped area**.
- '`in testp[400000+98000]`' tells us the specific virtual memory area that *the instruction pointer* is in, specifying which file it is (here it's the executable), the starting address that VMA is mapped at (`0x400000`), and the size of the mapping (`0x98000`).

With a faulting address of 0 and an error code of 4, we know this particular segfault is a read of a **null pointer**.

Here's two more error messages:

> ```
> bash[12235]: segfault at 1054808 ip 000000000041d989 sp 00007ffec1f1cbd8 error 6 in bash[400000+f4000]
> ```

'Error 6' means a write to an **unmapped user address**, here `0x1054808`.

> ```
> bash[11909]: segfault at 0 ip 00007f83c03db746 sp 00007ffccbeda010 error 4 in libc-2.23.so[7f83c0350000+1c0000]
> ```

Error 4 and address 0 is a null pointer read but this time it's in some `libc` function, not in bash's own code, since it's reported as 'in `libc-2.23.so`[...]'. Since I looked at the core dump, I can tell you that this was in `strlen()`.

On 64-bit x86 Linux, you'll get a somewhat different message if the problem is actually with the instruction being executed, not the address it's referencing. For example:

> ```
> bash[2848] trap invalid opcode ip:48db90 sp:7ffddc8879e8 error:0 in bash[400000+f4000]
> ```

There are a number of such trap types set up in [traps.c](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/kernel/traps.c#n313). Two notable additional ones are 'divide error', which you get if you do an integer division by zero, and 'general protection', which you can get for certain extremely wild pointers (one case I know of is when your 64-bit x86 address is not in ['canonical form'](https://en.wikipedia.org/wiki/X86-64#Virtual_address_space_details)). Although these fields are formatted slightly differently, most of them mean the same thing as in segfaults. The exception is '`error:0`', which is not a page fault error code. I don't understand the relevant kernel code enough to know what it means, but if I'm reading between the lines correctly in [entry_64.txt](https://www.kernel.org/doc/Documentation/x86/entry_64.txt), then it's either 0 (the usual case) or an error code from the CPU. [Here](https://wiki.osdev.org/Exceptions) is one possible list of exceptions that get error codes.

Sometimes these messages can be a little bit unusual and surprising. Here is a silly sample program and the error it produces when run. The code:

> ```
> #include <stdio.h>
> int main(int argc, char **argv) {
>    int (*p)();
>    p = 0x0;
>    return printf("%d\n", (*p)());
> }
> ```

If compiled (without optimization is best) and run, this generates the kernel message:

> ```
> a.out[3714]: segfault at 0 ip           (null) sp 00007ffe872aa418 error 14 in a.out[400000+1000]
> ```

The '`(null)`' bit turns out to be expected; it's what the general kernel `printf()` function generates when asked to print something as a pointer and it's null (as seen [here](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/lib/vsprintf.c#n1852)). In our case the instruction pointer is 0 (null) because we've made a subroutine call through a null pointer and thus we're trying to execute code at address 0. I don't know why the 'in ...' portion says that we're in the executable (although in this case the call actually was there).

The error code of 14 is in hex, which means that as bits it's 010100. This is a user mode read of an unmapped area (our usual '4' case), but it's an instruction fetch, not a normal data read or write. Any error 14s are a sign of some form of mangled function call or a return to a mangled address because the stack has been mashed.

(These bits turn out to come straight from [the CPU's page fault IDT](https://wiki.osdev.org/Exceptions#Page_Fault).)

For 64-bit x86 Linux kernels (and possibly for 32-bit x86 ones as well), the code you want to look at is `show_signal_msg` in [fault.c](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/mm/fault.c), which prints the general 'segfault at ..' message, `do_trap` and`do_general_protection` in [traps.c](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/kernel/traps.c), which print the 'trap ...' messages, and `print_vma_addr` in[memory.c](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/mm/memory.c), which prints the 'in ...' portion for all of these messages.

### Sidebar: The various error code bits as numbers

| +1          | protection fault in a mapped area (eg writing to a read-only mapping) |
| ----------- | ------------------------------------------------------------ |
| +2          | write (instead of a read)                                    |
| +4          | user mode access (instead of kernel mode access)             |
| +8          | use of reserved bits in the page table entry detected (the kernel will panic if this happens) |
| +16 (+0x10) | fault was an instruction fetch, not data read or write       |
| +32 (+0x20) | 'protection keys block access' (don't ask me)                |

Hex 0x14 is 0x10 + 4; (hex) 6 is 4 + 2. Error code 7 (0x7) is 4 + 2 + 1, a user-mode write to a read-only mapping, and is what you get if you attempt to write to a string constant in C:

> ```
> char *ex = "example";
> int main(int argc, char **argv) {
>    *ex = 'E';
> }
> ```

Compile and run this and you will get:

> ```
> a.out[8832]: segfault at 400540 ip 0000000000400499 sp 00007ffce6831490 error 7 in a.out[400000+1000]
> ```

It appears that the program code always gets loaded at 0x400000 for ordinary programs, although I believe that shared libraries can have their location randomized.

PS: Per a comment in the kernel source, all accesses to addresses above the end of user space will be labeled as 'protection fault in a mapped area' whether or not there are actual page table entries there. The kernel does this so you can't work out where its memory pages are by looking at the error code.

(I believe that user space normally ends around 0x07fffffffffff, per [mm.txt](https://www.kernel.org/doc/Documentation/x86/x86_64/mm.txt), although see the comments about `TASK_SIZE_MAX` in [processor.h](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/include/asm/processor.h) and also [page_64_types.h](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/arch/x86/include/asm/page_64_types.h).)