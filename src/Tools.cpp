#include "Tools.h"
#include "Canvas.h"
#include <iostream>

void Pencil::OnClick(const point_t p, Canvas &canvas)
{
    if (p.x >= 0 && p.x < canvas.getWidth() && p.y >= 0 && p.y < canvas.getHeight())
    {
        if (!isPressed)
        {
            int sD = ((canvas.getHeight() - p.y) * canvas.getWidth() + p.x) * 4;

            canvas.getCanvasData()[sD] = getColor().RGBA[0];
            canvas.getCanvasData()[sD + 1] = getColor().RGBA[1];
            canvas.getCanvasData()[sD + 2] = getColor().RGBA[2];
            canvas.getCanvasData()[sD + 3] = getColor().RGBA[3];

            isPressed = true;

            oldP = p;
        }
        else
        {
            point_t p1 = {300, 300};
            oldP = {400, 300};
            float slope = (float)(p1.y - oldP.y) / (float)(p1.x - oldP.x);
            float acummulated = 0.f;
            point_t aux = oldP;

            //Ascending slope < 45º
            if (slope <= 1.f && slope >= 0.f)
            {
                while (aux.x != p1.x || aux.y != p1.y)
                {
                    int sD = ((canvas.getHeight() - aux.y) * canvas.getWidth() + aux.x) * 4;

                    canvas.getCanvasData()[sD] = getColor().RGBA[0];
                    canvas.getCanvasData()[sD + 1] = getColor().RGBA[1];
                    canvas.getCanvasData()[sD + 2] = getColor().RGBA[2];
                    canvas.getCanvasData()[sD + 3] = getColor().RGBA[3];

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
                    int sD = ((canvas.getHeight() - aux.y) * canvas.getWidth() + aux.x) * 4;

                    canvas.getCanvasData()[sD] = getColor().RGBA[0];
                    canvas.getCanvasData()[sD + 1] = getColor().RGBA[1];
                    canvas.getCanvasData()[sD + 2] = getColor().RGBA[2];
                    canvas.getCanvasData()[sD + 3] = getColor().RGBA[3];

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
            }
            //Descending slope > 45º
            else if (slope < -1.f)
            {
            }

            oldP = p;
        }
    }
}

void Pencil::OnRelease(const point_t p, Canvas &canvas)
{
    isPressed = false;
}