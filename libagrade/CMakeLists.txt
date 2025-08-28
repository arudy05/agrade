add_library(libagrade agrade.cpp)

target_include_directories(libagrade
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
