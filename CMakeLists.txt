cmake_minimum_required(VERSION 3.20)

project(agrade VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libagrade)

add_executable(agrade main.cpp)

target_link_libraries(agrade PUBLIC libagrade)

target_include_directories(agrade PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/libagrade"
)

