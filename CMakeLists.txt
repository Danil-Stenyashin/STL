cmake_minimum_required(VERSION 3.10)
project(circular_list)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(circular_list_tests test.cpp)
target_link_libraries(circular_list_tests GTest::GTest GTest::Main)

enable_testing()
add_test(NAME circular_list_tests COMMAND circular_list_tests)
