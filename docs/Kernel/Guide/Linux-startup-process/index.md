# Linux startup process

1、本节标题的含义是: "LinuxOS的启动过程"。

2、对这个过程有一个大致的了解是由必要的

## wikipedia [Linux startup process](https://en.wikipedia.org/wiki/Linux_startup_process)

**Linux startup process** is the multi-stage initialization process performed during [booting](https://en.wikipedia.org/wiki/Booting) a [Linux](https://en.wikipedia.org/wiki/Linux) installation. It is in many ways similar to the [BSD](https://en.wikipedia.org/wiki/BSD) and other [Unix](https://en.wikipedia.org/wiki/Unix)-style boot processes, from which it derives.

Booting a Linux installation involves multiple stages and software components, including [firmware](https://en.wikipedia.org/wiki/Firmware) initialization, execution of a [boot loader](https://en.wikipedia.org/wiki/Boot_loader), loading and startup of a [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel) image, and execution of various [startup scripts](https://en.wikipedia.org/wiki/Startup_scripts) and [daemons](https://en.wikipedia.org/wiki/Daemon_(computing)). For each of these stages and components there are different variations and approaches; for example, [GRUB](https://en.wikipedia.org/wiki/GNU_GRUB), [LILO](https://en.wikipedia.org/wiki/LILO_(boot_loader)), [SYSLINUX](https://en.wikipedia.org/wiki/SYSLINUX) or [Loadlin](https://en.wikipedia.org/wiki/Loadlin) can be used as boot loaders, while the **startup scripts** can be either traditional [init](https://en.wikipedia.org/wiki/Init)-style, or the system configuration can be performed through modern alternatives such as [systemd](https://en.wikipedia.org/wiki/Systemd) or [Upstart](https://en.wikipedia.org/wiki/Upstart_(software)).

> NOTE: 
> 1、当今的Linux的boot loader、init process都是有多种可选的，作为programmer，我们需要对init process的主流的方案有一个大致的了解
>
> 

### Overview

> NOTE: 
> 1、下面的内容基本上包含了programmer需要了解的内容

Early stages of the **Linux startup process** depend very much on the computer architecture. IBM PC compatible hardware is one architecture Linux is commonly used on; on these systems, the [BIOS](https://en.wikipedia.org/wiki/BIOS) plays an important role, which might not have exact analogs on other systems. In the following example, IBM PC compatible hardware is assumed:

1、The **BIOS** performs **startup tasks** specific to the actual [hardware](https://en.wikipedia.org/wiki/Computer_hardware) platform. Once the hardware is [enumerated](https://en.wikipedia.org/wiki/Enumeration) and the hardware which is necessary for boot is initialized correctly, the **BIOS** loads and executes the boot code from the configured **boot device**.

2、The **boot loader** often presents the user with a menu of possible boot options and has a default option, which is selected after some time passes. Once the selection is made, the **boot loader** loads the **kernel** into **memory**, supplies it with some parameters and gives it control.

3、The **kernel**, if compressed, will decompress itself. It then sets up **system functions** such as essential hardware and memory paging, and calls `start_kernel()`which performs the majority of **system setup** (interrupts, the rest of memory management, device and driver initialization, etc.). It then starts up, separately, the [idle process](https://en.wikipedia.org/wiki/Idle_process), scheduler, and the [init process](https://en.wikipedia.org/wiki/Init_process), which is executed in [user space](https://en.wikipedia.org/wiki/User_space).

> NOTE: 
>
> 1、init process是运行在user space的，以root权限运行，这非常重要
>
> 2、下面对init process的介绍是需要programmer了解的

4、The init either consists of scripts that are executed by the shell (sysv, bsd, runit) or configuration files that are executed by the binary components (systemd, upstart). Init has specific levels (sysv, bsd) or targets (systemd), each of which consists of specific set of **services** (daemons). These provide various non-operating system services and structures and form the user environment. A typical server environment starts a web server, database services, and networking.



5、The typical desktop environment begins with a daemon, called the display manager, that starts a graphic environment which consists of a graphical server that provides a basic underlying graphical stack and a login manager that provides the ability to enter credentials and select a session. After the user has entered the correct credentials, the session manager starts a session. A session is a set of programs such as UI elements (panels, desktops, applets, etc.) which, together, can form a complete desktop environment.

#### Shutdown

> NOTE: 
>
> 1、下面还介绍了shutdown过程

On shutdown, init is called to close down all user space functionality in a controlled manner. Once all the other processes have terminated, init makes a system call to the kernel instructing it to shut the system down.

### Boot loader phase

> NOTE: 
>
> 1、programmer可以不了解

### Kernel phase

> NOTE: 
>
> 1、有必要了解

The [kernel](https://en.wikipedia.org/wiki/Linux_kernel) in Linux handles all operating system processes, such as [memory management](https://en.wikipedia.org/wiki/Memory_management), task [scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing)), [I/O](https://en.wikipedia.org/wiki/I/O), [interprocess communication](https://en.wikipedia.org/wiki/Interprocess_communication), and overall system control. 

This is loaded in two stages – in the first stage, the kernel (as a compressed image file) is loaded into memory and decompressed, and a few fundamental functions such as basic memory management are set up. Control is then switched one final time to the main kernel start process. Once the kernel is fully operational – and as part of its startup, upon being loaded and executing – the kernel looks for an [init process](https://en.wikipedia.org/wiki/Init_process) to run, which (separately) sets up a **user space** and the processes needed for a user environment and ultimate login. The kernel itself is then allowed to go idle, subject to calls from other processes.

For some platforms (like ARM 64-bit), kernel decompression has to be performed by the **boot loader** instead.

#### Kernel loading stage

The kernel is typically loaded as an image file, compressed into either [zImage or bzImage](https://en.wikipedia.org/wiki/Vmlinux) formats with [zlib](https://en.wikipedia.org/wiki/Zlib). A routine at the head of it does a minimal amount of hardware setup, decompresses the image fully into [high memory](https://en.wikipedia.org/wiki/High_memory), and takes note of any [RAM disk](https://en.wikipedia.org/wiki/RAM_disk) if configured.[[3\]](https://en.wikipedia.org/wiki/Linux_startup_process#cite_note-ibm_description-3) It then executes **kernel startup** via `./arch/i386/boot/head` and the `startup_32 ()` (for x86 based processors) process.



#### Kernel startup stage

The **startup function** for the kernel (also called the **swapper** or process 0) establishes [memory management](https://en.wikipedia.org/wiki/Memory_management) (paging tables and memory paging), detects the type of [CPU](https://en.wikipedia.org/wiki/Central_processing_unit) and any additional functionality such as [floating point](https://en.wikipedia.org/wiki/Floating_point) capabilities, and then switches to non-architecture specific Linux kernel functionality via a call to `start_kernel()`.[[4\]](https://en.wikipedia.org/wiki/Linux_startup_process#cite_note-4)



### Early user space

Main article: [initramfs](https://en.wikipedia.org/wiki/Initramfs)

[initramfs](https://en.wikipedia.org/wiki/Initramfs), also known as *early user space*, has been available since version 2.5.46 of the Linux kernel,[[6\]](https://en.wikipedia.org/wiki/Linux_startup_process#cite_note-6) with the intent to replace as many functions as possible that previously the kernel would have performed during the start-up process. Typical uses of early user space are to detect what [device drivers](https://en.wikipedia.org/wiki/Device_driver) are needed to load the main user space file system and load them from a [temporary filesystem](https://en.wikipedia.org/wiki/Temporary_filesystem).

### Init process

> NOTE: 
>
> 1、这是需要programmer掌握的，在`Operating-system-service-management`章节对其进行介绍
>
> 2、这是Linux startup process执行的，不是由user执行的
>
> 3、我们常说的"开机自启动"就是在这个环节

Once the kernel has started, it starts the [init](https://en.wikipedia.org/wiki/Init) process. Historically this was the "SysV init", which was just called "init". More recent Linux distributions are likely to use one of the more modern alternatives such as "systemd".

Basically, these are grouped as [operating system service-management](https://en.wikipedia.org/wiki/Operating_System_service_management).



