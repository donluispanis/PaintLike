#include "Tools.h"
#include "Canvas.h"
#include <iostream>
#include <cmath>

void Pencil::OnClick(const point_t p, Canvas &canvas)
{
    //Lambda function for drawing pixels
    auto drawPixel = [](const point_t &p, const color_t &c, Canvas &canvas) 
    {
        int sD = ((canvas.getHeight() - p.y) * canvas.getWidth() + p.x) * 4;

        canvas.getCanvasData()[sD] = c.RGBA[0];
        canvas.getCanvasData()[sD + 1] = c.RGBA[1];
        canvas.getCanvasData()[sD + 2] = c.RGBA[2];
        canvas.getCanvasData()[sD + 3] = c.RGBA[3];
    };

    if (p.x >= 0 && p.x < canvas.getWidth() && p.y >= 0 && p.y < canvas.getHeight())
    {
        //If its the first time we press, draw points and save press points
        if (!isPressed)
        {
            drawPixel(p, getColor(), canvas);

            isPressed = true;

            oldP = p;
        }
        //If we continue pressing and move
        else if (p.x != oldP.x || p.y != oldP.y)
        {
            //Calculate the slope of the line to be drawn
            float slope = (float)(p.y - oldP.y) / (float)(p.x - oldP.x);
            float acummulated = 0.f;    //When this hits 1, we make 1 pixel increment
            point_t aux = oldP; //auxiliar point that we will increment from the old point to the new one

            //Slope < 45º
            if (std::abs(slope) <= 1.f && std::abs(slope) >= 0.f)
            {
                //While we don't reach the desired pixel position
                while (aux.x != p.x || aux.y != p.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    int signX = (p.x - aux.x) >= 0 ? 1 : -1;

                    aux.x += signX;
                    acummulated += std::abs(slope);

                    if (acummulated >= 1.f)
                    {
                        int signY = (p.y - aux.y) >= 0 ? 1 : -1;
                        aux.y += signY;
                        acummulated -= 1.f;
                    }
                }
            }
            //Slope > 45º
            else if (std::abs(slope) > 1.f)
            {
                //While we don't reach the desired pixel position
                while (aux.x != p.x || aux.y != p.y) 
                {
                    drawPixel(aux, getColor(), canvas);

                    int signY = (p.y - aux.y) >= 0 ? 1 : -1;

                    aux.y += signY;
                    acummulated += 1 / std::abs(slope);

                    if (acummulated >= 1.f)
                    {
                        int signX = (p.x - aux.x) >= 0 ? 1 : -1;
                        aux.x += signX;
                        acummulated -= 1.f;
                    }
                }
            }

            oldP = p;   //Update new point as old point
        }
    }
}

void Pencil::OnRelease(const point_t p, Canvas &canvas)
{
    isPressed = false;
}