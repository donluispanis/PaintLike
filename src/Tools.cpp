#include "Tools.h"
#include "Canvas.h"
#include <iostream>

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
        if (!isPressed)
        {
            drawPixel(p, getColor(), canvas);

            isPressed = true;

            oldP = p;
        }
        else if (p.x != oldP.x || p.y != oldP.y)
        {
            point_t p1 = p;
            float slope = (float)(p1.y - oldP.y) / (float)(p1.x - oldP.x);
            float acummulated = 0.f;
            point_t aux = oldP;

            //Ascending slope < 45º
            if (slope <= 1.f && slope >= 0.f)
            {
                while (aux.x != p1.x || aux.y != p1.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    int signX = (p1.x - aux.x) >= 0 ? 1 : -1;

                    aux.x += signX;
                    acummulated += slope;

                    if (acummulated >= 1.f)
                    {
                        int signY = (p1.y - aux.y) >= 0 ? 1 : -1;
                        aux.y += signY;
                        acummulated -= 1.f;
                    }
                }
            }
            //Ascending slope > 45º
            else if (slope > 1.f)
            {
                while (aux.x != p1.x || aux.y != p1.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    int signY = (p1.y - aux.y) >= 0 ? 1 : -1;

                    aux.y += signY;
                    acummulated += 1 / slope;

                    if (acummulated >= 1.f)
                    {
                        int signX = (p1.x - aux.x) >= 0 ? 1 : -1;
                        aux.x += signX;
                        acummulated -= 1.f;
                    }
                }
            }
            //Descending slope < 45º
            else if (slope >= -1.f && slope < 0.f)
            {
                while (aux.x != p1.x || aux.y != p1.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    int signX = (p1.x - aux.x) >= 0 ? 1 : -1;

                    aux.x += signX;
                    acummulated += slope;

                    if (acummulated <= -1.f)
                    {
                        int signY = (p1.y - aux.y) >= 0 ? 1 : -1;
                        aux.y += signY;
                        acummulated += 1.f;
                    }
                }
            }
            //Descending slope > 45º
            else if (slope < -1.f)
            {
                while (aux.x != p1.x || aux.y != p1.y)
                {
                    drawPixel(aux, getColor(), canvas);

                    int signY = (p1.y - aux.y) >= 0 ? 1 : -1;

                    aux.y += signY;
                    acummulated += 1 / slope;

                    if (acummulated <= -1.f)
                    {
                        int signX = (p1.x - aux.x) >= 0 ? 1 : -1;
                        aux.x += signX;
                        acummulated += 1.f;
                    }
                }
            }

            oldP = p;
        }
    }
}

void Pencil::OnRelease(const point_t p, Canvas &canvas)
{
    isPressed = false;
}