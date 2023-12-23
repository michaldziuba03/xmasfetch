cmake_minimum_required(VERSION 3.22)
project(xmasfetch)

set(CMAKE_CXX_STANDARD 20)

set(XMASFETCH_SRC
        utils.hxx
        ascii.h
        info.cpp
        info.h
        colors.cpp
        colors.h)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND XMASFETCH_SRC
        linux/linux_info.cpp
        linux/linux_info.h)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND XMASFETCH_SRC
    windows/wmi.hxx
    windows/windows_info.cpp
    windows/windows_info.h)
endif ()

add_executable(xmasfetch main.cpp ${XMASFETCH_SRC})
