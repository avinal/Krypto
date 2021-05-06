cmake_minimum_required(VERSION 3.1)
set(PROJECT_NAME Krypto)

project(${PROJECT_NAME} VERSION 0.1)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
elseif (CMAKE_CXX_STANDARD LESS 14)
    message(WARNING "CMAKE_CXX_STANDARD has been set to '${CMAKE_CXX_STANDARD}' which is lower than the minimum required standard (c++14).")
endif ()

message(STATUS "Using C++ standard c++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message (STATUS "CMake version: ${CMAKE_VERSION}")
message (STATUS "Project version: ${PROJECT_VERSION}")

add_subdirectory(blowfish)

file(GLOB KRYPTO_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)


file(GLOB KRYPTO_INC ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(${PROJECT_NAME} ${KRYPTO_SRC} ${KRYPTO_INC})
target_include_directories(${PROJECT_NAME} PRIVATE blowfish/include PUBLIC include)
target_link_libraries(${PROJECT_NAME} blowfish)
