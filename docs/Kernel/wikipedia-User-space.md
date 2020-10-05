# [User space](https://en.wikipedia.org/wiki/User_space)

A modern computer [operating system](https://en.wikipedia.org/wiki/Operating_system) usually segregates [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) into **kernel space** and **user space**.[[a\]](https://en.wikipedia.org/wiki/User_space#cite_note-1) Primarily, this separation serves to provide [memory protection](https://en.wikipedia.org/wiki/Memory_protection) and hardware protection from malicious or errant software behaviour.

Kernel space is strictly reserved for running a privileged [operating system kernel](https://en.wikipedia.org/wiki/Operating_system_kernel), kernel extensions, and most [device drivers](https://en.wikipedia.org/wiki/Device_driver). In contrast, user space is the memory area where [application software](https://en.wikipedia.org/wiki/Application_software) and some drivers execute.



## Overview 

The term **userland** (or user space) refers to all code that runs outside the operating system's **kernel**.[[1\]](https://en.wikipedia.org/wiki/User_space#cite_note-1) Userland usually refers to the various programs and [libraries](https://en.wikipedia.org/wiki/Library_(computing)) that the operating system uses to interact with the **kernel**: software that performs [input/output](https://en.wikipedia.org/wiki/Input/output), manipulates [file system](https://en.wikipedia.org/wiki/File_system) objects, [application software](https://en.wikipedia.org/wiki/Application_software), etc.

Each user space [process](https://en.wikipedia.org/wiki/Process_(computing)) normally runs in its own [virtual memory](https://en.wikipedia.org/wiki/Virtual_memory) space, and, unless explicitly allowed, cannot access the memory of other processes. This is the basis for [memory protection](https://en.wikipedia.org/wiki/Memory_protection) in today's mainstream operating systems, and a building block for [privilege separation](https://en.wikipedia.org/wiki/Privilege_separation). A **separate user mode** can also be used to build efficient virtual machines – see [Popek and Goldberg virtualization requirements](https://en.wikipedia.org/wiki/Popek_and_Goldberg_virtualization_requirements). With enough privileges, processes can request the kernel to map part of another process's memory space to its own, as is the case for [debuggers](https://en.wikipedia.org/wiki/Debugger). Programs can also request [shared memory](https://en.wikipedia.org/wiki/Shared_memory_(interprocess_communication)) regions with other processes, although other techniques are also available to allow [inter-process communication](https://en.wikipedia.org/wiki/Inter-process_communication).

## Various layers within Linux, also showing separation between the **userland** and [kernel space](https://en.wikipedia.org/wiki/Kernel_space)

### User mode 

#### User applications

For example, [bash](https://en.wikipedia.org/wiki/Bourne-again_shell), [LibreOffice](https://en.wikipedia.org/wiki/LibreOffice), [GIMP](https://en.wikipedia.org/wiki/GIMP), [Blender](https://en.wikipedia.org/wiki/Blender_(software)), [0 A.D.](https://en.wikipedia.org/wiki/0_A.D._(video_game)), [Mozilla Firefox](https://en.wikipedia.org/wiki/Mozilla_Firefox), etc.

#### Low-level system components: 

System [daemons](https://en.wikipedia.org/wiki/Daemon_(computing)):
[systemd](https://en.wikipedia.org/wiki/Systemd), [runit](https://en.wikipedia.org/wiki/Runit), logind, networkd, [PulseAudio](https://en.wikipedia.org/wiki/PulseAudio), ...

***SUMMARY*** : 需要注意的是，systemd是运行在user mode，而不是kernel mode；

#### [C standard library](https://en.wikipedia.org/wiki/C_standard_library) 

`open()`, `exec()`, `sbrk()`, `socket()`, `fopen()`, `calloc()`, ... (up to 2000 [subroutines](https://en.wikipedia.org/wiki/Subroutine))
[glibc](https://en.wikipedia.org/wiki/GNU_C_Library) aims to be [POSIX](https://en.wikipedia.org/wiki/POSIX)/[SUS](https://en.wikipedia.org/wiki/Single_UNIX_Specification)-compatible, [uClibc](https://en.wikipedia.org/wiki/UClibc) targets embedded systems, [bionic](https://en.wikipedia.org/wiki/Bionic_(software)) written for [Android](https://en.wikipedia.org/wiki/Android_(operating_system)), etc.





### Kernel mode

#### [Linux kernel](https://en.wikipedia.org/wiki/Linux_kernel)

[stat](https://en.wikipedia.org/wiki/Stat_(system_call)) , [splice](https://en.wikipedia.org/wiki/Splice_(system_call)) ,[dup](https://en.wikipedia.org/wiki/Dup_(system_call)) , `read`, `open`, `ioctl`, `write`, `mmap`, `close`, `exit`, etc. (about 380 system calls)
The Linux kernel [System Call Interface](https://en.wikipedia.org/wiki/System_call) (SCI, aims to be [POSIX](https://en.wikipedia.org/wiki/POSIX)/[SUS](https://en.wikipedia.org/wiki/Single_UNIX_Specification)-compatible)



##### [Process scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing)) subsystem



##### IPC subsystem



##### [Memory management](https://en.wikipedia.org/wiki/Memory_management) subsystem



##### Virtual files subsystem



##### Network subsystem



##### Other components:

 [ALSA](https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture), [DRI](https://en.wikipedia.org/wiki/Direct_Rendering_Infrastructure), [evdev](https://en.wikipedia.org/wiki/Evdev), [LVM](https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux)), [device mapper](https://en.wikipedia.org/wiki/Device_mapper), [Linux Network Scheduler](https://en.wikipedia.org/wiki/Linux_Network_Scheduler), [Netfilter](https://en.wikipedia.org/wiki/Netfilter) [Linux Security Modules](https://en.wikipedia.org/wiki/Linux_Security_Modules): *SELinux*, [*TOMOYO*](https://en.wikipedia.org/wiki/TOMOYO_Linux), [*AppArmor*](https://en.wikipedia.org/wiki/AppArmor), [*Smack*](https://en.wikipedia.org/wiki/Smack_(Linux_security_module))



### **Hardware (**[CPU](https://en.wikipedia.org/wiki/Central_processing_unit)**,** [main memory](https://en.wikipedia.org/wiki/Random-access_memory)**,** [data storage devices](https://en.wikipedia.org/wiki/Computer_data_storage), etc.)



## Implementation

The most common way of implementing a **user mode** separate from [kernel mode](https://en.wikipedia.org/wiki/Supervisor_mode) involves operating system [protection rings](https://en.wikipedia.org/wiki/Protection_ring).

Another approach taken in experimental operating systems is to have a single [address space](https://en.wikipedia.org/wiki/Address_space) for all software, and rely on the programming language's [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine) to make sure that arbitrary memory cannot be accessed – applications simply cannot acquire any [references](https://en.wikipedia.org/wiki/Reference_(computer_science)) to the objects that they are not allowed to access.[[2\]](https://en.wikipedia.org/wiki/User_space#cite_note-2)[[3\]](https://en.wikipedia.org/wiki/User_space#cite_note-3) This approach has been implemented in [JXOS](https://en.wikipedia.org/wiki/JX_(operating_system)), Unununium as well as Microsoft's [Singularity](https://en.wikipedia.org/wiki/Singularity_(operating_system)) research project.

## See also

- [BIOS](https://en.wikipedia.org/wiki/BIOS)
- [CPU modes](https://en.wikipedia.org/wiki/CPU_modes)
- [Memory protection](https://en.wikipedia.org/wiki/Memory_protection)