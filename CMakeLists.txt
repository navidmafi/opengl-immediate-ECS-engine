cmake_minimum_required(VERSION 3.20)

project(testas)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLU REQUIRED)
add_subdirectory(glad/)

add_executable(testas 
    src/Clock.cpp
    src/GameHost.cpp
    src/GameObject.cpp
    src/Renderer.cpp
    src/Scene.cpp
    src/Cube.cpp
    src/Sphere.cpp
    src/main.cpp 
)

target_include_directories(testas PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(testas PUBLIC glad glfw OpenGL::GL OpenGL::GLU fmt)