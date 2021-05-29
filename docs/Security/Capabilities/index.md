# Capabilities 



## linuxjournal [Taking Advantage of Linux Capabilities](https://www.linuxjournal.com/article/5737)

A common topic of discussion nowadays is security, and for good reason. Security is becoming more important as the world becomes further networked. Like all good systems, Linux is evolving in order to address increasingly important security concerns.

> NOTE: 
>
> Linux capability就是为了解决security的问题的

### UNIX-style user privileges 

One aspect of security is **user privileges**. UNIX-style user privileges come in two varieties, user and root. Regular users are absolutely powerless; they cannot modify any processes or files but their own. Access to hardware and most network specifications also are denied. Root, on the other hand, can do anything from modifying all processes and files to having unrestricted network and hardware access. In some cases root can even physically damage hardware.

> NOTE: 
>
> "UNIX-style user privileges"是非常粗的，无法进行精细的调控，并且还存在着隐患，下面以`ping` 为例进行了说明

Sometimes a middle ground is desired. A utility needs special privileges to perform its function, but unquestionable god-like root access is overkill. The ping utility is `setuid` root simply so it can send and receive ICMP messages. The danger lies in the fact that ping can be exploited before it has dropped its root privileges, giving the attacker root access to your server.

### POSIX capabilities

> NOTE: 
>
> 相比于 UNIX-style user privileges ，POSIX capabilities是非常精细的

Fortunately, such a middle ground now exists, and it's called POSIX capabilities. Capabilities divide system access into logical groups that may be individually granted to, or removed from, different processes. Capabilities allow system administrators to fine-tune(精细的调控) what a process is allowed to do, which may help them significantly reduce security risks to their system. The best part is that your system already supports it. If you're lucky, no patching should be necessary.

A list of all the capabilities that your system is, well, capable of, is available in `/usr/include/linux/capability.h`, starting with `CAP_CHOWN`. They're pretty self-explanatory and well commented. Capability checks are sprinkled throughout the kernel source, and grepping for them can make for some fun midnight reading.

Each capability is nothing more than a bit in a bitmap. With 32 bits in a capability set, and 28 sets currently defined, there are currently discussions as to how to expand this number. Some purists(纯粹主义者) believe that additional capabilities would be too confusing, while others argue that there should be many more, even a capability for each system call. Time and Linus will ultimately decide how this exciting feature develops.

### The Proc Interface

As of kernel 2.4.17, the file /proc/sys/kernel/cap-bound contains a single 32-bit integer that defines the current **global capability set**. The **global capability set** determines what every process on the system is allowed to do. If a capability is stripped from the system, it is impossible for any process, even root processes, to regain them.

For example, many crackers' rootkits (a set of tools that cover up their activities and install backdoors into the system) will load kernel modules that hide illicit(违法的) processes and files from the system administrator. To counter this, the administrator could simply remove the `CAP_SYS_MODULE` capability from the system as the last step in the system startup process. This step would prevent any kernel modules from being loaded or unloaded. Once a capability has been removed, it cannot be re-added. The system must be restarted (which means you might have to use the power button if you've removed the `CAP_SYS_BOOT` capability) to regain the full-capability set.

Okay, I lied. There are two ways to add back a capability:

1、`init` can re-add capabilities, in theory; there's no actual implementation to my knowledge. This is to facilitate capability-aware systems in the event that init needs to change runlevels.
2、If a process is capable of `CAP_SYS_RAWIO`, it can modify kernel memory through `/dev/mem`. Among other things, it can modify kernel memory to grant itself whatever access it desires. Remove `CAP_SYS_RAWIO`, but be careful: by removing `CAP_SYS_RAWIO`, programs such as X most likely will fail to run.

## TODO

linux-audit [Linux capabilities 101](https://linux-audit.com/linux-capabilities-101/)

container-solutions [Linux Capabilities: Why They Exist and How They Work](https://blog.container-solutions.com/linux-capabilities-why-they-exist-and-how-they-work)

k3a [Linux Capabilities in a nutshell](https://k3a.me/linux-capabilities-in-a-nutshell/)

