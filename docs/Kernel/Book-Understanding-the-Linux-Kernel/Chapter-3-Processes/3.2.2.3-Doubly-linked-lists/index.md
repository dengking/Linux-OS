# 3.2.2.3. Doubly linked lists

Before moving on and describing how the kernel keeps track of the various processes in the system,
we would like to emphasize the role of special data structures that implement doubly linked lists.



For each list, a set of primitive operations must be implemented: initializing the list, inserting and
deleting an element, scanning the list, and so on. It would be both a waste of programmers' efforts
and a waste of memory to replicate the primitive operations for each different list.



Therefore, the **Linux kernel** defines the  `list_head` data structure, whose only fields  `next` and  `prev`
represent the forward and back pointers of a generic doubly linked list element, respectively. It is
important to note, however, that the pointers in a  `list_head` field store the addresses of other
`list_head` fields rather than the addresses of the whole data structures in which the  `list_head`
structure is included; see Figure 3-3 (a).

> NOTE: [list_head](https://elixir.bootlin.com/linux/v2.6.11/source/include/linux/list.h#L28) 

A new list is created by using the  `LIST_HEAD(list_name)` macro. It declares a new variable named
`list_name` of type  `list_head` , which is a dummy first element that acts as a placeholder for the head
of the new list, and initializes the  `prev` and  `next` fields of the  `list_head` data structure so as to point
to the  `list_name` variable itself; see Figure 3-3 (b).

Several functions and macros implement the primitives, including those shown in Table Table 3-1.





The Linux kernel 2.6 sports another kind of doubly linked list, which mainly differs from a  `list_head`
list because it is not circular; it is mainly used for **hash tables**, where space is important, and finding
the the last element in constant time is not. The list head is stored in an  `hlist_head` data structure,
which is simply a pointer to the first element in the list ( NULL if the list is empty). Each element is represented by an  `hlist_node` data structure, which includes a pointer  `next` to the next element, and
a pointer  `pprev` to the  `next` field of the previous element. Because the list is not circular, the  `pprev`
field of the first element and the  `next` field of the last element are set to  `NULL` . The list can be
handled by means of several helper functions and macros similar to those listed in Table 3-1:
`hlist_add_head( )` ,  `hlist_del( )` ,  `hlist_empty( )` ,  `hlist_entry` ,  `hlist_for_each_entry` , and so on.