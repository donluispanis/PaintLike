#include "Canvas.h"
#include <cstring>

//Constructor
Canvas::Canvas(const int w, const int h)
{
    //Check size is adequate
    if (w > 0 && w < kMaxSize)
    {
        width = w;
    }
    else
    {
        width = kDefaultValue;
    }

    if (h > 0 && h < kMaxSize)
    {
        height = h;
    }
    else
    {
        height = kDefaultValue;
    }

    //Set center in the middle by default
    centerX = width >> 1;
    centerY = height >> 1;

    //Set default color valuess
    opacity = 1.f;
    hue = 0.5f;
    saturation = 0.5f;
    value = 0.5f;

    //Initilize canvas screen data
    canvasData = new unsigned char[width * height * 4];
    memset(canvasData, 0, width * height * 4);
}

Canvas::~Canvas()
{
    delete[] canvasData;
}