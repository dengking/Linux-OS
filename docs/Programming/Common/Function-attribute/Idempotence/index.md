# Idempotence

## 参考文章:

1、stackoverflow [What is an idempotent operation?](https://stackoverflow.com/questions/1077412/what-is-an-idempotent-operation)

解释了幂等的含义，但是并没有讨论如何实现幂等、需要幂等的场景

2、csdn [这三年被分布式坑惨了，曝光十大坑](https://blog.csdn.net/jackson0714/article/details/108775573?spm=1001.2014.3001.5501) 

非常好的文章，详细说明了如何实现幂等、需要幂等的场景



## stackoverflow [What is an idempotent operation?](https://stackoverflow.com/questions/1077412/what-is-an-idempotent-operation)



### [A](https://stackoverflow.com/a/1077420)

> NOTE: 最最精简的回答

No matter how many times you call the operation, the result will be the same.

### [A](https://stackoverflow.com/a/1077489)

> NOTE: 从RESTful的角度来分析，这一段关于restful的介绍非常好
>
> 1、阐述了RESTful的内涵，非常精简

An idempotent operation can be repeated an arbitrary number of times and the result will be the same as if it had been done only once. In arithmetic, adding zero to a number is idempotent.

Idempotence is talked about a lot in the context of **"RESTful" web services**. REST seeks to maximally leverage HTTP to give programs access to web content, and is usually set in contrast to **SOAP-based web services**, which just tunnel(打开通道) remote procedure call style services inside HTTP requests and responses.

REST organizes a web application into "resources" (like a Twitter user, or a Flickr image) and then uses the HTTP verbs of POST, PUT, GET, and DELETE to create, update, read, and delete those resources.

Idempotence plays an important role in REST. If you GET a representation of a REST resource (eg, GET a jpeg image from Flickr), and the operation fails, you can just repeat the GET again and again until the operation succeeds. To the web service, it doesn't matter how many times the image is gotten. Likewise, if you use a RESTful web service to update your Twitter account information, you can PUT the new information as many times as it takes in order to get confirmation from the web service. PUT-ing it a thousand times is the same as PUT-ing it once. Similarly DELETE-ing a REST resource a thousand times is the same as deleting it once. Idempotence thus makes it a lot easier to construct a web service that's resilient(可迅速恢复的) to communication errors.

Further reading: [RESTful Web Services](https://rads.stackoverflow.com/amzn/click/com/0596529260), by Richardson and Ruby (idempotence is discussed on page 103-104), and Roy Fielding's [PhD dissertation on REST](http://www.ics.uci.edu/~fielding/pubs/dissertation/top.htm). Fielding was one of the authors of HTTP 1.1, RFC-2616, which talks about idempotence in [section 9.1.2](http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html).



### [A](https://stackoverflow.com/a/1077421)

In computing, an idempotent operation is one that has no additional effect if it is called more than once with the same input parameters. For example, removing an item from a set can be considered an idempotent operation on the set.

In mathematics, an idempotent operation is one where *f(f(x)) = f(x)*. For example, the `abs()` function is idempotent because `abs(abs(x)) = abs(x)` for all `x`.

These slightly different definitions can be reconciled by considering that *x* in the mathematical definition represents the state of an object, and *f* is an operation that may mutate that object. For example, consider the [Python `set`](https://docs.python.org/2/library/stdtypes.html#set) and its `discard` method. The `discard` method removes an element from a set, and does nothing if the element does not exist. So:

> NOTE: 
>
> set操作是天然幂等的

```python
my_set.discard(x)
```

has exactly the same effect as doing the same operation twice:

```python
my_set.discard(x)
my_set.discard(x)
```

Idempotent operations are often used in the design of network protocols, where a request to perform an operation is guaranteed to happen at least once, but might also happen more than once. If the operation is idempotent, then there is no harm in performing the operation two or more times.

See the Wikipedia article on [idempotence](http://en.wikipedia.org/wiki/Idempotence) for more information.



## wikipedia [Idempotence](https://en.wikipedia.org/wiki/Idempotence)

## 如何实现幂等

一、在 csdn [这三年被分布式坑惨了，曝光十大坑](https://blog.csdn.net/jackson0714/article/details/108775573?spm=1001.2014.3001.5501)  中进行了比较好的总结。

二、核心思想: "通过标志来来自动过滤掉重复的消息"

## 需要幂等的场景

### Message queue重复消息

这在 csdn [这三年被分布式坑惨了，曝光十大坑](https://blog.csdn.net/jackson0714/article/details/108775573?spm=1001.2014.3001.5501) 中进行了详细讨论，下面补充一些例子: 

比如:

1、[celery tasks](http://docs.celeryproject.org/en/latest/userguide/tasks.html)

### Callback、hook

在一些场景中，callback、hook需要实现幂等，下面是一些例子: 

1、[hiredis `redisAsyncContext`](https://github.com/redis/hiredis/blob/master/async.h)

hiredis的`async.h`中的`struct redisAsyncContext`就有如下定义：
```C
/* Context for an async connection to Redis */
typedef struct redisAsyncContext {
    /* Hold the regular context, so it can be realloc'ed. */
    redisContext c;

    /* Setup error flags so they can be used directly. */
    int err;
    char *errstr;

    /* Not used by hiredis */
    void *data;

    /* Event library data and hooks */
    struct {
        void *data;

        /* Hooks that are called when the library expects to start
         * reading/writing. These functions should be 	idempotent. */
        void (*addRead)(void *privdata);
        void (*delRead)(void *privdata);
        void (*addWrite)(void *privdata);
        void (*delWrite)(void *privdata);
        void (*cleanup)(void *privdata);
    } ev;
```

## TODO



Jaskey Lam [匠心零度](javascript:void(0);) [消息幂等（去重）通用解决方案，真顶！](https://mp.weixin.qq.com/s/qKCpo9x8PjkiYVE12YWnqQ)