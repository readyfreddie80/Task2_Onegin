cmake_minimum_required(VERSION 3.13)
project(Task2_Onegin)

set(CMAKE_CXX_STANDARD 14)

add_executable(Task2_Onegin main.cpp texts.h texts.cpp stdfuncs_wrappers.cpp stdfuncs_wrappers.h project_defines.h texts_tests.cpp)