# 1.2. Hardware Dependency

Linux tries to maintain a neat distinction between **hardware-dependent** and **hardware-independent** source code. To that end, both the `arch` and the `include` directories include 23 subdirectories that correspond to the different types of hardware platforms supported. The standard names of the platforms are:

*arm, arm26*

ARM processor-based computers such as PDAs and embedded devices

*i386*

IBM-compatible personal computers based on 80x86 microprocessors

*ia64*

Workstations based on the Intel 64-bit Itanium microprocessor

*mips*

Workstations based on MIPS microprocessors, such as those marketed by Silicon Graphics

*x86_64*

Workstations based on the AMD's 64-bit microprocessorssuch Athlon and Opteron and Intel's  ia32e/EM64T 64-bit microprocessors