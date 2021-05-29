# `pthread_cond_timedwait`

## [`pthread_cond_timedwait`(3) - Linux man page](https://linux.die.net/man/3/pthread_cond_timedwait)

### Name

`pthread_cond_timedwait`, `pthread_cond_wait` - wait on a condition

### Synopsis

```C
#include <pthread.h>

int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex); 
```

