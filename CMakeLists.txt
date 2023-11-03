cmake_minimum_required(VERSION 3.25)
project(Local_File_Search_Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Local_File_Search_Engine)
set(SOURCE src/main.cpp)

#== Source Program ==#

include_directories(src/lib/include/nlohmann)

set(LIBRARY_CONVERTER src/lib/ConverterJSON.cpp src/lib/ConverterJSON.h)
set(LIBRARY_SERVER src/lib/SearchServer.h src/lib/SearchServer.cpp)
set(LIBRARY_INVERTED_INDEX src/lib/InvertedIndex.cpp src/lib/InvertedIndex.h)

add_executable(${PROJECT_NAME} ${SOURCE})

add_library(MyConverterJSON SHARED ${LIBRARY_CONVERTER})
add_library(SearchServer SHARED ${LIBRARY_SERVER})
add_library(InvertedIndex SHARED ${LIBRARY_INVERTED_INDEX})
target_link_libraries(${PROJECT_NAME} PRIVATE SearchServer MyConverterJSON)
target_link_libraries(SearchServer PUBLIC InvertedIndex)