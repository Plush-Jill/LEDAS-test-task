cmake_minimum_required(VERSION 3.29)
project(LEDAS_test_task)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME LEDAS-test-task)
set(TESTS_NAME Tests)
set(LIB_NAME ltt-lib)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(${LIB_NAME} OBJECT
        src/vector-3d.cpp
        src/segment-3d.cpp
)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(${EXECUTABLE_NAME}
        src/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME} ${LIB_NAME})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${TESTS_NAME}
        test/vector-test.cpp
        test/segment-test.cpp
)

target_link_libraries(${TESTS_NAME} gtest_main ${LIB_NAME})
target_include_directories(${TESTS_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
