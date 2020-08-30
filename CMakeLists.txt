cmake_minimum_required(VERSION 3.17)
project(maco)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(maco
        include/maco/basic.h
        include/maco/pp_size.h
        include/maco/repeat_call.h
        include/maco/repeats.h
        tests/test_maco.cpp)