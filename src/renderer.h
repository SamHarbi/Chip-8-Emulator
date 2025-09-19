#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "glfwinput.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    int init();
    int render();
    void inputDisplayData(uint32_t *data);
    void generateRandomTestData();

    GLFWInput *input;

private:
    unsigned int VBO;
    unsigned int VAO; // Going to use a single VAO here, don't expect the need for multiple atm
    unsigned int EBO;
    unsigned int program;
    unsigned int texture;
    GLFWwindow *window;

    // Draw a quad covering the whole screen
    float vertices[32] = { // Position 3 floats - Color 3 FLoats - Texture 2 Floats
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[6] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    float texture_cords[6] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f};

    int readShaderFromFile(std::string &shader, std::string shaderFileName);
    std::unique_ptr<std::vector<uint32_t, std::allocator<uint32_t>>> generateRandomTexture();

    // Basic debug shaders in case we need em during dev, actual shaders are read during runtime from src/shaders
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