#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

const std::string ASCII_TREE[] = {
        R"(      $2**      )",
        R"(      $0/\      )",
        R"(     $0/\$2*$0\     )",
        R"(    $0/\$4o$0\*\    )",
        R"(   $0/*/\/$1o$0/\   )",
        R"(  $0/\$3o$0\/\$2*$0\/\  )",
        R"( $0/\$2*$0\/\*\/\/\ )",
        R"($0/\$1o$0\/\/$2*$0/\/$1o$0/\)",
        R"(    $2\____/    )",
};

const size_t ASCII_TREE_SIZE = std::ssize(ASCII_TREE);
