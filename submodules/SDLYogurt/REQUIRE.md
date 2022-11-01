# OS

Windows 10 Version 10.0.19043 Build 19043

# Software requirements

clang-format version 13.0.0 (https://github.com/llvm/llvm-project d7b669b3a30345cfcdb2fde2af6f48aa4b94845d)
cmake version 3.21.2
gcc.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
git version 2.23.0.windows.1
clang-tidy :
  LLVM version 12.0.0-6923b0a7
  Optimized build with assertions.
  Default target: x86_64-pc-windows-msvc
  Host CPU: skylake
Visual Studio Code 1.63.0

# Compiler flags

## UNIX

### DEBUG

--std=c++2a -pedantic -Wall -Wextra -Werror -Wconversion -Od

### RELEASE

--std=c++2a -pedantic -Wall -Wextra -Werror -Wconversion -O2

## MSVC

### DEBUG
/W4
/WX
/MTd
/Od>

### RELEASE
/W4
/WX
/MT
/O2>



