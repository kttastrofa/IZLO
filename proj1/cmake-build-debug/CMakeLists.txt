cmake_minimum_required(VERSION 3.27)
project(IZLO C)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(IZLO
        code/add_conditions.c
        code/cnf.h
        code/main.c)
