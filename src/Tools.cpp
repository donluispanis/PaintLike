#include "Tools.h"
#include "Canvas.h"
#include <iostream>

void Pencil::OnClick(int x, int y, Canvas &canvas)
{
    if (x >= 0 && x < canvas.getWidth() && y >= 0 && y < canvas.getHeight())
    {
        int sD = ((canvas.getHeight() - y) * canvas.getWidth() + x) * 4;

        canvas.getCanvasData()[sD] = getColor().RGBA[0];
        canvas.getCanvasData()[sD + 1] = getColor().RGBA[1];
        canvas.getCanvasData()[sD + 2] = getColor().RGBA[2];
        canvas.getCanvasData()[sD + 3] = getColor().RGBA[3];

        isPressed = true;
    }
}

void Pencil::OnRelease(int x, int y, Canvas &canvas)
{
    isPressed = false;
}