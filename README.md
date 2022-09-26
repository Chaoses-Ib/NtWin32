# NtWin32
Use the Win32 subsystem API while depending only on Ntdll.dll.

## Example
example.cpp:
```cpp
#include <NtWin32/Windows.h>

int main() {
    SetLastError(123);
    DWORD error = GetLastError();
}
```

CMake:
```cmake
# FetchContent_MakeAvailable requires CMake 3.14+
cmake_minimum_required(VERSION 3.14)

project(example)

FetchContent_Declare(
    NtWin32
    GIT_REPOSITORY https://github.com/Chaoses-Ib/NtWin32.git
    # It is recommanded to specify a version instead of using the main branch
    GIT_TAG        main
)
FetchContent_MakeAvailable(NtWin32)

# Disable runtime error checks
string(REGEX REPLACE "/RTC[^ ]*" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_C_STANDARD_LIBRARIES "ntdll.lib" CACHE STRING "Libraries linked into every executable and shared library linked for C." FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "ntdll.lib" CACHE STRING "Libraries linked into every executable and shared library linked for C++." FORCE)

add_executable(example example.cpp)
target_link_options(example PRIVATE /NODEFAULTLIB /ENTRY:main)
target_link_libraries(example PRIVATE NtWin32)
```