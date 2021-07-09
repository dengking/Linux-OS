# Address Resolution Protocol

## leetbook [ARP 地址解析协议的原理和地址解析过程](https://leetcode-cn.com/leetbook/read/networks-interview-highlights/esjj3r/)

ARP（Address Resolution Protocol）是地址解析协议的缩写，该协议提供根据 **IP 地址**获取物理地址的功能，它工作在第二层，是一个**数据链路层协议**，其在本层和物理层进行联系，同时向上层提供服务。当通过以太网发送 IP 数据包时，需要先封装 32 位的 IP 地址和 48位 MAC 地址。在局域网中两台主机进行通信时需要依靠各自的物理地址进行标识，但由于发送方只知道目标 IP 地址，不知道其 MAC 地址，因此需要使用地址解析协议。 ARP 协议的解析过程如下：

① 首先，每个主机都会在自己的 ARP 缓冲区中建立一个 ARP 列表，以表示 **IP 地址**和 **MAC 地址**之间的对应关系；

② 当源主机要发送数据时，首先检查 ARP 列表中是否有 IP 地址对应的目的主机 MAC 地址，如果存在，则可以直接发送数据，否则就向同一子网的所有主机发送 **ARP 数据包**。该数据包包括的内容有源主机的 IP 地址和 MAC 地址，以及目的主机的 IP 地址。

③ 当本网络中的所有主机收到该 ARP 数据包时，首先检查数据包中的 目的 主机IP 地址是否是自己的 IP 地址，如果不是，则忽略该数据包，如果是，则首先从数据包中取出源主机的 IP 和 MAC 地址写入到 ARP 列表中，如果已经存在，则覆盖，然后将自己的 MAC 地址写入 ARP 响应包中，告诉源主机自己是它想要找的 MAC 地址。

④ 源主机收到 ARP 响应包后。将目的主机的 IP 和 MAC 地址写入 ARP 列表，并利用此信息发送数据。如果源主机一直没有收到 ARP 响应数据包，表示 ARP 查询失败。



## wanweibaike [Address Resolution Protocol](https://en.wanweibaike.com/wiki-Address%20Resolution%20Protocol)

