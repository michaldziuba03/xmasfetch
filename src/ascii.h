#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

const std::string ASCII_TREE[] = {
        R"(      $4**      )",
        R"(      $3/\      )",
        R"(     $3/\$4*$3\     )",
        R"(    $3/\$6o$3\*\    )",
        R"(   $3/*/\/$2o$3/\   )",
        R"(  $3/\$5o$3\/\$4*$3\/\  )",
        R"( $3/\$4*$3\/\*\/\/\ )",
        R"($3/\$2o$3\/\/$4*$3/\/$2o$3/\)",
        R"(    $4\____/    )",
};

const size_t ASCII_TREE_SIZE = std::ssize(ASCII_TREE);
