cmake_minimum_required(VERSION 3.15)

project(MicroBasic VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(microbasic)

install(TARGETS microbasic DESTINATION bin)

target_sources(microbasic
    PRIVATE
        src/main.cpp
        src/lexer.cpp
        src/parser.cpp
        src/ast.cpp
        src/vm.cpp
        src/analyzer.cpp
)


