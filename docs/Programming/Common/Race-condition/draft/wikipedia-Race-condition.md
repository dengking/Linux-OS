# [Race condition](https://en.wikipedia.org/wiki/Race_condition)

A **race condition** or **race hazard** is the behavior of an [electronics](https://en.wikipedia.org/wiki/Electronics), [software](https://en.wikipedia.org/wiki/Software), or other [system](https://en.wikipedia.org/wiki/System) where the system's substantive(实质的) behavior is dependent on the sequence or timing of other uncontrollable events. It becomes a [bug](https://en.wikipedia.org/wiki/Software_bug) when one or more of the possible behaviors is undesirable.

The term **race condition** was already in use by 1954, for example in [David A. Huffman](https://en.wikipedia.org/wiki/David_A._Huffman)'s doctoral thesis(博士论文) "The synthesis of sequential switching circuits". [[1\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-1)

**Race conditions** can occur especially in [logic circuits](https://en.wikipedia.org/wiki/Logic_gate), [multithreaded](https://en.wikipedia.org/wiki/Thread_(computing)) or [distributed](https://en.wikipedia.org/wiki/Distributed_computing) software programs.



## Software

**Race conditions** arise in software when an application depends on the sequence or timing of [processes](https://en.wikipedia.org/wiki/Process_(computing)) or [threads](https://en.wikipedia.org/wiki/Thread_(computing)) for it to operate properly. As with electronics, there are **critical race conditions** that result in invalid execution and [bugs](https://en.wikipedia.org/wiki/Software_bug). **Critical race conditions** often happen when the processes or threads depend on some **shared state**. Operations upon **shared states** are [critical sections](https://en.wikipedia.org/wiki/Critical_section) that must be [mutually exclusive](https://en.wikipedia.org/wiki/Mutual_exclusion). Failure to obey this rule opens up the possibility of corrupting the shared state.

The [memory model](https://en.wikipedia.org/wiki/Memory_model_(programming)) defined in the [C11](https://en.wikipedia.org/wiki/C11_(C_standard_revision)) and [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) standards uses the term "**data race**" for a **race condition** caused by potentially concurrent operations on a **shared memory location**, of which at least one is a write. A C or `C++` program containing a **data race** has [undefined behavior](https://en.wikipedia.org/wiki/Undefined_behavior).[[3\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-3)[[4\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-4)

**Race conditions** have a reputation of being difficult to reproduce and debug, since the end result is [nondeterministic](https://en.wikipedia.org/wiki/Nondeterministic_algorithm) and depends on the relative timing between interfering threads. Problems occurring in production systems can therefore disappear when running in debug mode, when additional logging is added, or when attaching a debugger, often referred to as a "[Heisenbug](https://en.wikipedia.org/wiki/Heisenbug)". It is therefore better to avoid **race conditions** by careful software design rather than attempting to fix them afterwards.

### Example

As a simple example, let us assume that two threads want to increment the value of a global integer variable by one. Ideally, the following sequence of operations would take place:

|    Thread 1    |    Thread 2    |      | Integer value |
| :------------: | :------------: | :--: | :-----------: |
|                |                |      |       0       |
|   read value   |                |  ←   |       0       |
| increase value |                |      |       0       |
|   write back   |                |  →   |       1       |
|                |   read value   |  ←   |       1       |
|                | increase value |      |       1       |
|                |   write back   |  →   |       2       |



In the case shown above, the final value is 2, as expected. However, if the two threads run simultaneously without locking or synchronization, the outcome of the operation could be wrong. The alternative sequence of operations below demonstrates this scenario:

|    Thread 1    |    Thread 2    |      | Integer value |
| :------------: | :------------: | :--: | :-----------: |
|                |                |      |       0       |
|   read value   |                |  ←   |       0       |
|                |   read value   |  ←   |       0       |
| increase value |                |      |       0       |
|                | increase value |      |       0       |
|   write back   |                |  →   |       1       |
|                |   write back   |  →   |       1       |



In this case, the final value is 1 instead of the expected result of 2. This occurs because here the increment operations are not [mutually exclusive](https://en.wikipedia.org/wiki/Mutually_exclusive). Mutually exclusive operations are those that cannot be interrupted while accessing some resource such as a memory location.

​	

### Computer security

Many software race conditions have associated [computer security](https://en.wikipedia.org/wiki/Computer_security) implications. A race condition allows an attacker with access to a shared resource to cause other actors（参与者） that utilize that resource to malfunction, resulting in effects including [denial of service](https://en.wikipedia.org/wiki/Denial-of-service_attack)[[5\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-CVE-2015-8461-5) and [privilege escalation](https://en.wikipedia.org/wiki/Privilege_escalation).[[6\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-CVE-2017-6512-6)[[7\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-lighttpd-issue-2724-7)

***TRANSLATION*** : 许多软件竞争条件都与计算机安全性有关。 竞争条件允许攻击者访问共享资源，导致其他使用该资源的参与者出现故障，从而导致包括拒绝服务[5]和权限提升等影响。

A specific kind of race condition involves checking for a predicate (e.g. for [authentication](https://en.wikipedia.org/wiki/Authentication)), then acting on the predicate, while the state can change between the *time of check* and the *time of use*. When this kind of [bug](https://en.wikipedia.org/wiki/Computer_bug) exists in security-sensitive code, a [security vulnerability](https://en.wikipedia.org/wiki/Security_vulnerability) called a [time-of-check-to-time-of-use](https://en.wikipedia.org/wiki/Time-of-check-to-time-of-use) (*TOCTTOU*) bug is created.

Race conditions are also intentionally used to create [hardware random number generators](https://en.wikipedia.org/wiki/Hardware_random_number_generator) and [physically unclonable functions](https://en.wikipedia.org/wiki/Physically_unclonable_function).[[8\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-8)[*citation needed*] PUFs can be created by designing circuit topologies with identical paths to a node and relying on manufacturing variations to randomly determine which paths will complete first. By measuring each manufactured circuit's specific set of race condition outcomes, a profile can be collected for each circuit and kept secret in order to later verify a circuit's identity.

***SUMMARY*** : 上面这段话涉及到circuit的知识，非software领域知识；

### File systems



Two or more programs may collide in their attempts to modify or access a file system, which can result in data corruption or privilege escalation.[[6\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-CVE-2017-6512-6) [File locking](https://en.wikipedia.org/wiki/File_locking) provides a commonly used solution. A more cumbersome remedy(补救措施) involves organizing the system in such a way that one unique process (running a [daemon](https://en.wikipedia.org/wiki/Daemon_(computing)) or the like) has exclusive access to the file, and all other processes that need to access the data in that file do so only via interprocess communication with that one process. This requires synchronization at the process level.

A different form of **race condition** exists in file systems where unrelated programs may affect each other by suddenly using up(耗尽) available resources such as disk space, memory space, or processor cycles. Software not carefully designed to anticipate and handle this race situation may then become unpredictable. Such a risk may be overlooked(忽视) for a long time in a system that seems very reliable. But eventually enough data may accumulate or enough other software may be added to critically destabilize many parts of a system. An example of this occurred with the near loss of the [Mars Rover "Spirit"](https://en.wikipedia.org/wiki/Spirit_(rover)#Sol_17_(January_21,_2004)_flash_memory_management_anomaly) not long after landing. A solution is for software to request and reserve all the resources it will need before beginning a task; if this request fails then the task is postponed（推迟）, avoiding the many points where failure could have occurred. Alternatively, each of those points can be equipped with **error handling**, or the success of the entire task can be verified afterwards, before continuing. A more common approach is to simply verify that enough system resources are available before starting a task; however, this may not be adequate because in complex systems the actions of other running programs can be unpredictable.

***SUMMARY*** : 文件系统中存在不同形式的竞争条件，其中不相关的程序可能通过突然耗尽可用资源（例如磁盘空间，内存空间或处理器周期）而相互影响。未经过精心设计以预测和处理这种竞争情况的软件可能会变得无法预测。在一个看起来非常可靠的系统中，这种风险可能会长期被忽视。但最终可能会累积足够的数据，或者可能会添加足够的其他软件来严重破坏系统的许多部分的稳定性。这种情况的一个例子发生在着陆后不久，火星探测器“精神”几乎失去了。解决方案是软件在开始任务之前请求并保留所需的所有资源;如果此请求失败，则该任务将被推迟，从而避免可能发生故障的许多点。或者，这些点中的每一个都可以配备错误处理，或者在继续之前可以在之后验证整个任务的成功。更常见的方法是在开始任务之前简单地验证有足够的系统资源可用;但是，这可能不够，因为在复杂系统中，其他正在运行的程序的操作可能是不可预测的。

### Networking

In networking, consider a distributed chat network like [IRC](https://en.wikipedia.org/wiki/IRC), where a user who starts a channel automatically acquires **channel-operator privileges**. If two users on different servers, on different ends of the same network, try to start the same-named channel at the same time, each user's respective server will grant **channel-operator privileges** to each user, since neither server will yet have received the other server's signal that it has allocated that channel. (This problem has been largely [solved](https://en.wikipedia.org/wiki/Internet_Relay_Chat#Abuse_prevention) by various IRC server implementations.)

In this case of a race condition, the concept of the "[shared resource](https://en.wikipedia.org/wiki/Shared_resource)" covers the state of the network (what channels exist, as well as what users started them and therefore have what privileges), which each server can freely change as long as it signals the other servers on the network about the changes so that they can update their conception of the state of the network. However, the [latency](https://en.wikipedia.org/wiki/Latency_(engineering)) across the network makes possible the kind of **race condition** described. In this case, heading off(阻止) **race conditions** by imposing a form of control over access to the shared resource—say, appointing one server to control who holds what privileges—would mean turning the **distributed network** into a **centralized one** (at least for that one part of the network operation).

***SUMMARY*** : 这段关于distributed network和centralized one的阐述是非常好的；

**Race conditions** can also exist when a computer program is written with [non-blocking sockets](https://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_vs._non-blocking_mode), in which case the performance of the program can be dependent on the speed of the network link.

***TRANSLATION*** : 在网络中，考虑像IRC这样的分布式聊天网络，其中启动频道的用户自动获取频道操作员权限。如果位于同一网络不同端的不同服务器上的两个用户尝试同时启动同名通道，则每个用户的相应服务器将为每个用户授予通道操作员权限，因为两个服务器都没有收到其他服务器已分配该通道的信号。 （这个问题已经在很大程度上通过各种IRC服务器实现来解决。）

在这种竞争条件的情况下，“共享资源”的概念涵盖了网络的状态（存在哪些信道，以及用户启动它们因此具有哪些特权），每个服务器可以自由更改，只要它向网络上的其他服务器发出关于变化的信号，以便他们可以更新他们对网络状态的概念。但是，网络上的延迟使得所描述的竞争条件成为可能。在这种情况下，通过对共享资源的访问实施一种控制形式来控制竞争条件 - 例如，指定一个服务器来控制谁拥有什么特权 - 意味着将分布式网络转变为集中式网络（至少对于那个部分）网络运营）。

当计算机程序使用非阻塞套接字编写时，竞争条件也可能存在，在这种情况下，程序的性能可能取决于网络链接的速度。

### Life-critical systems 生死攸关的系统

Software flaws in [life-critical systems](https://en.wikipedia.org/wiki/Life-critical_system) can be disastrous. Race conditions were among the flaws in the [Therac-25](https://en.wikipedia.org/wiki/Therac-25) [radiation therapy](https://en.wikipedia.org/wiki/Radiation_therapy) machine, which led to the death of at least three patients and injuries to several more.[[9\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-9)

***TRANSLATION*** : 生命攸关系统中的软件缺陷可能是灾难性的。 

Another example is the Energy Management System provided by [GE Energy](https://en.wikipedia.org/wiki/GE_Energy) and used by [Ohio](https://en.wikipedia.org/wiki/Ohio)-based [FirstEnergy Corp](https://en.wikipedia.org/wiki/FirstEnergy_Corp) (among other power facilities). A **race condition** existed in the alarm subsystem; when three sagging power lines were tripped simultaneously, the condition prevented alerts from being raised to the monitoring technicians, delaying their awareness of the problem. This software flaw eventually led to the [North American Blackout of 2003](https://en.wikipedia.org/wiki/2003_North_America_blackout).[[10\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-10) GE Energy later developed a software patch to correct the previously undiscovered error.



## Tools

Many software tools exist to help detect race conditions in software. They can be largely categorized into two groups: [static analysis](https://en.wikipedia.org/wiki/Static_program_analysis) tools and [dynamic analysis](https://en.wikipedia.org/wiki/Dynamic_program_analysis) tools.

Thread Safety Analysis is a static analysis tool for annotation-based intra-procedural static analysis, originally implemented as a branch of gcc, and now reimplemented in [Clang](https://en.wikipedia.org/wiki/Clang), supporting PThreads.[[13\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-13)[*non-primary source needed*]

Dynamic analysis tools include:

- [Intel Inspector](https://en.wikipedia.org/wiki/Intel_Inspector), a memory and thread checking and debugging tool to increase the reliability, security, and accuracy of C/C++ and Fortran applications; [Intel Advisor](https://en.wikipedia.org/wiki/Intel_Advisor), a sampling based, SIMD vectorization optimization and shared memory threading assistance tool for C, C++, C#, and Fortran software developers and architects;
- ThreadSanitizer, which uses binary ([Valgrind](https://en.wikipedia.org/wiki/Valgrind)-based) or source, [LLVM](https://en.wikipedia.org/wiki/LLVM)-based instrumentation, and supports PThreads);[[14\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-14)[*non-primary source needed*] and Helgrind, a [Valgrind](https://en.wikipedia.org/wiki/Valgrind) tool for detecting synchronisation errors in C, C++ and Fortran programs that use the POSIX pthreads threading primitives.[[15\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-15)[*non-primary source needed*]
- Data Race Detector[[16\]](https://en.wikipedia.org/wiki/Race_condition#cite_note-16) is designed to find data races in the Go Programming language.

