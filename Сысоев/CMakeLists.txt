cmake_minimum_required(VERSION 3.10)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

project(dynamic_stack)

include_directories(base gtest)

# BUILD
add_subdirectory(base)
add_subdirectory(base_test)
add_subdirectory(gtest)
