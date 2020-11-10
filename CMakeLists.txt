cmake_minimum_required(VERSION 3.15)
project(RNA)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(RNA main.cpp RNA.h rna.cpp cmake-build-debug/lib/Tests/RNA.h cmake-build-debug/lib/Tests/Tests.cpp)

target_link_libraries(RNA gtest gtest_main)