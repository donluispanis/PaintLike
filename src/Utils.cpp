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

    int minX = std::max(0, p1.y - (borderSize / 2 + borderSize % 2));
    int minY = std::max(0, p1.y - (borderSize / 2 + borderSize % 2));
    int maxX = std::min(cW, p2.x + (borderSize / 2 + borderSize % 2));
    int maxY = std::min(cH, p2.y + (borderSize / 2 + borderSize % 2));

    //Draw border
    for (int y = minY; y < maxY; y++)
    {
        for (int x = minX; x < maxX; x++)
        {
            int pos = (y * cW + x) * 4;

            if (x < minX + borderSize || y < minY + borderSize || x > maxX - borderSize - 1 || y > maxY - borderSize - 1)
            {
                cData[pos] = outerC.R;
                cData[pos + 1] = outerC.G;
                cData[pos + 2] = outerC.B;
                cData[pos + 3] = outerC.A;
            }
            else
            {
                cData[pos] = innerC.R;
                cData[pos + 1] = innerC.G;
                cData[pos + 2] = innerC.B;
                cData[pos + 3] = innerC.A;
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
