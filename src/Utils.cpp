#include "Utils.h"
#include "Canvas.h"

#include <algorithm>

//Draws a rectangle given some parameters
void U::drawRectangle(Canvas &c, M::point_t p1, M::point_t p2, const int borderSize, const int borderRadius, const color_t innerC, const color_t outerC)
{
    //Check if both points are outside the rectangle, and if they do, exit
    if ((p1.x < 0 && p2.x < 0) || (p1.x >= c.getWidth() && p2.x >= c.getWidth()) ||
        (p1.y < 0 && p2.y < 0) || (p1.y >= c.getHeight() && p2.y >= c.getHeight()))
        return;

    //Aux height and witdh variables to make code easier and faster
    int cW = c.getWidth();
    int cH = c.getHeight();
    unsigned char *cData = c.getCanvasData();

    //If some coordinate is ouside the rectangle, clamp it
    clampPoint(p1, cW, cH);
    clampPoint(p2, cW, cH);

    //Order points in order to get left up and right down corner
    M::point_t minP, maxP;
    minP.x = std::min(p1.x, p2.x);
    minP.y = std::min(p1.y, p2.y);
    maxP.x = std::max(p1.x, p2.x);
    maxP.y = std::max(p1.y, p2.y);

    //Clamp again point values taking border size in account, and invert Y
    int minX = std::max(0, minP.x - (borderSize / 2 + borderSize % 2));
    int minY = std::max(0, cH - maxP.y - (borderSize / 2 + borderSize % 2));
    int maxX = std::min(cW, maxP.x + (borderSize / 2 + borderSize % 2));
    int maxY = std::min(cH, cH - minP.y + (borderSize / 2 + borderSize % 2));

    //Draw rectangle
    for (int y = minY; y < maxY; y++)
    {
        for (int x = minX; x < maxX; x++)
        {
            int pos = (y * cW + x) * 4;

            //Draw border
            if (x < minX + borderSize || y < minY + borderSize || x > maxX - borderSize - 1 || y > maxY - borderSize - 1)
            {
                float opacity = cData[pos + 3] * 0.00392157f; //Same as dividing between 255

                cData[pos] = std::min(255, (int)(outerC.R + cData[pos] * opacity));
                cData[pos + 1] = std::min(255, (int)(outerC.G + cData[pos + 1] * opacity));
                cData[pos + 2] = std::min(255, (int)(outerC.B + cData[pos + 2] * opacity));
                cData[pos + 3] = std::min(255, outerC.A + cData[pos + 3]);
            }
            //Draw insides
            else
            {
                float opacity = cData[pos + 3] * 0.00392157f; //Same as dividing between 255
                
                cData[pos] = std::min(255, (int)(innerC.R + cData[pos] * opacity));
                cData[pos + 1] = std::min(255, (int)(innerC.G + cData[pos + 1] * opacity));
                cData[pos + 2] = std::min(255, (int)(innerC.B + cData[pos + 2] * opacity));
                cData[pos + 3] = std::min(255, innerC.A + cData[pos + 3]);
            }
        }
    }
}

void U::drawCircle(Canvas &c, M::point_t p1, const int radius, const int borderSize, const color_t innerC, const color_t outerC) {}

void U::drawShape(Canvas &c, std::vector<std::pair<M::point_t, M::point_t>> coords, const int borderSize, const color_t innerC, const color_t outerC) {}

void U::drawLine(Canvas &c, M::point_t p1, M::point_t p2, const int borderSize, const color_t color) {}

void U::drawSpline(Canvas &c, M::point_t p1, M::point_t p2, const M::point_t p3, const int borderSize, const color_t color) {}

void U::drawGradient(Canvas &c, M::point_t p1, M::point_t p2, M::point_t dirVec, const color_t innerC, const color_t outerC) {}

//Clamp a point between 0 and max witdh and height
void U::clampPoint(M::point_t &p, int w, int h)
{
    if (p.x < 0)
        p.x = 0;
    if (p.y < 0)
        p.y = 0;
    if (p.x >= w)
        p.x = w - 1;
    if (p.y >= h)
        p.y = h - 1;
}
