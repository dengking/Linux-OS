# TCP flow control

TCP流控。

## 参考文章

1、leetbook [TCP 流量控制与拥塞控制](https://leetcode-cn.com/leetbook/read/networks-interview-highlights/estnmd/)





## 流量控制

所谓**流量控制**就是让**发送方**的发送速率不要太快，让**接收方**来得及接收。如果接收方来不及接收发送方发送的数据，那么就会有分组丢失。在 TCP 中利用可变长的**滑动窗口机制**可以很方便的在 TCP 连接上实现对发送方的流量控制。主要的方式是接收方返回的 ACK 中会包含自己的接收窗口大小，以控制发送方此次发送的数据量大小（发送窗口大小）。
