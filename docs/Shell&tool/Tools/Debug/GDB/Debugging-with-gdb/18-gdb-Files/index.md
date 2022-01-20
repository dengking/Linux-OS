# 18 gdb Files



## 18.1 Commands to Specify Files



### `exec-file  [ filename ]`



### `symbol-file [ filename ]`



### `add-symbol-file filename address`

The `add-symbol-file` command reads additional **symbol table** information from the file `filename`. You would use this command when `filename` has been dynamically loaded (by some other means) into the program that is running.



> NOTE: 是在阅读[Load Shared library Symbols](https://www.thegeekstuff.com/2014/03/few-gdb-commands/)时，发现的这个command，它让我想起来了有时候`glibc`抛出exception导致program core dump。在`Shell-and-tools\Tools\Debug\GDB\Debugging-with-gdb\GDB-Command-Reference.md`中收录了这部分内容。

