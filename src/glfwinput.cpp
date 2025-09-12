#include "glfwinput.h"

GLFWInput::GLFWInput() {}
GLFWInput::~GLFWInput() {}


void GLFWInput::InputInit(GLFWwindow* intwindow) {
    window = intwindow;
}

void GLFWInput::poll() {
    glfwPollEvents();

    int state = glfwGetKey(window, GLFW_KEY_E);
    if (state == GLFW_PRESS) {
        std::cout << "KEY PRESSED" << std::endl;
        key_E = true;
    } else { key_E = false; }
}