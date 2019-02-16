
cmake_minimum_required(VERSION 3.13)
project(npuzzle)

set(COVERAGE OFF CACHE BOOL "Code coverage flags")

if(COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

set(BUILD_GMOCK   OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

set(GRAPHVIZ_GRAPH_NAME          deps)
set(GRAPHVIZ_GENERATE_PER_TARGET OFF)
set(GRAPHVIZ_GENERATE_DEPENDERS  OFF)
set(GRAPHVIZ_IGNORE_TARGETS )

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(googletest)

add_library(solver)

target_include_directories(solver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(solver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/InputParser.h
        ${CMAKE_CURRENT_LIST_DIR}/include/Puzzle.h

    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/InputParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Puzzle.cpp
)



add_executable(npuzzle ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

target_link_libraries(npuzzle PUBLIC solver)



add_executable(test)

target_link_libraries(test PUBLIC gtest_main solver)

target_sources(test
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/testInputParserClass.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/testPuzzleClass.cpp
)
