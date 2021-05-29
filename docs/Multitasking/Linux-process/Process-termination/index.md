# Process termination

进程终止。

## stackoverflow [What is the difference between exit() and abort()?](https://stackoverflow.com/questions/397075/what-is-the-difference-between-exit-and-abort)

In C and C++, what is the difference between `exit()` and `abort()`? I am trying to end my program after an error (not an exception).

### [A](https://stackoverflow.com/a/397081)

[`abort()`](http://en.cppreference.com/w/c/program/abort) exits your program without calling functions registered using [`atexit()`](http://en.cppreference.com/w/c/program/atexit) first, and without calling objects' destructors first. [`exit()`](http://en.cppreference.com/w/c/program/exit) does both before exiting your program. It does not call destructors for automatic objects though. So

```c++
A a;
void test() { 
    static A b;
    A c;
    exit(0);
}
```

Will destruct `a` and `b` properly, but will not call destructors of `c`. `abort()` wouldn't call destructors of neither objects. As this is unfortunate, the C++ Standard describes an alternative mechanism which ensures properly termination:

> Objects with **automatic storage duration** are all destroyed in a program whose function `main()`contains **no automatic objects** and executes the call to `exit()`. Control can be transferred directly to such a `main()` by throwing an exception that is caught in `main()`.

```
struct exit_exception { 
   int c; 
   exit_exception(int c):c(c) { } 
};

int main() {
    try {
        // put all code in here
    } catch(exit_exception& e) {
        exit(e.c);
    }
}
```

Instead of calling `exit()`, arrange that code `throw exit_exception(exit_code);` instead.

### [A](https://stackoverflow.com/a/397079)

**abort** sends a `SIGABRT` signal, **exit** just closes the application performing normal cleanup.

You can handle an **abort** signal however you want, but the default behavior is to close the application as well with an error code.

**abort** will not perform object destruction of your **static** and **global** members, but **exit** will.

Of course though when the application is completely closed the operating system will free up any unfreed memory and other resources.

In both **abort** and **exit** program termination (assuming you didn't override the default behavior), the return code will be returned to the parent process that started your application.

See the following example:

```c
SomeClassType someobject;

void myProgramIsTerminating1(void)
{
  cout<<"exit function 1"<<endl;
}

void myProgramIsTerminating2(void)
{
  cout<<"exit function 2"<<endl;
}

int main(int argc, char**argv)
{
  atexit (myProgramIsTerminating1);
  atexit (myProgramIsTerminating2);
  //abort();
  return 0;
}
```

Comments:

- If **abort** is uncommented: nothing is printed and the destructor of someobject will not be called.
- If **abort** is commented like above: someobject destructor will be called you will get the following output:

> exit function 2
> exit function 1

## TODO

geeksforgeeks [exit(), abort() and assert()](https://www.geeksforgeeks.org/understanding-exit-abort-and-assert/) 

stackoverflow [Execute function on exit or program end](https://stackoverflow.com/questions/44540679/execute-function-on-exit-or-program-end)

[std::set_terminate](http://www.cplusplus.com/reference/exception/set_terminate/)

[ON_EXIT(3)](http://man7.org/linux/man-pages/man3/on_exit.3.html)

[ATEXIT(3)](http://man7.org/linux/man-pages/man3/atexit.3.html)

stackexchange [When does a process terminate in UNIX?](https://unix.stackexchange.com/questions/232061/when-does-a-process-terminate-in-unix)

