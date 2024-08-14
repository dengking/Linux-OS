# docker



## docker [Get started](https://docs.docker.com/get-started/) # [Overview](https://docs.docker.com/get-started/)

### What is a container?

To summarize, a container is a runnable instance of an image. You can create, start, stop, move, or delete a container using the DockerAPI or CLI.

> NOTE: 如process 和 program的关系
>



### What is a container image?

When running a container, it uses an isolated filesystem. This custom filesystem is provided by a container image. Since the image contains the container’s filesystem, it must contain everything needed to run an application - all dependencies, configurations, scripts, binaries, etc. The image also contains other configuration for the container, such as environment variables, a default command to run, and other metadata.



## docker [Get started](https://docs.docker.com/get-started/) # [Containerize an application](https://docs.docker.com/get-started/02_our_app/)

```shell
$ docker build -t getting-started .
```



```shell
$ docker run -dp 3000:3000 getting-started
```



## docker [Get started](https://docs.docker.com/get-started/) # [Update the application](https://docs.docker.com/get-started/03_updating_app/)



```shell
$ docker ps
```



```shell
$ docker stop <the-container-id>
```



```shell
$ docker rm <the-container-id>
```



```shell
$ docker rm -f <the-container-id>
```



```shell
$ docker run -dp 3000:3000 getting-started
```



## docker [Get started](https://docs.docker.com/get-started/) # [Persist the DB](https://docs.docker.com/get-started/05_persisting_data/)



### The container’s filesystem

When a container runs, it uses the various layers from an image for its filesystem. Each container also gets its own “scratch space” to create/update/remove files. Any changes won’t be seen in another container, *even if* they are using the same image.



```shell
$ docker exec <container-id> cat /data.txt
```



```shell
$ docker rm -f <container-id>
```



### Container volumes

With the previous experiment, we saw that each container starts from the image definition each time it starts. While containers can create, update, and delete files, those changes are lost when the container is removed and all changes are isolated to that container. With volumes, we can change all of this.

[Volumes](https://docs.docker.com/storage/volumes/) provide the ability to connect specific filesystem paths of the container back to the host machine. If a directory in the container is mounted, changes in that directory are also seen on the host machine. If we mount that same directory across container restarts, we’d see the same files.

There are two main types of volumes. We will eventually use both, but we will start with **named volumes**.

### Persist the todo data

As mentioned, we are going to use a **named volume**. Think of a named volume as simply a bucket of data. Docker maintains the physical location on the disk and you only need to remember the name of the volume. Every time you use the volume, Docker will make sure the correct data is provided.



```shell
$ docker volume create todo-db
```



```shell
$ docker rm -f <id>
```

Start the todo app container, but add the `-v` flag to specify a volume mount. We will use the named volume and mount it to `/etc/todos`, which will capture all files created at the path.

```shell
$ docker run -dp 3000:3000 -v todo-db:/etc/todos getting-started
```

### Dive into the volume



```shell
$ docker volume inspect
```



## docker [Get started](https://docs.docker.com/get-started/) # Use bind mounts

```shell
$ docker run --name=compiler --hostname=53a6604b6b54 --mac-address=02:42:c0:a8:0a:02 --env=PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin --volume=/data/share/cloud/:/home/svn --privileged -p 5005:5005 --restart=no --runtime=runc -t mirrors.tencent.com/nds-compile/compiler-env /bin/bash
```





## docker [Get started](https://docs.docker.com/get-started/) # [Multi container apps](https://docs.docker.com/get-started/07_multi_container/)

In general, **each container should do one thing and do it well.**

And there are more reasons. So, we will update our application to work like this:

![Todo App connected to MySQL container](https://docs.docker.com/get-started/images/multi-app-architecture.png)

### Container networking

Simply remember this rule...

> If two containers are on the same network, they can talk to each other. If they aren’t, they can’t.



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

