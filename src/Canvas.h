#pragma once

class Canvas
{

  public:
    //Constructor and destructor
    Canvas(const int w, const int h);
    ~Canvas();

    //Public getters
    int getWidth() { return width; }
    int getHeight() { return height; }
    unsigned char *getCanvasData() { return canvasData; }

  private:
    //Defines
    static const int kMaxSize = 5000;
    static const int kDefaultValue = 500;

    //Position variables
    int width;
    int height;
    int centerX;
    int centerY;

    //Color variables
    float opacity;
    float hue;
    float saturation;
    float value;

    //Rendering variables
    float zoom;
    int offsetX;
    int offsetY;

    //Screen info
    unsigned char *canvasData;
};