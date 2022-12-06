cmake_minimum_required(VERSION 3.21)
project(dast_ex1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dast_ex1
        main23a1.cpp
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h)

#add_executable(dast_ex1 main.cpp test_maker/test_AVL_insertions_deletions.h test_maker/test_AVL_memory_leaks.h)
