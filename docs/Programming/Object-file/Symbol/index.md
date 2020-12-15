# Symbol

每个object file都有一个symbol table，这是非常重要的。

## Classification

### Dynamic symbol

主要是shared library的。

`nm -D`

### External symbol

`nm -g`

这是在阅读 [Find where is a shared library symbol defined on a live system / list all symbols exported on a system](https://unix.stackexchange.com/questions/103744/find-where-is-a-shared-library-symbol-defined-on-a-live-system-list-all-symbol) 时，发现的。

## nm

这是Linux OS中读取symbol的主要工具，在`./nm`中进行了介绍。

