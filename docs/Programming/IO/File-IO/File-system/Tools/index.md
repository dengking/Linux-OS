# File system command

下面是维基百科总结的 [Unix](https://en.wikipedia.org/wiki/Unix) [command-line interface](https://en.wikipedia.org/wiki/Command-line_interface) **programs and** [shell builtins](https://en.wikipedia.org/wiki/Shell_builtin) 中**File system** commands（链接: https://en.wikipedia.org/wiki/Df_(Unix) ）: 

| command                                                | 简介 |
| ------------------------------------------------------ | ---- |
| [cat](https://en.wikipedia.org/wiki/Cat_(Unix))        |      |
| [chmod](https://en.wikipedia.org/wiki/Chmod)           |      |
| [chown](https://en.wikipedia.org/wiki/Chown)           |      |
| [chgrp](https://en.wikipedia.org/wiki/Chgrp)           |      |
| [cksum](https://en.wikipedia.org/wiki/Cksum)           |      |
| [cmp](https://en.wikipedia.org/wiki/Cmp_(Unix))        |      |
| [cp](https://en.wikipedia.org/wiki/Cp_(Unix))          |      |
| [dd](https://en.wikipedia.org/wiki/Dd_(Unix))          |      |
| [du](https://en.wikipedia.org/wiki/Du_(Unix))          |      |
| [df](https://en.wikipedia.org/wiki/Df_(Unix))          |      |
| [file](https://en.wikipedia.org/wiki/File_(command))   |      |
| [fuser](https://en.wikipedia.org/wiki/Fuser_(Unix))    |      |
| [ln](https://en.wikipedia.org/wiki/Ln_(Unix))          |      |
| [ls](https://en.wikipedia.org/wiki/Ls)                 |      |
| [mkdir](https://en.wikipedia.org/wiki/Mkdir)           |      |
| [mv](https://en.wikipedia.org/wiki/Mv)                 |      |
| [pax](https://en.wikipedia.org/wiki/Pax_(command))     |      |
| [pwd](https://en.wikipedia.org/wiki/Pwd)               |      |
| [rm](https://en.wikipedia.org/wiki/Rm_(Unix))          |      |
| [rmdir](https://en.wikipedia.org/wiki/Rmdir)           |      |
| [split](https://en.wikipedia.org/wiki/Split_(Unix))    |      |
| [tee](https://en.wikipedia.org/wiki/Tee_(command))     |      |
| [touch](https://en.wikipedia.org/wiki/Touch_(command)) |      |
| [type](https://en.wikipedia.org/wiki/Type_(Unix))      |      |
| [umask](https://en.wikipedia.org/wiki/Umask)           |      |

## `du`

### [du(1) - Linux man page](https://linux.die.net/man/1/du)

Summarize disk usage of each FILE, recursively for directories.

> NOTE: 对象是file



### Example: 查看文件夹大小-并按大小进行排序

cnblogs [du-查看文件夹大小-并按大小进行排序](https://www.cnblogs.com/0616--ataozhijia/p/6364185.html) :

 `*` 可以将当前目录下所有文件的大小给列出来。那要将这些列出来的文件按照从大到小的方式排序呢？

```shell
jack@jiaobuchong:~$ du -sh * | sort -nr 
833M    installed-software 
452K    Documents 
284K    learngit 
170M    Desktop 
161M    Downloads 
112K    session 

```

> NOTE: 可以看出，上述排序是错误的，因为它没有考虑 单位

 找sort 来帮个忙就可以了。呵呵！这个排序不正常哦，都是因为`-h`参数的原因:

```SHELL
jack@jiaobuchong:~$ du -s * | sort -nr  
852756  installed-software 
173868  Desktop 
164768  Downloads 
4724    Pictures 
3236    program_pratice 

```

> NOTE: 排序支持，相当于统一了量纲

`du -s * | sort -nr | head` 选出排在前面的10个，

`du -s * | sort -nr | tail` 选出排在后面的10个。



### Example: Finding largest file

cyberciti [Finding largest file recursively on Linux bash shell using find](https://www.cyberciti.biz/faq/linux-find-largest-file-in-directory-recursively-using-find-du/) :

One can only list files and skip the directories with the find command instead of using the du command, sort command and NA command combination:

```shell
$ sudo find / -type f -printf "%s\t%p\n" | sort -n | tail -1
$ find $HOME -type f -printf '%s %p\n' | sort -nr | head -10
```



## `df`

### [df(1) - Linux man page](https://linux.die.net/man/1/df)

df - report file system disk space usage

> NOTE: 对象是disk