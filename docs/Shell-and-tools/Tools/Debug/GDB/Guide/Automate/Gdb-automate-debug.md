# Automate gdb debug

参考：

- [What are the best ways to automate a GDB debugging session?](https://stackoverflow.com/questions/10748501/what-are-the-best-ways-to-automate-a-gdb-debugging-session)
- [How to print every executed line in GDB automatically until a given breakpoint is reached?](https://stackoverflow.com/questions/6947389/how-to-print-every-executed-line-in-gdb-automatically-until-a-given-breakpoint-i)
- [gdb scripting: execute commands at selected breakpoint](https://stackoverflow.com/questions/13935443/gdb-scripting-execute-commands-at-selected-breakpoint)
- [Automate gdb: show backtrace at every call to function puts](https://stackoverflow.com/questions/2388799/automate-gdb-show-backtrace-at-every-call-to-function-puts)



所谓“automate gdb debug session”，是指充分利用gdb的scripting mechanism，而不使用interactive模式来进行debug。[What are the best ways to automate a GDB debugging session?](https://stackoverflow.com/questions/10748501/what-are-the-best-ways-to-automate-a-gdb-debugging-session)的提问者准确地表达了这种诉求：

> Does GDB have a built in **scripting mechanism**, should I code up an expect script, or is there an even better solution out there?
>
> I'll be sending the same sequence of commands every time and I'll be saving the output of each command to a file (most likely using GDB's built-in logging mechanism, unless someone has a better idea).



## `--batch --command`

### [Example](https://stackoverflow.com/a/10775939) 

Basically, in this example I wanted to get some variable values in particular places of the code; and have them output until the program crashes. So here is first a little program which is [guaranteed to crash](https://stackoverflow.com/questions/5028781/c-how-to-write-a-sample-code-that-will-crash-and-produce-dump-file) in a few steps, `test.c`:

```c
#include <stdio.h>
#include <stdlib.h>

int icount = 1; // default value

main(int argc, char *argv[])
{
  int i;

  if (argc == 2) {
    icount = atoi(argv[1]);
  }

  i = icount;
  while (i > -1) {
    int b = 5 / i;
    printf(" 5 / %d = %d \n", i, b );
    i = i - 1;
  }

  printf("Finished\n");
  return 0;
}
```

The only reason the program accepts command-line arguments is to be able to choose the number of steps before crashing - and to show that `gdb` ignores `--args` in batch mode. This I compile with:

```
gcc -g test.c -o test.exe
```

Then, I prepare the following script - the main trick here is to assign a `command` to each `breakpoint`, which will eventually `continue` (see also [Automate gdb: show backtrace at every call to function puts](https://stackoverflow.com/questions/2388799/automate-gdb-show-backtrace-at-every-call-to-function-puts)). This script I call `test.gdb`:

```shell
# http://sourceware.org/gdb/wiki/FAQ: to disable the
# "---Type <return> to continue, or q <return> to quit---"
# in batch mode:
set width 0
set height 0
set verbose off

# at entry point - cmd1
b main
commands 1
  print argc
  continue
end

# printf line - cmd2
b test.c:17
commands 2
  p i
  p b
  continue
end

# int b = line - cmd3
b test.c:16
commands 3
  p i
  p b
  continue
end

# show arguments for program
show args
printf "Note, however: in batch mode, arguments will be ignored!\n"

# note: even if arguments are shown;
# must specify cmdline arg for "run"
# when running in batch mode! (then they are ignored)
# below, we specify command line argument "2":
run 2     # run

#start # alternative to run: runs to main, and stops
#continue
```

Note that, if you intend to use it in batch mode, you have to "start up" the script at the end, with `run` or `start` or something similar.

With this script in place, I can call `gdb` in batch mode - which will generate the following output in the terminal:

```shell
$ gdb --batch --command=test.gdb --args ./test.exe 5
Breakpoint 1 at 0x804844d: file test.c, line 10.
Breakpoint 2 at 0x8048485: file test.c, line 17.
Breakpoint 3 at 0x8048473: file test.c, line 16.
Argument list to give program being debugged when it is started is "5".
Note, however: in batch mode, arguments will be ignored!

Breakpoint 1, main (argc=2, argv=0xbffff424) at test.c:10
10    if (argc == 2) {
$1 = 2

Breakpoint 3, main (argc=2, argv=0xbffff424) at test.c:16
16      int b = 5 / i;
$2 = 2
$3 = 134513899

Breakpoint 2, main (argc=2, argv=0xbffff424) at test.c:17
17      printf(" 5 / %d = %d \n", i, b );
$4 = 2
$5 = 2
 5 / 2 = 2 

Breakpoint 3, main (argc=2, argv=0xbffff424) at test.c:16
16      int b = 5 / i;
$6 = 1
$7 = 2

Breakpoint 2, main (argc=2, argv=0xbffff424) at test.c:17
17      printf(" 5 / %d = %d \n", i, b );
$8 = 1
$9 = 5
 5 / 1 = 5 

Breakpoint 3, main (argc=2, argv=0xbffff424) at test.c:16
16      int b = 5 / i;
$10 = 0
$11 = 5

Program received signal SIGFPE, Arithmetic exception.
0x0804847d in main (argc=2, argv=0xbffff424) at test.c:16
16      int b = 5 / i;
```

Note that while we specify command line argument 5, the loop still spins only two times (as is the specification of `run` in the `gdb` script); if `run` didn't have any arguments, it spins only once (the default value of the program) confirming that `--args ./test.exe 5` is ignored.

However, since now this is output in a single call, and without any user interaction, the command line output can easily be captured in a text file using `bash` redirection, say:

```
gdb --batch --command=test.gdb --args ./test.exe 5 > out.txt
```

There is also an example of using python for automating gdb in [c - GDB auto stepping - automatic printout of lines, while free running?](https://stackoverflow.com/a/6964213/277826)

Hope this helps,
Cheers!

### [Example](https://stackoverflow.com/a/2410442) : `break puts`

Try this instead:

```
set width 0
set height 0
set verbose off
start  # runs to main, so shared libraries are loaded
       # after you reach main, GDB should have libc symbols, "puts" among them
break puts
commands 1
backtrace
continue
end
```

If this doesn't work, please state operating system version.

EDIT: as osgx correctly points out, the other alternative is to add

```
set breakpoint pending on
```

before `break puts`

## 使用`.gdbinit`

### [Example](https://stackoverflow.com/a/10748611) 

`gdb` executes file `.gdbinit` after running. So you can add your commands to this file and see if it is OK for you. This is an example of `.gdbinit` in order to print backtrace for all `f()` calls:

```shell
set pagination off
set logging file gdb.txt
set logging on
file a.out
b f
commands
bt
continue
end
info breakpoints
r
set logging off
quit
```



## 使用`-ex`

### [Example](https://stackoverflow.com/a/46867839) 

If a -x with a file is too much for you, just use multiple `-ex`'s. This is an example to track a running program showing (and saving) the backtrace on crashes

```shell
sudo gdb -p $(pidof my-app) -batch \
  -ex "set logging on" \
  -ex continue \
  -ex "bt full" \
  -ex quit
```





## TO READ

[How to print every executed line in GDB automatically until a given breakpoint is reached?](https://stackoverflow.com/questions/6947389/how-to-print-every-executed-line-in-gdb-automatically-until-a-given-breakpoint-i)