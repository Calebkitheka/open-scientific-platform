cmake_minimum_required(VERSION 3.16)
project(SciShell VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(scishell src/main.cpp)

if(MSVC)
    target_compile_options(scishell PRIVATE /W4 /WX)
else()
    target_compile_options(scishell PRIVATE -Wall -Wextra -Wpedantic)
endif()

message(STATUS "Building SciShell v${PROJECT_VERSION} on ${CMAKE_SYSTEM_NAME}")