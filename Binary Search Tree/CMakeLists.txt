cmake_minimum_required(VERSION 3.25)
project(Binary_Search_Tree C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Binary_Search_Tree
        binarysearchtrees.c
        binarysearchtrees.h)
