cmake_minimum_required(VERSION 3.28)
project(11SimpleSearchEngine)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib)

add_executable(11SimpleSearchEngine
        bin/main.cpp
        lib/engine.hpp)
