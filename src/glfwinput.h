#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "input.h"

class GLFWInput: public IInput {
    private:
        GLFWInput();
        ~GLFWInput();

    public:
        void poll(); // Populate class members
};