# linking
**Executable files** are created from **individual object files** and **libraries** through the **linking process**. The linker resolves the **references** (including subroutines and data references) among
the different object files, adjusts the **absolute references** in the object files, and **relocates instructions**. The linking and loading processes, which are described in Chapter 2, require
information defined in the object files and store this information in specific sections such as .dynamic

上面这段话中的reference如何理解？？

Each operating system supports a set of **linking models** which fall into two categories:
1. Static 
A set of object files, system libraries and library archives are statically bound, references are resolved, and an executable file is created that is completely self contained.
2. Dynamic
A set of object files, libraries, system shared resources and other shared libraries are linked together to create the executable. When this executable is loaded, other shared resources and dynamic libraries must be made available in the system for the program to run successfully.

The general method used to resolve references at execution time for a dynamically linked executable file is described in the linkage model used by the operating system, and the actual implementation of this linkage model will contain processor-specific components.
