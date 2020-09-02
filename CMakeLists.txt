cmake_minimum_required(VERSION 3.17)
project(maco)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -E ")

add_executable(maco
        tests/catch.cpp
        include/maco/basic.h
        include/maco/detail/pp_size.h
        include/maco/detail/repeat_call.h
        tests/test_maco.cpp include/maco/aggregate.h include/maco/foreach.h include/maco/foreach_2.h include/maco/repeats_0.h include/maco/repeats_1.h include/maco/pp_size.h include/maco/condtion.h)