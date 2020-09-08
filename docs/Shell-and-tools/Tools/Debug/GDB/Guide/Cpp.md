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