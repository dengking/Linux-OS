# 25 gdb Text User Interface

> NOTE: 是在检索View both source and assembly发现的TUI





## Application

### View both source and assembly

#### stackoverflow [View Both Assembly and C code](https://stackoverflow.com/questions/9970636/view-both-assembly-and-c-code)

[A](https://stackoverflow.com/a/9971443)

You can run gdb in *Text User Interface* (TUI) mode:

```assembly
gdb -tui <your-binary>
(gdb) b main
(gdb) r
(gdb) layout split
```

The `layout split` command divides the window into two parts - one of them displaying the source code, the other one the corresponding assembly. A few others tricks:

- *set disassembly-flavor intel* - if your prefer intel notation
- *set print asm-demangle* - demangles C++ names in assembly view
- *ni* - next instruction
- *si* - step instruction

If you do not want to use the TUI mode (e.g. your terminal does not like it), you can always do:

```
x /12i $pc
```

which means *print 12 instructions from current program counter address* - this also works with the tricks above (demangling, stepping instructions, etc.).

The "`x /12i $pc`" trick works in both gdb and cgdb, whereas "layout split" only works in gdb.

Enjoy :)