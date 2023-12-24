cmake_minimum_required(VERSION 3.22)
project(xmasfetch)

set(CMAKE_CXX_STANDARD 20)

set(XMASFETCH_SRC
        src/utils.hxx
        src/ascii.h
        src/info.cpp
        src/info.h
        src/colors.cpp
        src/colors.h)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND XMASFETCH_SRC
            src/linux/linux_info.cpp
            src/linux/linux_info.h)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND XMASFETCH_SRC
            src/windows/wmi.hxx
            src/windows/windows_info.cpp
            src/windows/windows_info.h)
endif ()

add_executable(xmasfetch src/main.cpp ${XMASFETCH_SRC})
