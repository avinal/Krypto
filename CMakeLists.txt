cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME MCPS)
file(GLOB SOURCES src/*.cpp)

project(${PROJECT_NAME} VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)

add_subdirectory(blowfish)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE blowfish/include PUBLIC include)
