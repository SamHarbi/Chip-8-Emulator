#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// g++ src/main.cpp -I ./include/ -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
    return 0;
}