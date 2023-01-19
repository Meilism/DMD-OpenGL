#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// DMD_MODE: Create a window and send frames on a secondary monitor. Otherwise on primary monitor.
// const bool DMD_MODE = true;

GLFWwindow* setUpWindow();
void processInput(GLFWwindow* window);

// setUpWindow: sets up a window using GLFW and returns a pointer to the window. Returns NULL on failure.
GLFWwindow* setUpWindow() {

    // GLFW Setup
    if (not(glfwInit())) {
        std::cout << "GLFW Initialization Failure\n";
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__    // Additional GLFW initialization for Mac        
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Wether the full screen window will automatically iconify
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    if (count == 0){
        std::cout << "No monitor connected, unable to initialize.\n";
        return NULL;
    }

    // Select the last monitor as display
    GLFWmonitor* monitor;
    monitor = monitors[count-1];

    // Get current video mode of traget monitor and set the GLFW window hint
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    std::cout << "Target monitor properties:\n\twidth = " << mode->width << "\theight = " << mode->height 
    << "\n\tredBits = " << mode->redBits << "\tgreenBits = " << mode->greenBits << "\tblueBits = " << mode->blueBits
    << "\trefreshRate = " << mode->refreshRate << "\n";

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "DMD Test Window", monitor, NULL);

    // Check if current video mode is correct
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if ((width != mode->width)|(height != mode->height)){
        std::cout << "Incompatible video mode\n";
        std::cout << "Window Frame buffer size:\n\twidth = " << width << "\theight = " << height << "\n";
        return NULL;
    }

    if (!window) {
        std::cout << "Failed to create GLFW window\n";
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return NULL;
    }

    // Hide the mouse cursor when it is on top of the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    return window;
}

// processInput: iconify window if the escape key is being pressed.
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // glfwIconifyWindow(window);
        glfwSetWindowShouldClose(window, true);
    return;
}

int main(){
    GLFWwindow* window = setUpWindow();
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}