#pragma once

#include <vector>
#include <utility>

//===============================================================================
// IN THIS FILE WE FIND UTLITY DEFINITIONS AND FUNCTIONS FOR THE ENGINE
//===============================================================================

class Canvas;

namespace U
{

struct color_t
{ //Color data
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

struct point_t
{ //Point data
    int x;
    int y;
};

//Draws a rectangle given some parameters
void drawRectangle(Canvas &c, point_t p1, point_t p2, const int borderSize, const int borderRadius, const color_t innerC, const color_t outerC);
//Draws a circle with antialising
void drawCircle(Canvas &c, point_t p, const int radius, const int borderSize, const color_t innerC, const color_t outerC);
//Draws only a circle outline
void drawCircleOutline(Canvas &c, point_t p, const int radius, const color_t color);
void drawShape(Canvas &c, std::vector<std::pair<point_t, point_t>> coords, const int borderSize, const color_t innerC, const color_t outerC);
void drawLine(Canvas &c, point_t p1, point_t p2, const int borderSize, const color_t color);
void drawSpline(Canvas &c, point_t p1, point_t p2, point_t p3, const int borderSize, const color_t color);
void drawGradient(Canvas &c, point_t p1, point_t p2, const point_t dirVec, const color_t innerC, const color_t outerC);

//Clamp a point between 0 and max witdh and height
void clampPoint(point_t &p, int w, int h);
//Paint the correspondent pixel with the corresponding alpha blending
void paintWithColorBlending(unsigned char *cData, const color_t c);
//Orders points in order to get left up and right down corner
void orderPoints(point_t &p1, point_t &p2);

} // namespace U
