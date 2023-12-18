cmake_minimum_required(VERSION 3.26)
project(xmasfetch)

set(CMAKE_CXX_STANDARD 20)

add_executable(xmasfetch main.cpp
        wmi.hxx
        windows_info.cpp
        windows_info.h
        utils.hxx
        ascii.h)
