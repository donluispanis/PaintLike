#pragma once

#include "Tools.h"

class Pencil : public Tool
{
  public:
    Pencil() : Tool(Tool::Type::PENCIL), size(20), dispersion(20)
    {
    }

    virtual ~Pencil()
    {
    }

    virtual void OnClick(const point_t p, Canvas &canvas) override;
    virtual void OnRelease(const point_t p, Canvas &canvas) override;

    unsigned int getSize() { return size; }
    unsigned char getDispersion() { return dispersion; }

  private: 
    void DrawPencil(const point_t &p, const color_t &c, Canvas &canvas);  //Draw at per pixel level
    void DrawLineBresenham(const point_t &p, Canvas &canvas); //Draw a line using Bresenham's algorithym

    unsigned int size;          //Size of the brush
    unsigned char dispersion;   //Dispersion of the brush (airbrush effect)
};
