#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "input.h"

class GLFWInput: public IInput {
    private:
        GLFWwindow *window;

    public:
        GLFWInput(GLFWwindow* initwindow);
        ~GLFWInput();

        void poll(); // Populate class members
        bool queryKey(uint8_t name);
        bool isAnyKeyPressed(uint8_t &keyThatIsPressed);
};