# Run command



## Run command multiple times

### `for`

https://serverfault.com/a/273241：

For starters you can use a dummy `for` loop:

```sh
for i in `seq 10`; do command; done
```

Or equivalently as per JimB's suggestion, using the Bash builtin for generating sequences:

```sh
for i in {1..10}; do command; done
```

This iterates ten times executing `command` each time - it can be a pipe or a series of commands separated by `;` or `&&`. You can use the `$i` variable to know which iteration you're in.

If you consider this one-liner a script and so for some unspecified (but perhaps valid) reason undesireable you can implement it as a command, perhaps something like this on your `.bashrc` (untested):

```sh
#function run
run() {
    number=$1
    shift
    for i in `seq $number`; do
      $@
    done
}
```

Usage:

```sh
run 10 command
```

Example:

```sh
run 5 echo 'Hello World!'
```

https://stackoverflow.com/a/3737773

```sh
for run in {1..10}
do
  command
done
```

Or as a one-liner for those that want to copy and paste easily:

```sh
for run in {1..10}; do command; done
```

### `seq`

[Shell下重复多次执行命令](https://zhuanlan.zhihu.com/p/28023094):

```text
seq 10 | xargs -i date
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
Fri Jul 21 14:20:55 CST 2017
```

seq 生成一个1-10的数组。`xargs`兴高彩烈的拿着这个数组，准备将数组元素传给`date` 命令做参数。`xargs -i`会查找命令字符串中的`{}`，并用数组元素替换`{}`。但是`xargs`一看，WTF！命令里面居然没有占位符。那好吧，就执行10遍命令，让参数随风去吧。

## Run command periodically

### watch

#### [man 1 watch](https://linux.die.net/man/1/watch)



#### [Shell下重复多次执行命令](https://zhuanlan.zhihu.com/p/28023094)



```shell
watch -n 1 date
```



### while true; do ... ; sleep ...; done

[Shell下重复多次执行命令](https://zhuanlan.zhihu.com/p/28023094)

```text
$ while true; do date; sleep 1; done
Fri Jul 21 14:20:24 CST 2017
Fri Jul 21 14:20:25 CST 2017
Fri Jul 21 14:20:26 CST 2017
Fri Jul 21 14:20:27 CST 2017
```