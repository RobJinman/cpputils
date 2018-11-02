cmake_minimum_required(VERSION 3.5)

include(externalGoogleTest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_compile_options(-Wall -g -DDEBUG)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(unitTests ${SRCS})

target_link_libraries(unitTests ${CPPUTILS_LIB_NAME} googleTest)
