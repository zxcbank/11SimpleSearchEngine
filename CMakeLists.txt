cmake_minimum_required(VERSION 3.28)
project(11SearchEngine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(indexation)
add_subdirectory(search)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)