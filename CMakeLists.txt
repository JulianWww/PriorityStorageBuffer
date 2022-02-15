project(AlphaZero)

set (CMAKE_CXX_STANDARD 20)
cmake_minimum_required (VERSION 3.8)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main "main.cpp")
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include")