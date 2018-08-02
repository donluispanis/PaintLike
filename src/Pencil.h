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

    virtual void OnClick(const M::point_t p, Canvas &canvas) override;
    virtual void OnRelease(const M::point_t p, Canvas &canvas) override;

    unsigned int getSize() { return size; }
    unsigned char getDispersion() { return dispersion; }

  private: 
    void DrawPencil(const M::point_t &p, const U::color_t &c, Canvas &canvas);  //Draw at per pixel level
    void DrawLineBresenham(const M::point_t &p, Canvas &canvas); //Draw a line using Bresenham's algorithym

    unsigned int size;          //Size of the brush
    unsigned char dispersion;   //Dispersion of the brush (airbrush effect)
};
