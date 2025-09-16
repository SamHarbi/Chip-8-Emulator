#include "glfwinput.h"

GLFWInput::GLFWInput(GLFWwindow* intwindow) {
    window = intwindow;
    //keys.insert(std::pair{"ESC", false});
}
GLFWInput::~GLFWInput() {}

void GLFWInput::poll() {
    glfwPollEvents();

    glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS ? keys[0x0] = true: keys[0x0] = false;
    glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS ? keys[0x1] = true: keys[0x1] = false;
    glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS ? keys[0x2] = true: keys[0x2] = false;
    glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS ? keys[0x3] = true: keys[0x3] = false;
    glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS ? keys[0x4] = true: keys[0x4] = false;
    glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS ? keys[0x5] = true: keys[0x5] = false;
    glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS ? keys[0x6] = true: keys[0x6] = false;
    glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS ? keys[0x7] = true: keys[0x7] = false;
    glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS ? keys[0x8] = true: keys[0x8] = false;
    glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS ? keys[0x9] = true: keys[0x9] = false;

    glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? keys[0xA] = true: keys[0xA] = false;
    glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS ? keys[0xB] = true: keys[0xB] = false;
    glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS ? keys[0xC] = true: keys[0xC] = false;
    glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? keys[0xD] = true: keys[0xD] = false;
    glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS ? keys[0xE] = true: keys[0xE] = false;
    glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS ? keys[0xF] = true: keys[0xF] = false;

    // Non emulator controls
    //glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ? keys[0xESC] = true: keys[0xESC] = false;
    
}

bool GLFWInput::queryKey(uint8_t name) {
    return keys[name];
}

bool GLFWInput::isAnyKeyPressed(uint8_t &keyThatIsPressed) {
    for( auto key : keys ) {
        if (std::get<1>(key)) {
            keyThatIsPressed = std::get<0>(key);
            return true;
        }
    }
    return false;
}