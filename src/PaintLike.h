#pragma once

#include <chrono>
class GLFWwindow;

class PaintLike {

    public:

        //Void Constructor and Destructor
        PaintLike() {}
        ~PaintLike();

        //Basic functions
        bool Init(int w, int h);

        void Run();


    private: 

        void Draw();

        int height;
        int width;
        GLFWwindow *window;
        unsigned char *screenData;

        std::chrono::system_clock::time_point clockOld;
        std::chrono::system_clock::time_point clockNow;
        float fDeltaTime;

};