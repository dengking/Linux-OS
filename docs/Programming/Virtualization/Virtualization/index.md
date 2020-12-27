# [Virtualization](https://en.wikipedia.org/wiki/Virtualization)

> NOTE: 下面介绍各个层级的的virtualization

## Hardware virtualization

Main article: [Hardware virtualization](https://en.wikipedia.org/wiki/Hardware_virtualization)

See also: [Mobile virtualization](https://en.wikipedia.org/wiki/Mobile_virtualization)

## Desktop virtualization

*Main article:* [Desktop virtualization](https://en.wikipedia.org/wiki/Desktop_virtualization)

## Containerization

*Main article:* [Operating-system-level virtualization](https://en.wikipedia.org/wiki/Operating-system-level_virtualization)

> NOTE: 这是本章主要关注的

# [OS-level virtualization](https://en.wikipedia.org/wiki/OS-level_virtualization)

**OS-level virtualization** refers to an [operating system](https://en.wikipedia.org/wiki/Operating_system) paradigm in which the [kernel](https://en.wikipedia.org/wiki/Kernel_(computer_science)) allows the existence of multiple isolated [user space](https://en.wikipedia.org/wiki/User_space) instances. Such instances, called **containers** ([Solaris](https://en.wikipedia.org/wiki/Solaris_Containers), [Docker](https://en.wikipedia.org/wiki/Docker_(software))), **Zones** ([Solaris](https://en.wikipedia.org/wiki/Solaris_Containers)), **virtual private servers** ([OpenVZ](https://en.wikipedia.org/wiki/OpenVZ)), **partitions**, **virtual environments** (VEs), **virtual kernel** ([DragonFly BSD](https://en.wikipedia.org/wiki/Vkernel)), or **jails** ([FreeBSD jail](https://en.wikipedia.org/wiki/FreeBSD_jail) or [chroot jail](https://en.wikipedia.org/wiki/Chroot_jail)),[[1\]](https://en.wikipedia.org/wiki/OS-level_virtualization#cite_note-1) may look like real computers from the point of view of programs running in them. A computer program running on an ordinary operating system can see all resources (connected devices, files and folders, [network shares](https://en.wikipedia.org/wiki/Shared_resource), CPU power, quantifiable hardware capabilities) of that computer. However, programs running inside of a container can only see the container's contents and devices assigned to the container.

> NOTE: 常常听到的[Docker](https://en.wikipedia.org/wiki/Docker_(software))，**container**所使用的就是[OS-level virtualization](https://en.wikipedia.org/wiki/OS-level_virtualization)

On [Unix-like](https://en.wikipedia.org/wiki/Unix-like) operating systems, this feature can be seen as an advanced implementation of the standard [chroot](https://en.wikipedia.org/wiki/Chroot) mechanism, which changes the apparent root folder for the current running process and its children. In addition to isolation mechanisms, the kernel often provides [resource-management](https://en.wikipedia.org/wiki/Resource_management_(computing)) features to limit the impact of one container's activities on other containers.

> NOTE:
>
> linux kernel特性[Linux namespaces](http://man7.org/linux/man-pages/man7/namespaces.7.html)用于支持isolation；
>
> linux kernel特性[Linux control groups](http://man7.org/linux/man-pages/man7/cgroups.7.html)用于支持[resource-management](https://en.wikipedia.org/wiki/Resource_management_(computing))；

The term *"container,"* while most popularly referring to OS-level virtualization systems, is sometimes ambiguously used to refer to fuller [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine) environments operating in varying degrees of concert with the host OS, e.g. [Microsoft's](https://en.wikipedia.org/wiki/Microsoft) *"[Hyper-V](https://en.wikipedia.org/wiki/Hyper-V) Containers."*



# [List of Linux containers](https://en.wikipedia.org/wiki/List_of_Linux_containers)

