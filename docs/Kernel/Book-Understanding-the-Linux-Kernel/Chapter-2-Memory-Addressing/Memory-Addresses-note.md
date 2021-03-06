A logical address consists of two parts: a segment identifier and an offset that specifies the relative
address within the segment. The segment identifier is a 16-bit field called the **Segment Selector** (see
Figure 2-2), while the offset is a 32-bit field. 



the processor provides **segmentation registers** whose only purpose is to hold **Segment Selectors**

***SUMMARY*** : 在Segment Selector中有Request Privilege Level字段，The  `cs` register has another important function: it includes a 2-bit field that specifies the Current Privilege Level (CPL) of the CPU. Segment Selector的Request Privilege Level字段与`cs` register 的Current Privilege Level (CPL) 字段相对应；参见Table 2-2. Segment Selector fields，其中有这样的一段描述：

> Requestor Privilege Level : specifies the Current Privilege Level of the CPU when the
> corresponding Segment Selector is loaded into the  cs register; it also may be used to
> selectively weaken the processor privilege level when accessing data segments (see Intel
> documentation for details).

