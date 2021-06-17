# MTU(Maximum-Transmission-Unit)

## microsoft [The default MTU sizes for different network topologies](https://support.microsoft.com/en-us/topic/the-default-mtu-sizes-for-different-network-topologies-b25262c5-d90f-456d-7647-e09192eeeef4)

The maximum transfer unit (MTU) specifies the maximum transmission size of an interface. A different MTU value may be specified for each interface that TCP/IP uses. The MTU is usually determined by negotiating with the lower-level driver. However, this value may be overridden.

### More Information

Each media type has a maximum frame size. The **link layer** is responsible for discovering this MTU and reporting the MTU to the protocols above the **link layer**. The protocol stack may query **Network Driver Interface Specification (NDIS) drivers** for the local MTU. Upper-layer protocols such as TCP use an interface's MTU to optimize packet sizes for each medium.

If a network adapter driver, such as an asynchronous transfer mode (ATM) driver, uses local area network (LAN) emulation mode, the driver may report that its MTU is larger than expected for that media type. For example, the network adapter may emulate Ethernet but report an MTU of 9180 bytes. Windows accepts and uses the MTU size that the adapter reports even when the MTU size exceeds the usual MTU size for a particular media type.


The following table summarizes the default MTU sizes for different network media.



Network MTU (bytes)
\-------------------------------
16 Mbps Token Ring 17914
4 Mbps Token Ring 4464
FDDI 4352
**Ethernet 1500**
IEEE 802.3/802.2 1492
PPPoE (WAN Miniport) 1480
X.25 576

