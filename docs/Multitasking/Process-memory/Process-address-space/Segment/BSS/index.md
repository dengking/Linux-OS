# .bss

其实就是**Uninitialized data segment** 。

## wikipedia [.bss](https://en.wikipedia.org/wiki/.bss)

In [computer programming](https://en.wikipedia.org/wiki/Computer_programming), the **block starting symbol** (abbreviated to **.bss** or **bss**) is the portion of an [object file](https://en.wikipedia.org/wiki/Object_file), executable, or [assembly language](https://en.wikipedia.org/wiki/Assembly_language) code that contains [statically-allocated variables](https://en.wikipedia.org/wiki/Static_variable) that are declared but have not been assigned a value yet. It is often referred to as the "bss section" or "bss segment".

> NOTE: 
>
> static、uninitialized 

Typically only the length of the `bss` section, but no data, is stored in the [object file](https://en.wanweibaike.com/wiki-Object_file). The [program loader](https://en.wanweibaike.com/wiki-Program_loader) allocates memory for the `bss` section when it loads the program. By placing variables with no value in the `.bss` section, instead of the `.data` or `.rodata` section which require initial value data, the size of the object file is reduced.

On some platforms, some or all of the bss section is initialized to zeroes. [Unix-like](https://en.wanweibaike.com/wiki-Unix-like) systems and [Windows](https://en.wanweibaike.com/wiki-Windows) initialize the bss section to zero, allowing [C](https://en.wanweibaike.com/wiki-C_(programming_language)) and [C++](https://en.wanweibaike.com/wiki-C%2B%2B) statically allocated variables initialized to values represented with all bits zero to be put in the bss segment. Operating systems may use a technique called **zero-fill-on-demand** to efficiently implement the bss segment.[[1\]](https://en.wanweibaike.com/wiki-.bss#cite_note-1) In embedded software, the bss segment is mapped into memory that is initialized to zero by the C [run-time system](https://en.wanweibaike.com/wiki-Run-time_system) before `main()` is entered. Some C run-time systems may allow part of the bss segment not to be initialized; C variables must explicitly be placed into that portion of the bss segment.[[2\]](https://en.wanweibaike.com/wiki-.bss#cite_note-2)

### BSS in C

In [C](https://en.wanweibaike.com/wiki-C_(programming_language)), statically allocated objects without an explicit initializer are initialized to zero (for arithmetic types) or a null pointer (for pointer types). Implementations of C typically represent zero values and null pointer values using a bit pattern consisting solely of zero-valued bits (though this is not required by the C standard). Hence, the BSS segment typically includes all **uninitialized objects (both variables and [constants](https://en.wanweibaike.com/wiki-Constant_(computer_programming))) declared at file scope** (i.e., outside any function) as well as **uninitialized [static local variables](https://en.wanweibaike.com/wiki-Static_local_variable) ([local variables](https://en.wanweibaike.com/wiki-Local_variable) declared with the `static` [keyword](https://en.wanweibaike.com/wiki-Keyword_(computer_programming)))**; static local *constants* must be initialized at declaration, however, as they do not have a separate declaration, and thus are typically not in the BSS section, though they may be implicitly or explicitly initialized to zero. An implementation may also assign statically-allocated variables and constants initialized with a value consisting solely of zero-valued bits to the BSS section.

