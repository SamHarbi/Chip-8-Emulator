#include "glfwinput.h"

GLFWInput::GLFWInput() {

}

GLFWInput::~GLFWInput() {

}

void GLFWInput::poll() {
    glfwPollEvents();
}