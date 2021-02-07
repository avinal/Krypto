cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME RCRS)
file(GLOB SOURCES src/*.cpp)

project(${PROJECT_NAME} VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)

add_subdirectory(SQLiteCpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE SQLiteCpp/include PUBLIC include)
target_link_libraries(${PROJECT_NAME}
  SQLiteCpp
  sqlite3
  pthread
  dl
  )