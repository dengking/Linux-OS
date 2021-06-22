# Inter process lock

一、各种实现方式都需要依赖于IPC

二、如何避免dead lock是一个非常重要的问题

三、参考的文章、实现方式

| 文章、章节                                                   |      |      |
| ------------------------------------------------------------ | ---- | ---- |
| csdn [进程互斥锁](https://blog.csdn.net/luansxx/article/details/7736618) |      |      |
| `Nginx-accept_mutex-implementation`                          |      |      |
| csdn [【Linux】进程间同步（进程间互斥锁、文件锁）](https://blog.csdn.net/qq_35396127/article/details/78942245) |      |      |



## csdn [进程互斥锁](https://blog.csdn.net/luansxx/article/details/7736618)

进程间共享数据的保护，需要进程互斥锁。与线程锁不同，进程锁并没有直接的C库支持，但是在Linux平台，要实现进程之间互斥锁，方法有很多，大家不妨回忆一下你所了解的。下面就是标准C库提供的一系列方案。

### 1、实现方案

不出意外的话，大家首先想到的应该是信号量（Semaphores）。对信号量的操作函数有两套，一套是Posix标准，另一套是System V标准。

**Posix信号量**

```C
sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
int sem_close(sem_t *sem);
int sem_destroy(sem_t *sem);
int sem_unlink(const char *name);

```

**System V信号量**

```C++
int semget(key_t key, int nsems, int semflg);
int semctl(int semid, int semnum, int cmd, ...);
int semop(int semid, struct sembuf *sops, unsigned nsops);
int semtimedop(int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout);

```

**线程锁共享**

线程锁就是pthread那一套C函数了：

```C++
int pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
int pthread_mutex_destroy (pthread_mutex_t *mutex);
int pthread_mutex_trylock (pthread_mutex_t *mutex);
int pthread_mutex_lock (pthread_mutex_t *mutex);
int pthread_mutex_timedlock (pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
int pthread_mutex_unlock (pthread_mutex_t *mutex);

```

但是这只能用在一个进程内的多个线程实现互斥，怎么应用到多进程场合呢，被多个进程共享呢？

很简单，首先需要设置互斥锁的进程间共享属性：

```C++
int pthread_mutexattr_setpshared(pthread_mutexattr_t *mattr, int pshared); 
pthread_mutexattr_t mattr; 
pthread_mutexattr_init(&mattr); 
pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);

```

其次，为了达到多进程共享的需要，互斥锁对象需要创建在**共享内存**中。

> NOTE: 
>
> 也就是说，需要使用share memory IPC

最后，需要注意的是，并不是所有Linux系统都支持这个特性，程序里需要检查是否定义了`_POSIX_SHARED_MEMORY_OBJECTS`宏，只有定义了，才能用这种方式实现进程间互斥锁。

### 2、平台兼容性

我们来看看这三套方案的平台移植性。

绝大部分嵌入式Linux系统，glibc或者uclibc，不支持_POSIX_SHARED_MEMORY_OBJECTS；

绝大部分嵌入式Linux系统，不支持Posix标准信号量；

部分平台，不支持System V标准信号量，比如Android。

### 3、匿名锁与命名锁

当两个（或者多个）进程没有特殊关系（比如父子进程共享）时，我们只能通过约定好的名字来访问同一个锁，这就是命名锁。然而，如果我们有其他途径定位一个锁，那么匿名锁是更好的选择。这三套方案是否都支持匿名锁与命名锁呢？

#### Posix信号量

通过sem_open创建命名锁，通过sem_init创建匿名锁，其实sem_init也支持进程内部锁。

#### System V信号量

semget中的key参数可以看成是名字，所以支持命名锁。该方案不支持匿名锁。

#### 线程锁共享

不支持命名锁，支持匿名锁。

### 4、缺陷

在匿名锁与命名锁的支持上，一些方案是有不足的，但这还是小问题，更严重的问题是异常状况下的死锁问题。

与多线程环境不一样的是，在多进程环境中，一个进程的异常退出不会影响其他进程，但是如果使用了进程互斥锁呢？假如一个进程获取了互斥锁，但是在访问互斥资源的代码中crash了，或者遇到信号退出了，那么其他等待同一个锁的进程（内部某个线程）就挂死了。在多线程环境中，程序异常整个进程退出，不需要考虑异常时锁的释放，多进程环境则是一个实实在在的问题。

System V信号量通过UNDO方式可以解决该问题。但是如果考虑到平台兼容性等问题，这三个方案仍不能满足需求，我会接着介绍一种更好的方案。


## csdn [【Linux】进程间同步（进程间互斥锁、文件锁）](https://blog.csdn.net/qq_35396127/article/details/78942245)



```C
/*
 互斥量 实现 多进程 之间的同步
 */

#include<unistd.h>
#include<sys/mman.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct mt
{
	int num;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
};

int main(void)
{

	int i;
	struct mt *mm;

	pid_t pid;

	/*
	 // 创建映射区文件
	 int fd = open("mt_test",O_CREAT|O_RDWR,0777);
	 if( fd == -1 )
	 {
	 perror("open file:");
	 exit(1);
	 }
	 ftruncate(fd,sizeof(*mm));
	 mm = mmap(NULL,sizeof(*mm),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	 close(fd);
	 unlink("mt_test");
	 */

	// 建立映射区
	mm = mmap(NULL, sizeof(*mm), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

//    printf("-------before memset------\n");
	memset(mm, 0x00, sizeof(*mm));
//   printf("-------after memset------\n");

	pthread_mutexattr_init(&mm->mutexattr);         // 初始化 mutex 属性
	pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);               // 修改属性为进程间共享

	pthread_mutex_init(&mm->mutex, &mm->mutexattr);      // 初始化一把 mutex 锁

	pid = fork();
	if (pid == 0)          // 子进程
	{
		for (i = 0; i < 10; i++)
		{
			pthread_mutex_lock(&mm->mutex);
			(mm->num)++;
			printf("-child--------------num++    %d\n", mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(1);
		}

	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			sleep(1);
			pthread_mutex_lock(&mm->mutex);
			mm->num += 2;
			printf("--------parent------num+=2   %d\n", mm->num);
			pthread_mutex_unlock(&mm->mutex);

		}
		wait(NULL);

	}
	pthread_mutexattr_destroy(&mm->mutexattr);  // 销毁 mutex 属性对象
	pthread_mutex_destroy(&mm->mutex);          // 销毁 mutex 锁

	return 0;
}
// gcc test.c -lpthread
```





## TODO

stackexchange [How do you make a cross-process locking in Linux (C/C++)?](https://unix.stackexchange.com/questions/20756/how-do-you-make-a-cross-process-locking-in-linux-c-c)
