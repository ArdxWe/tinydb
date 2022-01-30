cmake_minimum_required(VERSION 3.16)
project(bitmask)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Werror)

add_executable(bitmask
               src/main.cpp
               src/Block.cpp
               src/Block.h
               src/Datafile.cpp
               src/Datafile.h
               src/Conf.cpp
               src/Conf.h
               src/Util.cpp
               src/Util.h)
