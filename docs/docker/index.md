# docker

## 安装

cnblogs [docker学习（一）ubuntu上安装docker](https://www.cnblogs.com/walker-lin/p/11214127.html)



## 实战

```shell
docker pull ubuntu:18.04
sudo !!
mkdir -p workspace/fuxi
cd workspace/fuxi/
docker run -it --mount src=`pwd`,target=/app/demo,type=bind ubuntu:18.04 bash
sudo !!
```

在启动的时候，指定磁盘映射。

```
docker commit 898e279df534 ubuntu:base
```



```sh
docker images
```

查看本地所有的镜像。