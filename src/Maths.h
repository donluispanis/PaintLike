#pragma once

//===============================================================================
// IN THIS FILE WE FIND MATHS RELATED DECLARATIONS AND FUNCTIONS
//===============================================================================

namespace M
{

struct point_t
{ //Point data
    int x;
    int y;
};

//Swaps the contents of each point
void swap(point_t& p1, point_t& p2);

//Approximates the sinus function
float sin(float angle);

//Approximates the cosinus function
float cos(float angle);

//Absolute value function
float abs(float value);

} // namespace M