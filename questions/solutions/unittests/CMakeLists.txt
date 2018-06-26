PROJECT(TOOLS)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
set(EXTERNAL_DIR "${ROOT_DIR}../3p")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CheckCXXCompilerFlag)
include(AddCXXCompilerFlag)
include(CXXFeatureCheck)

# set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_BUILD_TYPE Release)
add_cxx_compiler_flag(-O3)
add_cxx_compiler_flag(-march=native)
add_cxx_compiler_flag(-std=c++14)
add_cxx_compiler_flag(-Wall)
add_cxx_compiler_flag(-flto)

add_cxx_compiler_flag(-fstrict-aliasing)
if (HAVE_CXX_FLAG_FSTRICT_ALIASING)
  add_cxx_compiler_flag(-Wstrict-aliasing)
endif()
# add_cxx_compiler_flag(-Wthread-safety)
if (HAVE_WTHREAD_SAFETY)
  add_definitions(-DHAVE_WTHREAD_SAFETY)
  cxx_feature_check(THREAD_SAFETY_ATTRIBUTES)
endif()

add_cxx_compiler_flag(-DFMT_HEADER_ONLY)
add_cxx_compiler_flag(-DCEREAL_RAPIDJSON_HAS_CXX11_RVALUE_REFS)
add_cxx_compiler_flag(-flto)

ENABLE_TESTING()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include other headers such as fmt library.
include_directories ("${EXTERNAL_DIR}/include")

# Include utils headers
include_directories ("../src")

set(COMMAND_SRC_FILES max_sum 4_1 dfs bfs dag_loop sorted_list data_structures)
foreach (src_file ${COMMAND_SRC_FILES})
  ADD_EXECUTABLE(${src_file} ${src_file}.cpp)
  TARGET_LINK_LIBRARIES(${src_file})
  ADD_TEST(${src_file} ./${src_file})
endforeach (src_file)
