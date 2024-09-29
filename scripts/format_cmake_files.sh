#!/bin/bash
format_cmake_files() {
    shift

    # Find all C++ source files in the grpc directory
    files=$(fd "(CMakeLists.txt$|.cmake$)" "$@")

    # Check if any files were found
    if [ -z "$files" ]; then
        echo "No C++ source files found in grpc directory"
        exit 1
    fi

    # Format the found files
    cmake-format -i $files
}

format_cmake_files "CMakeLists.txt$" grpc duckdb sqlite arrow boost glaze utilities
format_cmake_files "[.]cmake$" cmake
