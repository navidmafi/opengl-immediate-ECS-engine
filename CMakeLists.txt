cmake_minimum_required(VERSION 3.20)

project(testas)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
add_subdirectory(glad/)

add_executable(testas 
    src/main.cpp 
    src/shaderload.cpp
)

target_link_libraries(testas PUBLIC glad glfw fmt)