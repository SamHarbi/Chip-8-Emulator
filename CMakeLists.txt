cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Chip8Emulator VERSION 1.0)
add_executable(Chip8Emulator src/main.cpp src/renderer.cpp src/cpu.cpp src/glfwinput.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Chip8Emulator glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Chip8Emulator GLEW::glew)
