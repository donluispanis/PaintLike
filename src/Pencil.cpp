#include "Pencil.h"
#include "Canvas.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

void Pencil::OnClick(const U::point_t p, Canvas &canvas)
{

    if (p.x >= 0 && p.x < canvas.getWidth() && p.y >= 0 && p.y < canvas.getHeight())
    {
        //If its the first time we press, draw points and save press points
        if (!isActive())
        {
            DrawPencil(p, getColor(), canvas);

            setActive(true);

            setOldPoint(p);
            setNewPoint(p);
        }
        //If we continue pressing and move
        else if (p.x != getNewPoint().x || p.y != getNewPoint().y) //We use the new point before updating it, so it's the future old points
        {
            DrawLineBresenham(p, canvas);

            setOldPoint(getNewPoint()); //Update new point as old point
            setNewPoint(p);
        }
    }
}

void Pencil::OnRelease(const U::point_t p, Canvas &canvas)
{
    setActive(false);
}

void Pencil::DrawPencil(const U::point_t &p, const U::color_t &c, Canvas &canvas)
{
    int sD;

    auto random = [](const int dispersion) {
        return rand() % dispersion - dispersion / 2;
    };

    for (unsigned int i = 0; i < size; i++)
    {
        if (i % 2) //If i % 2 == 1, then enter
            sD = ((canvas.getHeight() - p.y - (i / 2 + i % 2) + random(dispersion)) * canvas.getWidth() + p.x + random(dispersion)) * 4;
        else
            sD = ((canvas.getHeight() - p.y + (i / 2) + random(dispersion)) * canvas.getWidth() + p.x + random(dispersion)) * 4;

        canvas.getCanvasData()[sD] = c.R;
        canvas.getCanvasData()[sD + 1] = c.G;
        canvas.getCanvasData()[sD + 2] = c.B;
        canvas.getCanvasData()[sD + 3] = c.A;
    }
}

void Pencil::DrawLineBresenham(const U::point_t &p, Canvas &canvas) {
    //Calculate the slope of the line to be drawn
            float slope = (float)(p.y - getNewPoint().y) / (float)(p.x - getNewPoint().x);
            float acummulated = 0.f;     //When this hits 1, we make 1 pixel increment
            U::point_t aux = getNewPoint(); //auxiliar point that we will increment from the old point to the new one

            int signX = (p.x - aux.x) >= 0 ? 1 : -1; //Calculate X direction
            int signY = (p.y - aux.y) >= 0 ? 1 : -1; //Calculate Y direction

            //Slope < 45º
            if (std::abs(slope) <= 1.f && std::abs(slope) >= 0.f)
            {
                //While we don't reach the desired pixel position
                while (aux.x != p.x || aux.y != p.y)
                {
                    DrawPencil(aux, getColor(), canvas);

                    if (aux.x != p.x)
                        aux.x += signX; //Increment X until it reaches the target

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
                    DrawPencil(aux, getColor(), canvas);

                    if (aux.y != p.y)
                        aux.y += signY;                 //Increment Y until it reaches the target
                    acummulated += 1 / std::abs(slope); //When this reaches 1, we increment X

                    if (acummulated >= 1.f)
                    {

                        aux.x += signX;
                        acummulated -= 1.f;
                    }
                }
            }
}