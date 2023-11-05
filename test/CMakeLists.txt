cmake_minimum_required(VERSION 3.25)
project(program_tests)

set(SrcFiles
        ../src/InvertedIndex.cpp
        ../src/SearchServer.cpp
        ../src/ConverterJSON.cpp
        )

set(TestsFiles
        FinalTest.cpp
        StandardTest.cpp
        )


include_directories(../include)
include_directories(../include/nlohmann/)

add_executable(GtestTests ${TestsFiles} ${SrcFiles})

add_subdirectory(include/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_include_directories(GtestTests PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(GtestTests gtest gtest_main)

include(GoogleTest)

gtest_discover_tests(GtestTests)