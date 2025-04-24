cmake_minimum_required(VERSION 3.30)
project(P2 C)

set(CMAKE_C_STANDARD 11)

add_executable(P2 main.c
        Library/vector.c
        Library/vector.h
        Library/read.c
        Library/read.h
        Library/ray.c
        Library/ray.h
)
