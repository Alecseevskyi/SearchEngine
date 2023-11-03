cmake_minimum_required(VERSION 3.25)
project(program_tests)

add_subdirectory(lib/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests StandardTest.cpp FinalTest.cpp)
add_library(IndexLibrary ../src/lib/InvertedIndex.h ../src/lib/InvertedIndex.cpp)
add_library(ServerLibrary ../src/lib/SearchServer.cpp ../src/lib/SearchServer.h)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests IndexLibrary ServerLibrary)