cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_FLAGS "-Llib")
project (OpenGL)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/imgui
        ${PROJECT_SOURCE_DIR}/include/stb
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB_RECURSE all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
add_executable(OpenGL ${all_SRCS})
set_target_properties(OpenGL PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
target_link_libraries(OpenGL "${PROJECT_SOURCE_DIR}/glfw3.dll")
