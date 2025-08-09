#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    //Sized as per chip8 specification (Width x Height)
    bool screen[64][32];

    Renderer();
    int init();
    int render();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int program;
    GLFWwindow *window;

    // Draw a quad covering the whole screen
    float screen_verts[18] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
    };


    void processInput(GLFWwindow *window);

    // Honestly not worth reading these in from a separate file, minimal shaders is all that will ever be needed for this project
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
};