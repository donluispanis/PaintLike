#include "PaintLike.h"
#include <iostream>
#include <GLFW/glfw3.h>

//Window and functionality initialization
//Parameters: Witdh, Height
bool PaintLike::Init(int w, int h)
{
    width = w;
    height = h;

    screenData = new unsigned char[width * height * 3];

    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.1, since it's the last one providing glDrawPixels
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "PaintLike", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    clockOld = std::chrono::system_clock::now();
    clockNow = clockOld;

    std::cerr << "PaintLike has succesfully started\n";

    return true;
}

//Engine basic update
void PaintLike::Run()
{
    while (glfwWindowShouldClose(window) == 0)
    {
        //Sort input events
        glfwPollEvents();

        //Extract framerate
        clockOld = clockNow;
        clockNow = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = clockNow-clockOld;
        fDeltaTime = elapsed_seconds.count();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //Perform drawing over the pixel matrix
        Draw();

        // Draw
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, screenData);

        // Swap buffers
        glfwSwapBuffers(window);

        std::cout << 1/fDeltaTime << std::endl;
    }
}

//Window and variables deletion
PaintLike::~PaintLike()
{
    delete[] screenData;

    glfwDestroyWindow(window);
    glfwTerminate();
}

//Drawing the screen
void PaintLike::Draw()
{
    for (int i = 0; i < height * width * 3; i++)
        screenData[i] = rand() % 256;
}