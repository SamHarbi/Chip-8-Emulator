#include "glfwinput.h"

GLFWInput::GLFWInput(GLFWwindow* intwindow) {
    window = intwindow;

    keys.insert(std::pair{"ESC", false});
}
GLFWInput::~GLFWInput() {}

void GLFWInput::poll() {
    glfwPollEvents();

    glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS ? keys["0"] = true: keys["0"] = false;
    glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS ? keys["1"] = true: keys["1"] = false;
    glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS ? keys["2"] = true: keys["2"] = false;
    glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS ? keys["3"] = true: keys["3"] = false;
    glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS ? keys["4"] = true: keys["4"] = false;
    glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS ? keys["5"] = true: keys["5"] = false;
    glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS ? keys["6"] = true: keys["6"] = false;
    glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? keys["7"] = true: keys["7"] = false;
    glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? keys["8"] = true: keys["8"] = false;
    glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? keys["9"] = true: keys["9"] = false;

    glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? keys["A"] = true: keys["A"] = false;
    glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS ? keys["B"] = true: keys["B"] = false;
    glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS ? keys["C"] = true: keys["C"] = false;
    glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? keys["D"] = true: keys["D"] = false;
    glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ? keys["E"] = true: keys["E"] = false;
    glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS ? keys["F"] = true: keys["F"] = false;

    // Non emulator controls
    glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ? keys["ESC"] = true: keys["ESC"] = false;
    
}

bool GLFWInput::queryKey(std::string name) {
    return keys[name];
}