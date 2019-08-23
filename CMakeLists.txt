cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(test_cmake CXX)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
endif()

# 出力ディレクトリを指定
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")



include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
