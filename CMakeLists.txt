cmake_minimum_required(VERSION 3.25)
project(Local_File_Search_Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(PROJECT_NAME Local_File_Search_Engine)
set(SOURCE src/SearchEngine.cpp src/InvertedIndex.cpp src/ConverterJSON.cpp src/SearchServer.cpp)
#== Directories ==#
file(MAKE_DIRECTORY json)
file(MAKE_DIRECTORY res)

#== Source Program ==#

include_directories(${MY_INCLUDE_DIR}/)
include_directories(include/nlohmann/)

add_executable(${PROJECT_NAME} ${SOURCE})

add_subdirectory(test/)