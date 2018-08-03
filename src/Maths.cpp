#include "Maths.h"

//Swaps the contents of each point
void M::swap(point_t &p1, point_t &p2)
{
    int aux;

    aux = p1.x;
    p1.x = p2.x;
    p2.x = aux;

    aux = p1.y;
    p1.y = p2.y;
    p2.y = aux;
}

//Approximates the sinus function
//The credit for this approach goes for OneLoneCoder video: https://www.youtube.com/watch?v=1xlCVBIF_ig
float M::sin(float angle)
{
    angle *= 0.159154943f; // angle * 1 / 2pi, in order to normalize it

    angle -= (int)angle; //subtract from the angle its integer part in order to clamp it

    int sign = (angle > 0) ? 1 : -1;    //calculate sign of the angle
    angle = M::abs(angle);

    if (angle < 0.5)
        return (-16.f * angle * angle + 8 * angle) * sign; // y = -16(x - 0)(x - 0.5)  ==> y = -16x^2 + 8x
    else
    {
        angle -= 0.5f;
        return (16.f * angle * angle - 8 * angle) * sign; // if the angle is bigger than 0.5, use the same equation but inverted
    }
}

//Approximates the cosinus function
float M::cos(float angle) {
    return M::sin(1.570796327f - angle); // cos = pi/2 - sin
}

//Absolute value function
float M::abs(float value) {
    return (value > 0) ? (value) : (value * -1.f);
}