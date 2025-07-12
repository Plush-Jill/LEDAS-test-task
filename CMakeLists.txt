cmake_minimum_required(VERSION 3.29)
project(LEDAS_test_task)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME LEDAS-test-task)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(${EXECUTABLE_NAME}
        src/main.cpp
        include/vector-3d.hpp
        src/vector-3d.cpp
        include/segment-3d.hpp
        src/segment-3d.cpp
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)