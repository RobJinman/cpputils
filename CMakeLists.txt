cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "cpputils")
set(CPPUTILS_LIB_NAME "cpputils")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${CPPUTILS_LIB_NAME} ${SRCS})

add_subdirectory(test)
