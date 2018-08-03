#pragma once

#include "Maths.h"
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

void drawRectangle(Canvas& c, M::point_t p1, M::point_t p2, const int borderSize, const int borderRadius, const color_t innerC, const color_t outerC);
void drawCircle(Canvas& c, M::point_t p1, const int radius, const int borderSize, const color_t innerC, const color_t outerC);
void drawShape(Canvas& c, std::vector<std::pair<M::point_t, M::point_t>> coords, const int borderSize, const color_t innerC, const color_t outerC);
void drawLine(Canvas& c, M::point_t p1, M::point_t p2, const int borderSize, const color_t color);
void drawSpline(Canvas& c, M::point_t p1, M::point_t p2, M::point_t p3, const int borderSize, const color_t color);
void drawGradient(Canvas& c, M::point_t p1, M::point_t p2, const M::point_t dirVec, const color_t innerC, const color_t outerC);

void clampPoint(M::point_t& p, int w, int h);
void paintWithColorBlending(unsigned char* cData, const color_t c);

} // namespace U
