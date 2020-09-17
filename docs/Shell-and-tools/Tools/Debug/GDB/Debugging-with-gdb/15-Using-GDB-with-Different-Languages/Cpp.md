# C++



## Breakpoint for member functions

### stackoverflow [breakpoint for member functions](https://stackoverflow.com/questions/35806129/c-gdb-breakpoint-for-member-functions)

```C++
class BST
{
    BST()
    ...
    private:
    int add((BST * root, BST *src);
}
```

[A](https://stackoverflow.com/a/35809049)

As Dark Falcon said, `break BST::add` should work if you don't have overloads.

You can also type:

```cpp
(gdb) break 'BST::add(<TAB>
```

(note the single quote). This should prompt GDB to perform tab-completion, and finish the line like so:

```cpp
(gdb) break 'BST::add(BST*, BST*)
```

and which point you can add the terminating `'`' and hit Enter to add the breakpoint.

> I can get a break point for the void display function

Function return type is not part of its signature and has *nothing* to do with what's happening.



## Show all members of a class

如何在gdb中，展示一个class的所有的member？可以使用如下命令：

### `ptype`

参见

- stackoverflow [How to list class methods in gdb?](https://stackoverflow.com/questions/3956024/how-to-list-class-methods-in-gdb) `#` [A](https://stackoverflow.com/a/3956133)
- `GDB\Debugging-with-gdb\16-Examining-the-Symbol-Table`



## `struct` 

使用如下命令:

### `ptype /o`

- [How do I show what fields a struct has in GDB?](https://stackoverflow.com/questions/1768620/how-do-i-show-what-fields-a-struct-has-in-gdb)
- `GDB\Debugging-with-gdb\16-Examining-the-Symbol-Table`



