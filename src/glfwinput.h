#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "input.h"

class GLFWInput: public IInput {
    private:
        GLFWwindow *window;

    public:
        GLFWInput();
        ~GLFWInput();

        void InputInit(GLFWwindow* initwindow);

        void poll(); // Populate class members
};