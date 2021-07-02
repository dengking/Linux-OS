# Block signal

在下面文章中，对此进行了介绍:

1、"man [signal(7) ](http://man7.org/linux/man-pages/man7/signal.7.html) # Signal mask and pending signals"

2、csdn [Linux网络编程--select()和pselect()函数](https://blog.csdn.net/hnlyyk/article/details/48346227)

```C
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include <signal.h>
int sigint_event = 0;
void sigint_sig_handler(int s)
{ //设置信号处理函数
	sigint_event++;
	signal(SIGINT, sigint_sig_handler);
}
int main()
{
	int r;
	fd_set rd;
	FD_ZERO(&rd); //清空读描述符集合
	FD_SET(0, &rd); //将标准输入放入读描述符集合
	sigset_t sigmask, orignal_sigmask; //设置新掩码和保存原始掩码
	sigemptyset(&sigmask); //清空信号
	sigaddset(&sigmask, SIGINT); //将SIGINT信号加入sigmask中
	//设置信号SIG_BLOCK的掩码sigmask，并将原始的掩码保存在orignal_sigmask中
	sigprocmask(SIG_BLOCK, &sigmask, &orignal_sigmask);
	signal(SIGINT, sigint_sig_handler);    //挂接信号处理函数
	for (;;)
	{
		for (; sigint_event > 0; sigint_event--)
		{
			printf("sigint_event[%d]\n", sigint_event);
		}
		r = pselect(1, &rd, NULL, NULL, NULL, &orignal_sigmask);    //pselect函数IO复用
		if (r == -1)
		{
			perror("pselect");
		}
		else if (r)
		{
			printf("Data is avaialble now\n");
		}
		else
		{
			printf("NO Data within five seconds\n");
		}
		sleep(1);
	}
	return 0;
}

```

3、cnblogs [pselect 和 select](https://www.cnblogs.com/diegodu/p/3988103.html)

```C
sigset_t new, old, zero;

sigemptyset (&zero);
sigemptyset(&new);
sigaddset(&new, SIGINT);
sigprocmask(SIG_BLOCK, &new, old); //block SIGINT
if (intr_flag)
handle_intr();//handle the signal
if ((nready = pselet(..., &zero)) < 0)
{
	if (errno = EINTR)
	{
		if (intr_flag)
		handle_intr();
	}
	...
}
```



## see also

stackoverflow [How to block signals in C?](https://stackoverflow.com/questions/13481186/how-to-block-signals-in-c)
