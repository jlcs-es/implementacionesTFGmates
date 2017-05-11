cmake_minimum_required(VERSION 3.6)
project(ZKP_impl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp QR.cpp QR.h)
add_executable(ZKP_impl ${SOURCE_FILES})
target_link_libraries(ZKP_impl gmp)
