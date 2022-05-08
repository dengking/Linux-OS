# **4.4 Set-User-ID and Set-Group-ID**

> NOTE:
>
> "Set-User-ID" 设置用户ID
>
> "Set-Group-ID" 设置组ID





## 补充内容

cis.syr [Set-UID Privileged Programs](http://www.cis.syr.edu/~wedu/Teaching/IntrCompSec/LectureNotes_New/Set_UID.pdf)

[give administrator privileges to a one-file executable](https://pyinstaller.readthedocs.io/en/stable/operating-mode.html#how-the-one-file-program-works)

其中的一段话对于理解set user id的作用是非常好的：

> Do *not* give administrator privileges to a one-file executable (`setuid` root in Unix/Linux, or the “Run this program as an administrator” property in Windows 7). There is an unlikely but not impossible way in which a malicious attacker could corrupt one of the shared libraries in the temp folder while the bootloader is preparing it. Distribute a privileged program in one-folder mode instead.

`setuid` root in Unix/Linux是类似“Run this program as an administrator” property in Windows 7。