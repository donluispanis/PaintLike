#pragma once

#include "Tools.h"

class Pencil : public Tool
{
  public:
    Pencil() : Tool(Tool::Type::PENCIL)
    {
    }

    virtual ~Pencil()
    {
    }

    virtual void OnClick(const point_t p, Canvas &canvas) override;
    virtual void OnRelease(const point_t p, Canvas &canvas) override;
};
