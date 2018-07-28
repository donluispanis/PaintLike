#pragma once

#include "Tools.h"

class Pencil : public Tool
{
  public:
    Pencil() : Tool(Tool::Type::PENCIL), size(1), dispersion(1)
    {
    }

    virtual ~Pencil()
    {
    }

    virtual void OnClick(const point_t p, Canvas &canvas) override;
    virtual void OnRelease(const point_t p, Canvas &canvas) override;

  private: 
    void DrawPencil(const point_t &p, const color_t &c, Canvas &canvas);

    unsigned int size;          //Size of the brush
    unsigned char dispersion;   //Dispersion of the brush
};
