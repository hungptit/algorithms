PROJECT(Algorithms)
CMAKE_MINIMUM_REQUIRED(VERSION 3.24.0)

include(${PROJECT_SOURCE_DIR}/cmake/catch2.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/glaze.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/fmt.cmake)

# Custom options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
