# Inode



## 维基百科[inode](https://en.wikipedia.org/wiki/Inode)

The **inode** (index node) is a [data structure](https://en.wikipedia.org/wiki/Data_structure) in a [Unix-style file system](https://en.wikipedia.org/wiki/Unix_filesystem) that describes a [file-system](https://en.wikipedia.org/wiki/File_system) object such as a [file](https://en.wikipedia.org/wiki/Computer_file) or a [directory](https://en.wikipedia.org/wiki/Directory_(computing)). Each inode stores the **attributes** and **disk block location**(s) of the object's data.[[1\]](https://en.wikipedia.org/wiki/Inode#cite_note-1) File-system object **attributes** may include [metadata](https://en.wikipedia.org/wiki/Metadata) (times of last change,[[2\]](https://en.wikipedia.org/wiki/Inode#cite_note-2) access, modification), as well as owner and [permission](https://en.wikipedia.org/wiki/File_system_permissions) data.[[3\]](https://en.wikipedia.org/wiki/Inode#cite_note-3)

> NOTE: 根据3.10 File Sharing中的描述：This information is read from disk when the file is opened, so that all the pertinent（相关的） information about the file is readily available. 

Directories are lists of names assigned to inodes. A directory contains an entry for itself, its parent, and each of its children.

### Details

A file system relies on **data structures** *about* the files, beside the file content. The former are called *metadata*—data that describes data. Each file is associated with an *inode*, which is identified by an **integer number**, often referred to as an *i-number* or *inode number*.

Inodes store information about files and directories (folders), such as **file ownership**, **access mode** (read, write, execute permissions), and **file type**. On many types of file system implementations, the maximum number of inodes is fixed at file system creation, limiting the maximum number of files the file system can hold. A typical allocation heuristic for inodes in a file system is one percent of total size.

The inode number indexes a table of inodes in a known location on the device. From the inode number, the kernel's file system driver can access the inode contents, including the location of the file - thus allowing access to the file.

A file's inode number can be found using the `ls -i` command. The `ls -i` command prints the i-node number in the first column of the report.

Some Unix-style file systems such as [ReiserFS](https://en.wikipedia.org/wiki/ReiserFS) omit an inode table, but must store equivalent data in order to provide equivalent capabilities. The data may be called **stat data**, in reference to the `stat` [system call](https://en.wikipedia.org/wiki/System_call) that provides the data to programs.

File names and directory implications:

- Inodes do not contain its hardlink names, only other file metadata.
- Unix directories are lists of association structures, each of which contains one **filename** and one **inode number**.
- The file system driver must search a directory looking for a particular filename and then convert the filename to the correct corresponding inode number.

The operating system kernel's in-memory representation of this data is called `struct inode` in [Linux](https://en.wikipedia.org/wiki/Linux). Systems derived from [BSD](https://en.wikipedia.org/wiki/BSD) use the term `vnode`, with the **v** of **vnode** referring to the kernel's [virtual file system](https://en.wikipedia.org/wiki/Virtual_file_system) layer.



## [INODE(7)](http://man7.org/linux/man-pages/man7/inode.7.html)

