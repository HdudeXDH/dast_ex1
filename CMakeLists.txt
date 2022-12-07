cmake_minimum_required(VERSION 3.21)
project(dast_ex1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dast_ex1
        main23a1.cpp
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h player.cpp team.cpp)

#add_executable(dast_ex1 main.cpp )
#