cmake_minimum_required(VERSION 3.29)
project(LEDAS_test_task)
set(CMAKE_CXX_STANDARD 20)

set(exe_name ${PROJECT_NAME})
set(test_name Tests)
set(lib_name ltt-lib)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(${lib_name} OBJECT src/vector-3d.cpp src/segment-3d.cpp)
add_executable(${exe_name} src/main.cpp)
target_link_libraries(${exe_name} ${lib_name})
target_include_directories(${lib_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${lib_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${test_name} test/tests.cpp)
target_link_libraries(${test_name} gtest_main ${lib_name})
