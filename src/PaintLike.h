#pragma once

#include <chrono>
#include <vector>

class Tool;
class Canvas;
class GLFWwindow;

class PaintLike {

    public:

        //Void Constructor and Destructor
        PaintLike() {}
        ~PaintLike();

        //Basic functions
        bool Init(const int w, const int h);

        void Run();


    private: 
        
        //===============================================================================
        // PRIVATE FUNCTIONS
        //===============================================================================
        void Draw();    //Default draw
        void DrawAllCanvas(); //Draws all the canvases onto the screen
        void DrawTopCanvas(); //Redraws top canvas
        void DrawPartialCanvas(); //Redraws canvas partially
        void DrawInterface();   //Draws interface    

        bool InitWindow(const int w, const int h);  //Init window and openGL related stuff
        bool InitEngine(const int w, const int h);  //Init all paint related stuff

        void UpdateTime(); //Update engine delta time count
        void UpdateInput(); //Update engine input

        //===============================================================================
        // WINDOW RELATED VARIABLES
        //===============================================================================

        int height;
        int width;
        GLFWwindow *window;
        unsigned char *screenData;

        //===============================================================================
        // TIME RELATED VARIABLES
        //===============================================================================

        std::chrono::system_clock::time_point clockOld;
        std::chrono::system_clock::time_point clockNow;
        float fDeltaTime;

        unsigned char frameCounter;

        //===============================================================================
        // ENGINE RELATED VARIABLES
        //===============================================================================

        std::vector<Tool*> tools;
        std::vector<Canvas*> canvas;

        Tool* currentTool;
        Canvas* currentCanvas;

        float zoom;

};