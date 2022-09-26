cmake_minimum_required(VERSION 3.14)

project(NtWin32)

include(FetchContent)
FetchContent_Declare(
    phnt
    GIT_REPOSITORY https://github.com/processhacker/phnt.git
    GIT_TAG        d6135b7b616b48be3b4e09852964d3f9640b5a56
)
FetchContent_MakeAvailable(phnt)

# Disable runtime error checks
string(REGEX REPLACE "/RTC[^ ]*" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(headerFiles
    Windows.h
        minwindef.h
    ntdll.h
)
list(TRANSFORM headerFiles PREPEND include/NtWin32/)
set(sourceFiles
    errhandlingapi.cpp
)
list(TRANSFORM sourceFiles PREPEND source/)
add_library(NtWin32 ${headerFiles} ${sourceFiles})
target_compile_options(NtWin32 PRIVATE /Zl)  # Disable default libraries
target_include_directories(NtWin32 PUBLIC include)
target_link_libraries(NtWin32 PUBLIC phnt)

# test
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(BUILD_TESTING "Build the testing tree." OFF)
    include(CTest)
    if(BUILD_TESTING)
        #find_package(Catch2 3 REQUIRED)
        #FetchContent_Declare(
        #    Catch2
        #    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        #    GIT_TAG        v3.1.0
        #)
        #FetchContent_MakeAvailable(Catch2)
        
        set(CMAKE_C_STANDARD_LIBRARIES "ntdll.lib" CACHE STRING "Libraries linked into every executable and shared library linked for C." FORCE)
        set(CMAKE_CXX_STANDARD_LIBRARIES "ntdll.lib" CACHE STRING "Libraries linked into every executable and shared library linked for C++." FORCE)
	
        add_executable(NtWin32_test test/test.cpp)
	    target_link_options(NtWin32_test PRIVATE /NODEFAULTLIB /ENTRY:main)
        target_link_libraries(NtWin32_test
        PRIVATE
            NtWin32
            #Catch2::Catch2
        )
    endif()
endif()