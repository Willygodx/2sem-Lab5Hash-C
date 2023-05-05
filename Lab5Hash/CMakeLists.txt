cmake_minimum_required(VERSION 3.24)
project(Lab5Hash C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab5Hash main.c check.c check.h cache.c cache.h memory.c memory.h menu.c menu.h functions.c functions.h)
