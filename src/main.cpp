#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int main()
{

    //=========================================================================
    // SOME VARIABLES
    //=========================================================================
    const int width = 1280;
    const int height = 720;
    GLFWwindow *window;
    unsigned char *readData;

    readData = new unsigned char[width * height * 3];

    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.1, since it's the last one providing glDrawPixels
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "PaintLike", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // Initialize GLEW

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {

        glfwPollEvents();
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5,0.4,0.3,1);

        for(int i = 0; i < height * width * 3; i++)
            readData[i] = rand() % 255;

        // Draw
        glDrawPixels( width, height, GL_RGB, GL_UNSIGNED_BYTE, readData);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    return 0;
}