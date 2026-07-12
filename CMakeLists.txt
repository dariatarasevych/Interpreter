cmake_minimum_required(VERSION 4.2)
project(assignment_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment_5 main.cpp
        Token.h
        Tokenization.cpp
        Tokenization.h
        Environment.cpp
        Environment.h)
