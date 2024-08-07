project(algorithm-solution)

cmake_minimum_required(VERSION 3.25)

# Custom options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/fmt.cmake)
include(cmake/catch2.cmake)

# sub-directories
add_subdirectory(src)

enable_testing()
