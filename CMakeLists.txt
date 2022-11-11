cmake_minimum_required(VERSION 3.5)
project (lab)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(compilier  src/inout/classes.cpp
                          src/inout/inout.cpp
                          src/exceptions/exceptions.cpp
                          src/lexer/classes.cpp
                          src/lexer/lexer.cpp
                          src/compilier/compilier.cpp
                          )