# 断线重连

https://stackoverflow.com/questions/37029341/how-to-reconnect-socket-using-threads

https://stackoverflow.com/questions/57323865/how-to-reconnect-to-tcp-server-after-network-goes-down-and-comes-back-up-again

## redis reconnect

https://stackoverflow.com/questions/10879426/how-to-reconnect-redis-connection

https://github.com/NodeRedis/node-redis/issues/1007


https://developer.ibm.com/depmodels/cloud/articles/error-detection-and-handling-with-redis/


一种解决方案是使用一个thread，每隔一段时间就取检查，另外一种实现方式是当出现错误的时候，才去重连。