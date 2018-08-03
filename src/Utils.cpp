#include "Utils.h"
#include "Canvas.h"

#include <algorithm>
#include <cmath>

//Draws a rectangle given some parameters
void U::drawRectangle(Canvas &c, point_t p1, point_t p2, const int borderSize, const int borderRadius, const color_t innerC, const color_t outerC)
{
    //Check if both points are outside the rectangle, and if they do, exit
    if ((p1.x < 0 && p2.x < 0) || (p1.x >= c.getWidth() && p2.x >= c.getWidth()) ||
        (p1.y < 0 && p2.y < 0) || (p1.y >= c.getHeight() && p2.y >= c.getHeight()))
        return;

    //Aux height and witdh variables to make code easier and faster
    int cW = c.getWidth();
    int cH = c.getHeight();
    unsigned char *cData = c.getCanvasData();

    //Order points in order to get left up and right down corner
    orderPoints(p1, p2);

    //Calculate the absolute value the points are offscreen
    int offX1 = (p1.x >= 0) ? 0 : -p1.x;
    int offY1 = (p1.y >= 0) ? 0 : -p1.y;
    int offX2 = (p2.x < cW) ? 0 : p2.x - cW;
    int offY2 = (p2.y < cH) ? 0 : p2.y - cH;

    //If some coordinate is ouside the rectangle, clamp it
    clampPoint(p1, cW, cH);
    clampPoint(p2, cW, cH);

    //Clamp again point values taking border size in account, and invert Y
    int minX = std::max(0, p1.x - (borderSize / 2 + borderSize % 2));
    int minY = std::max(0, cH - p2.y - (borderSize / 2 + borderSize % 2));
    int maxX = std::min(cW, p2.x + (borderSize / 2 + borderSize % 2));
    int maxY = std::min(cH, cH - p1.y + (borderSize / 2 + borderSize % 2));

    //Draw rectangle
    for (int y = minY; y < maxY; y++)
    {
        for (int x = minX; x < maxX; x++)
        {
            int pos = (y * cW + x) * 4;

            //Draw border
            if (x < minX + borderSize - offX1 || y < minY + borderSize - offY2 || x > maxX - borderSize - 1 + offX2 || y > maxY - borderSize - 1 - offY1)
            {
                paintWithColorBlending(cData + pos, outerC);
            }
            //Draw insides
            else
            {
                paintWithColorBlending(cData + pos, innerC);
            }
        }
    }
}

//Draws a circle with antialising, based on https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void U::drawCircle(Canvas &c, point_t p, const int radius, const int borderSize, const color_t innerC, const color_t outerC)
{
    auto drawPixel = [](Canvas& c, const color_t color, const point_t &p) {
        int pos = ((c.getHeight() - p.y) * c.getWidth() + p.x) * 4;
        U::paintWithColorBlending(c.getCanvasData() + pos, color);
    };

    int x = radius-1-borderSize, y = 0;
    int dx = 1, dy = 1;
    int err = dx - (radius << 1);

    //lineFrom(x0 - x, y0 + y, x0 + x, y0 + y);

    while (x >= y)
    {
        drawPixel(c, outerC, {p.x + x, p.y + y});
        drawPixel(c, outerC, {p.x + y, p.y + x});
        drawPixel(c, outerC, {p.x - y, p.y + x});
        drawPixel(c, outerC, {p.x - x, p.y + y});
        drawPixel(c, outerC, {p.x - x, p.y - y});
        drawPixel(c, outerC, {p.x - y, p.y - x});
        drawPixel(c, outerC, {p.x + y, p.y - x});
        drawPixel(c, outerC, {p.x + x, p.y - y});

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void U::drawShape(Canvas &c, std::vector<std::pair<point_t, point_t>> coords, const int borderSize, const color_t innerC, const color_t outerC) {}

void U::drawLine(Canvas &c, point_t p1, point_t p2, const int borderSize, const color_t color) {}

void U::drawSpline(Canvas &c, point_t p1, point_t p2, const point_t p3, const int borderSize, const color_t color) {}

void U::drawGradient(Canvas &c, point_t p1, point_t p2, point_t dirVec, const color_t innerC, const color_t outerC) {}

//Clamp a point between 0 and max witdh and height
void U::clampPoint(point_t &p, int w, int h)
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

//Orders points in order to get left up and right down corner
void U::orderPoints(point_t &p1, point_t &p2)
{
    int aux;

    aux = std::min(p1.x, p2.x);
    p2.x = std::max(p1.x, p2.x);
    p1.x = aux;

    aux = std::min(p1.y, p2.y);
    p2.y = std::max(p1.y, p2.y);
    p1.y = aux;
}

//Paint the correspondent pixel with the corresponding alpha blending
//Formula found in https://en.wikipedia.org/wiki/Alpha_compositing
void U::paintWithColorBlending(unsigned char *cData, const color_t c)
{
    float srcAlpha = c.A * 0.00392157f;      //Same as dividing between 255
    float dstAlpha = cData[3] * 0.00392157f; //Same as dividing between 255

    float outAlpha = srcAlpha + dstAlpha * (1 - srcAlpha);

    float auxAlpha = dstAlpha * (1 - srcAlpha); //Auxn variable for efficiency

    cData[0] = (int)((c.R * srcAlpha + cData[0] * auxAlpha) / outAlpha);
    cData[1] = (int)((c.G * srcAlpha + cData[1] * auxAlpha) / outAlpha);
    cData[2] = (int)((c.B * srcAlpha + cData[2] * auxAlpha) / outAlpha);
    cData[3] = (int)(outAlpha * 255);
}
