#include "Pencil.h"
#include "Canvas.h"
#include <iostream>
#include <cmath>

void Pencil::OnClick(const point_t p, Canvas &canvas)
{
    //Lambda function for drawing pixels
    auto drawPixel = [](const point_t &p, const color_t &c, Canvas &canvas) {
        int sD = ((canvas.getHeight() - p.y) * canvas.getWidth() + p.x) * 4;

        canvas.getCanvasData()[sD] = c.R;
        canvas.getCanvasData()[sD + 1] = c.G;
        canvas.getCanvasData()[sD + 2] = c.B;
        canvas.getCanvasData()[sD + 3] = c.A;
    };

    if (p.x >= 0 && p.x < canvas.getWidth() && p.y >= 0 && p.y < canvas.getHeight())
    {
        //If its the first time we press, draw points and save press points
        if (!isActive())
        {
            drawPixel(p, getColor(), canvas);

            setActive(true);

            setOldPoint(p);
            setNewPoint(p);
        }
        //If we continue pressing and move
        else if (p.x != getNewPoint().x || p.y != getNewPoint().y)  //We use the new point before updating it, so it's the future old points
        {
            //Calculate the slope of the line to be drawn
            float slope = (float)(p.y - getNewPoint().y) / (float)(p.x - getNewPoint().x);
            float acummulated = 0.f; //When this hits 1, we make 1 pixel increment
            point_t aux = getNewPoint();      //auxiliar point that we will increment from the old point to the new one

            
            int signX = (p.x - aux.x) >= 0 ? 1 : -1; //Calculate X direction
            int signY = (p.y - aux.y) >= 0 ? 1 : -1; //Calculate Y direction

            //Slope < 45º
            if (std::abs(slope) <= 1.f && std::abs(slope) >= 0.f)
            {
                //While we don't reach the desired pixel position
                while (aux.x != p.x || aux.y != p.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    if(aux.x != p.x)
                        aux.x += signX;                 //Increment X until it reaches the target

                    acummulated += std::abs(slope); //When this reaches 1, we increment Y

                    if (acummulated >= 1.f)
                    {
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

                    if(aux.y != p.y)
                        aux.y += signY;                     //Increment Y until it reaches the target
                    acummulated += 1 / std::abs(slope); //When this reaches 1, we increment X

                    if (acummulated >= 1.f)
                    {
                        
                        aux.x += signX;
                        acummulated -= 1.f;
                    }
                }
            }

            setOldPoint(getNewPoint()); //Update new point as old point
            setNewPoint(p);
        }
    }
}

void Pencil::OnRelease(const point_t p, Canvas &canvas)
{
    setActive(false);
}