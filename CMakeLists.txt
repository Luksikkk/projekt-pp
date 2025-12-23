cmake_minimum_required(VERSION 4.1)
project(Projekt_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Projekt_C main.c
        include/menu/menu.h
        src/menu/menu.c
)
