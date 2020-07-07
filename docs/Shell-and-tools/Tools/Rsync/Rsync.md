# rsync

同步文件命令。

## 快速入门

### 两种工作方式

#### 第一种方式:服务器–客户端方式

在这种方式下， 服务端启动daemon 守护进程， 监听在端口 873， 并配置需要同步的模块。 然后客户端直接链接到873端口，通过认证，并同步。其中，同步用的账号和密码都是`rsync`专用的，在`rsync`配置文件中独立配置。 于系统账号无关。服务端运行`rsync`进程在daemon模式下， 客户端是普通的`rsync`进程。这种模式下，客户端只能同步服务端事先配置的模块（目录）。 不能访问其他路径。

#### 第二种方式:通过ssh链接

这种方式下， 无需事先配置远程服务端。本机 `rsync` 进程 直接通过 ssh 通道连接到远程， 并在远程ssh通道执行命令： `rsync –******`。

本地`rsync`进程和远程`rsync`进程通过自己的**标准输入**和**标准输出**互相通信。 具体的说就是，本地进程监听ssh通道的远程回显当做输入， 把自己的的输出通过ssh通道发送给远程。 而远程的`rsync`进程就一样， 也会监听ssh通道的输入，当做自己的输入，然后把自己的输出写入到ssh通道。于是， 远程rsync进程和本地rsync进程就通过这种方式同步文件。

这种情况，无需事先配置远程服务端， 只要你有ssh权限登录，就能同步。

同步的路径无限制。 当然只能访问你的ssh账号所能访问的目录。 如果你是root那就是无限制了。

#### 两种方式对比

这两种工作方式下，只是传输的通道不一样，第一种是直接走socket通道。 第二种是走的ssh通道。安全性显而易见。

两种方式下，`rsync`都使用自有协议进行同步，所以可以携带的参数都是没有区别的。



### 用法

`rsync` 的一般形式：

```shell
rsync  -options   SRC    DEST
```

**注意**，同步也是有方向的，因此需要明白从哪里同步到哪里。`rsync`命令肯定是将`SRC`复制到`DEST`。因为`SRC`，`DEST`即有可能在本地，也有可能在远程主机。



当通过ssh链接时， 有时需要指定ssh端口， 请使用这个方式：

```shell
rsync -options -e "ssh -p 10000"   SRC   DEST
```

**注意**，是否使用ssh通道，与上面这个参数没有必然联系。我这里指定了10000端口

| 命令                                                      | 说明                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| `rsync [OPTION]... SRC DEST`                              | 同步本地文件。当`SRC`和`DEST`路径信息都不包含有单个冒号"`:`"分隔符时就启动这种工作模式。如：`rsync -a /data /backup` |
| `rsync [OPTION]... SRC [USER@]HOST:DEST`                  | 使用一个**远程shell程序**(如`rsh`、`ssh`)来实现将本地机器的内容拷贝到远程机器。当`DSTT`路径地址包含单个冒号"`:`"分隔符时启动该模式。如：`rsync -avz *.c foo:src` |
| `rsync [OPTION]... [USER@]HOST:SRC DEST`                  | 使用一个**远程shell程序**(如`rsh`、`ssh`)来实现将远程机器的内容拷贝到本地机器。当`SRC`地址路径包含单个冒号"`:`"分隔符时启动该模式。如：`rsync -avz foo:src/bar /data` |
| `rsync [OPTION]... [USER@]HOST::SRC DEST`                 | 从**远程`rsync`服务器**中拷贝文件到本地机。当`SRC`路径信息包含"`::`"分隔符时启动该模式。如：`rsync -av root@172.16.78.192::www /databack` |
| `rsync [OPTION]... SRC [USER@]HOST::DEST`                 | 从本地机器拷贝文件到**远程`rsync`服务器**中。当DST路径信息包含"`::`"分隔符时启动该模式。如：`rsync -av /databack root@172.16.78.192::www` |
| `rsync [OPTION]... rsync://[USER@]HOST[:PORT]/SRC [DEST]` | 列远程机的文件列表。这类似于`rsync`传输，不过只要在命令中省略掉本地机信息即可。如：`rsync -v rsync://172.16.78.192/www` |

#### `rsync`如何区分这两种工作方式

| 命令格式             | 说明                                                         |
| -------------------- | ------------------------------------------------------------ |
| `[USER@]HOST:FOLDER` | 注意这里`HOST`和FOLDER之间用的是一个冒号， `rsync`由此判断使用ssh通道；这里，后面跟的直接是FOLDER的完整路径，需要是`USER`所能访问的地方。 |
| `[USER@]HOST::MODE`  | HOST于MODE之间有两个冒号，`rsync`由此判断使用服务器–客户端方式；`MODE`是远程daemon事先配置好的 模块名字。这里只能使用已经配好的模块名字，不能使用路径。 |



## Example

### 从local向remote同步



```shell
rsync local-file user@remote-host:remote-file
```

来源：维基百科[rsync](https://en.wikipedia.org/wiki/Rsync)；这是将本地推送到远程的例子。



```shell
rsync -vzacu  /home/wwwroot   root@198.***.***.***:/home/   --exclude  "wwwroot/index"   -e "ssh -p 22"
```

这是一个通过ssh通道从本地推送到远程的例子。 把本地的`/home/wwwroot` 推送到远程的`/home`下面。参数说明：

| 参数 | 说明                                                         |
| ---- | ------------------------------------------------------------ |
| `-z` | 表示传输过程压缩                                             |
| `-a` | 表示采用**归档模式**， 拷贝文件时，保留文件的**属主**，**用户组**，**权限**等等信息。 |
| `-c` | 表示校验文件checksum                                         |
| `-u` | 表示update，只传送更新的文件。`rsync`会比较文件的修改时间。只有较新的文件才会被同步。 |



### 符号链接

[Perform rsync while following sym links](https://serverfault.com/questions/245774/perform-rsync-while-following-sym-links)

[rsync and symbolic links](https://superuser.com/questions/799354/rsync-and-symbolic-links)

### Permission

[Rsync command issues, owner and group permissions doesn´t change](https://serverfault.com/questions/564385/rsync-command-issues-owner-and-group-permissions-doesn´t-change)





## 官网[rsync](https://rsync.samba.org/)

rsync is an [open source](http://www.opensource.org/) utility that provides fast incremental file transfer. rsync is freely available under the [GNU General Public License](https://rsync.samba.org/GPL.html) and is currently being maintained by [Wayne Davison](http://opencoder.net/).

### [Documentation](https://rsync.samba.org/documentation.html)

