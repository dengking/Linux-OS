# 2 Types of Linux File Locking (Advisory, Mandatory Lock Examples)

File locking is a mechanism which allows only one process to access a file at any specific time. By using file locking mechanism, many processes can read/write a single file in a safer way.

In this article we’ll explore the different types of Linux file locking and understand their differences using an example program.

We will take the following example to understand why file locking is required.

1. Process “A” opens and reads a file which contains account related information.
2. Process “B” also opens the file and reads the information in it.
3. Now Process “A” changes the account balance of a record in its copy, and writes it back to the file.
4. Process “B” which has no way of knowing that the file is changed since its last read, has the stale original value. It then changes the account balance of the same record, and writes back into the file.
5. Now the file will have only the changes done by process “B”.

To avoid such issues locking is used to ensure “serialization”.

The following are the two types of Linux file locking:

1. Advisory locking
2. Mandatory locking

### 1. Advisory Locking

Advisory locking requires **cooperation** from the participating processes. Suppose process “A” acquires an WRITE lock, and it started writing into the file, and process “B”, without trying to acquire a lock, it can open the file and write into it. Here process “B” is the **non-cooperating** process. If process “B”, tries to acquire a lock, then it means this process is co-operating to ensure the “serialization”.

Advisory locking will work, only if the participating process are cooperative. Advisory locking sometimes also called as “unenforced” locking.

### 2. Mandatory Locking

Mandatory locking doesn’t require cooperation from the participating processes. Mandatory locking causes the kernel to check every open, read, and write to verify that the calling process isn’t violating a lock on the given file. More information about mandatory locking can be found at [kernal.org](http://kernel.org/doc/Documentation/filesystems/mandatory-locking.txt)

To enable mandatory locking in Linux, you need to enable it on a file system level, and also on the individual files. The steps to be followed are:

1. Mount the file system with “-o mand” option
2. For the lock_file, turn on the set-group-ID bit and turn off the group-execute bit, to enable mandatory locking on that particular file. (This way has been chosen because when you turn off the group-execute bit, set-group-ID has no real meaning to it )

### Linux File Locking Examples

To understand how this works, crate the following `file_lock.c` program:

```C
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    int fd = open(argv[1], O_WRONLY);
    if(fd == -1) {
      printf("Unable to open the file\n");
      exit(1);
    }
    static struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLKW, &lock);
    printf("Return value of fcntl:%d\n",ret);
    if(ret==0) {
      while (1) {
        scanf("%c", NULL);
      }
    }
  }
}
```

Compile the program using gcc.

```
# cc -o file_lock file_lock.c
```

Remount the root filesystem with “mand” option using the mount command as shown below. This will enable mandatory locking at the file system level.

Note: You need to be root to execute the below command.

```
# mount -oremount,mand /
```

Create 2 files named “advisory.txt” and “mandatory.txt” in the directory where the executable (file_lock) is located. Enable the Set-Group-ID and disable the Group-Execute-Bit for “mandatory.txt” as follows

```
# touch advisory.txt
# touch mandatory.txt
# chmod g+s,g-x mandatory.txt
```

**Test Advisory Locking:** Now execute the sample program with ‘advisory.txt’ as the argument.

```
# ./file_lock advisory.txt
```

The program will wait to get input from the user. From another terminal, or console, try the following

```
# ls >>advisory.txt
```

In the above example, ls command will write its output to advisory.txt file. Even though we acquire a write lock, still some other process ( Non Cooperating ) can write into the file. This is termed as “Advisory” locking.

**Test Mandatory Locking:** Once again execute the sample program with ‘mandatory.txt’ as the argument.

```
# ./file_lock mandatory.txt
```

From another terminal or console, try the following:

```
# ls >>mandatory.txt
```

In the above example, ls command will wait for the lock to be removed before writing its output to the mandatory.txt file. It is still a non-cooperative process, but locking is achieved using mandatory locking.

