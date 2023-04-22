cmake_minimum_required(VERSION 3.24)
project(Bank_Management_System C)

set(CMAKE_C_STANDARD 11)

add_executable(Bank_Management_System main.c Linked_List.h Linked_List.c System_Methods.h System_Methods.c Linked_List_config.h)
