#!/bin/bash -ex

function format_cpp_files {
    pattern=$1
    folder=$2

    # Find all C++ source files in the grpc directory
    files=$(fd "$pattern" "$folder")

    # Check if any files were found
    if [ -z "$files" ]; then
        echo "No C++ source files found in grpc directory"
        exit 1
    fi

    # Format the found files
    clang-format -i $files
}

format_cpp_files ".cc$" grpc
format_cpp_files ".cpp$" tests
format_cpp_files ".cpp$" duckdb
format_cpp_files ".cc$" arrow
format_cpp_files ".cpp$" sqlite
format_cpp_files ".cpp$" glaze
format_cpp_files ".cpp$" boost
format_cpp_files ".cpp$" utilities
format_cpp_files ".cpp$" streaming
