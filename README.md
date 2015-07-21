# Information-Security-Tutorials
This repository consists of tutorials useful for beginner level exploitation and OS architectures.

**Note**

The code has been written for Unix based Systems.
The Assembly code is written in AT&T style syntax and compiled with gcc. It refers to 64-bit registers (%rsi, %rax, etc.). 

The exploits run successfully on a 32-bit machine without the DEP feature. The 64 bit architecture pretty much eliminates the chance of the exploits' success alltogether. If you wish to run the code on 32-bit systems, replace the 'r' in each register with 'e' (eg - %esi instead of %rsi, etc.).

#**Compilation**

1. For generating Debugger Information:

**gcc FILENAME -ggdb -o EXECUTABLE_NAME**

2. For normal Compilation:

**gcc FILENAME -o EXECUTABLE_NAME**

example:

gcc format_string_2.s -ggdb -o fs2
