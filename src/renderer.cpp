#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "renderer.h"

Renderer::Renderer() {}

int Renderer::init(void)
{
    /*
        Setup Window (GLFW)
    */

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Couldn't init GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    Renderer::window = glfwCreateWindow(640, 320, "Chip8", NULL, NULL);
    if (!Renderer::window)
    {
        std::cout << "Couldn't create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);

    /* Make the window's context current */
    glfwMakeContextCurrent(Renderer::window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    /*
        Compile Shaders
    */

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &(Renderer::vertexShaderSource), NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &(Renderer::fragmentShaderSource), NULL);
    glCompileShader(fragmentShader);

    Renderer::program = glCreateProgram();
    glAttachShader(Renderer::program, vertexShader);
    glAttachShader(Renderer::program, fragmentShader);
    glLinkProgram(Renderer::program);

    glUseProgram(Renderer::program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*
        Load in texture data
    */
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    /*
        Setup OpenGL Buffers and more
    */

    // Gen and set VAO
    glGenVertexArrays(1, &(Renderer::VAO));
    glBindVertexArray((Renderer::VAO));

    // Vertex Buffer VBO
    glGenBuffers(1, &(Renderer::VBO));
    glBindBuffer(GL_ARRAY_BUFFER, (Renderer::VBO));
    glBufferData(GL_ARRAY_BUFFER, sizeof(Renderer::vertices), Renderer::vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &(Renderer::EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (Renderer::EBO));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Renderer::indices), Renderer::indices, GL_STATIC_DRAW);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return 0;
}

void Renderer::processInput(GLFWwindow *local_window)
{
    if (glfwGetKey(local_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(local_window, true);
}

int Renderer::render()
{
    if (!glfwWindowShouldClose(Renderer::window))
    {
        glUseProgram(program);

        processInput(Renderer::window);

        // Prepare Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, (Renderer::VBO));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(0);

        /* Render starts here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(Renderer::window);
        glfwPollEvents();

        return 0;
    }
    else
    {
        glfwTerminate();
        return 1;
    }
}