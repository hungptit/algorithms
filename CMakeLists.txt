PROJECT(Algorithms)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(${ROOT_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Read the git tags to determine the project version
include(GetGitVersion)
get_git_version(GIT_VERSION)

# Tell the user what versions we are using
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" VERSION ${GIT_VERSION})
message("-- Version: ${VERSION}")

# The version of the libraries
set(GENERIC_LIB_VERSION ${VERSION})
string(SUBSTRING ${VERSION} 0 1 GENERIC_LIB_SOVERSION)

include(CheckCXXCompilerFlag)
include(AddCXXCompilerFlag)
include(CXXFeatureCheck)

# set(CMAKE_BUILD_TYPE Debug)

set (CMAKE_BUILD_TYPE Release)
add_cxx_compiler_flag(-O4)

add_cxx_compiler_flag(-std=c++14)
add_cxx_compiler_flag(-Wall)
add_cxx_compiler_flag(-Wextra)
add_cxx_compiler_flag(-Wshadow)

add_cxx_compiler_flag(-Werror RELEASE)
add_cxx_compiler_flag(-Werror RELWITHDEBINFO)
add_cxx_compiler_flag(-Werror MINSIZEREL)

add_cxx_compiler_flag(-pedantic)
add_cxx_compiler_flag(-pedantic-errors)

add_cxx_compiler_flag(-Wshorten-64-to-32)
add_cxx_compiler_flag(-Wfloat-equal)
add_cxx_compiler_flag(-Wint-to-void-pointer-cast)
add_cxx_compiler_flag(-fstrict-aliasing)
if (HAVE_CXX_FLAG_FSTRICT_ALIASING)
  add_cxx_compiler_flag(-Wstrict-aliasing)
endif()
add_cxx_compiler_flag(-Wthread-safety)
if (HAVE_WTHREAD_SAFETY)
  add_definitions(-DHAVE_WTHREAD_SAFETY)
  cxx_feature_check(THREAD_SAFETY_ATTRIBUTES)
endif()

add_cxx_compiler_flag(-DFMT_HEADER_ONLY)
add_cxx_compiler_flag(-DCEREAL_RAPIDJSON_HAS_CXX11_RVALUE_REFS)

set(CMAKE_CXX_COMPILER "clang++")

ENABLE_TESTING()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Used libraries
set(LIB_GTEST "${ROOT_DIR}/lib/libgtest.a")
set(LIB_GTEST_MAIN "${ROOT_DIR}/lib/libgtest_main.a")

# Libraries used by rocksdb
set(LIB_TBB_MALLOC "${ROOT_DIR}/lib/libtbb.so")
set(LIB_CELERO "${ROOT_DIR}/bin/libcelero.so")

# This option make sure that we use the local boost version. Note that if the 
# system boost is installed then CMake might use that boost version.
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
message("${BOOST_ROOT}")

find_package(Boost 1.60 REQUIRED regex date_time system filesystem thread graph program_options iostreams)

# Include folder
include_directories ("${ROOT_DIR}/include")
include_directories ("${ROOT_DIR}/sbutils")

# Use POCO static library
include_directories("${ROOT_DIR}/include")
set(LIB_POCO_FOUNDATION "${ROOT_DIR}/lib/libPocoFoundation.a")

if (Boost_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})

  set(UNITTEST_SRC_FILES tBalancedBrackets tUniqueCharacters tWildcardMatching tAnagram tReverseString tRemoveDuplicatedCharacters tRotateImage tSum tTowerOfHanoi tStockProfit tMinNumCoins tDecompressString tPermutation prob_7_14 tpriorioty_queue tree_height)

  foreach (src_file ${UNITTEST_SRC_FILES})
    ADD_EXECUTABLE(${src_file} ${src_file}.cpp)
    TARGET_LINK_LIBRARIES(${src_file} ${Boost_LIBRARIES}  ${LIB_GTEST} ${LIB_GTEST_MAIN} ${LIB_CELERO} -lpthread)
    ADD_TEST(${src_file} ./${src_file})
  endforeach (src_file)

  include_directories(${BOOST_INCLUDE_DIRS})
  set(UNITTEST_SRC_FILES pUniqueCharacters)
  foreach (src_file ${UNITTEST_SRC_FILES})
    ADD_EXECUTABLE(${src_file} ${src_file}.cpp)
    TARGET_LINK_LIBRARIES(${src_file} ${LIB_CELERO} -lpthread)
  endforeach (src_file) 
endif (Boost_FOUND)
