#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

#include "PaintLike.h"
#include "Tools.h"
#include "Canvas.h"

//===============================================================================
// ENGINE INITIALIZATION
//===============================================================================

//Window and functionality initialization
//Parameters: Witdh, Height
bool PaintLike::Init(const int w, const int h)
{

    if (!InitWindow(w, h))
    {
        std::cerr << "Couldn't open window\n";
        return false;
    }

    if (!InitEngine(w, h))
    {
        std::cerr << "Couldn't init engine\n";
        return false;
    }

    std::cerr << "PaintLike has succesfully started\n";

    return true;
}

//Window and OpenGL initialization
//Parameters: Witdh, Height
bool PaintLike::InitWindow(const int w, const int h)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.1, since it's the last one providing glDrawPixels
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(w, h, "PaintLike", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return true;
}

//Engine initialization
//Parameters: Witdh, Height
bool PaintLike::InitEngine(const int w, const int h)
{
    //Initialize window related variables
    width = w;
    height = h;

    screenData = new unsigned char[width * height * 3];

    //Initialize time related variables
    clockOld = std::chrono::system_clock::now();
    clockNow = clockOld;

    frameCounter = 0;

    //Initialize tools and canvses
    tools.push_back(new Pencil());
    canvas.push_back(new Canvas(width, height));

    currentTool = tools[0];
    currentCanvas = canvas[0];

    return true;
}

//===============================================================================
// ENGINE DESTRUCTION
//===============================================================================

//Window and variables deletion
PaintLike::~PaintLike()
{
    delete[] screenData;

    glfwDestroyWindow(window);
    glfwTerminate();
}

//===============================================================================
// ENGINE UPDATE
//===============================================================================

//Engine basic update
void PaintLike::Run()
{
    while (glfwWindowShouldClose(window) == 0)
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //Update engine time
        UpdateTime();

        //Update input
        UpdateInput();

        //Perform drawing over the pixel matrix
        Draw();

        // Draw
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, screenData);

        // Swap buffers
        glfwSwapBuffers(window);
    }
}

//Update engine delta time count
void PaintLike::UpdateTime()
{
    //Extract framerate
    clockOld = clockNow;
    clockNow = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed_seconds = clockNow - clockOld;
    fDeltaTime = elapsed_seconds.count();
    frameCounter++;

    if (frameCounter % 30 == 0)
    {
        std::string title = "PaintLike - FPS: " + std::to_string(1 / fDeltaTime);
        glfwSetWindowTitle(window, title.c_str());
    }
}

//Update engine input
void PaintLike::UpdateInput()
{
    //Sort input events
    glfwPollEvents();

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        currentTool->OnClick({(int)x, (int)y}, *currentCanvas);
    }
    else if (state == GLFW_RELEASE)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        currentTool->OnRelease({(int)x, (int)y}, *currentCanvas);
    }
}

//===============================================================================
// DRAWING FUNCTIONS
//===============================================================================

//Drawing the screen
void PaintLike::Draw()
{
    DrawAllCanvas();
    DrawInterface();
}

//Draw all canvases ::=> Unfinished
void PaintLike::DrawAllCanvas()
{
    for (int i = 0; i < canvas.size(); i++)
    {
        unsigned char *canvasData = canvas[i]->getCanvasData();
        for (int i = 0; i < width * height * 3; i += 3)
        {
            int tmp = i + i / 3;                               //Index correspondency between canvas data and screen data
            float opacity = canvasData[tmp + 3] * 0.00392157f; //Same as dividing between 255

            screenData[i] = canvasData[tmp] * opacity;
            screenData[i + 1] = canvasData[tmp + 1] * opacity;
            screenData[i + 2] = canvasData[tmp + 2] * opacity;
        }
    }
}

//Draws interface
void PaintLike::DrawInterface()
{
}