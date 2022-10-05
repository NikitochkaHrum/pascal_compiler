cmake_minimum_required(VERSION 3.5)
project (lab)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(lab src/classes.cpp src/inout.cpp)