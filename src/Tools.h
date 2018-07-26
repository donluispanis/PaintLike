#pragma once

#include <string>
class Canvas;

class Tool
{

  public:

    enum class Type {
      PENCIL,
      PEN,
      PEN_ROUND,
      RECTANGLE,
      CIRCLE
    };

    union color_t {
      uint32_t color;
      unsigned char RGBA[4];
    };

    Tool(Tool::Type t) : type(t)
    {
      color.color = 0xFFFFFFFF;
    }

    virtual ~Tool()
    {
    }

    virtual void OnClick(int x, int y, Canvas& canvas) = 0;
    virtual void OnRelease(int x, int y, Canvas& canvas) = 0;

    Tool::Type getType() {  return type;  }
    color_t    getColor(){  return color; }

  private:
    Tool::Type type;
    color_t color;
};

class Pencil : public Tool
{
  public:
    Pencil() : Tool(Tool::Type::PENCIL), isPressed(false)
    {
    }

    virtual ~Pencil()
    {
    }

    virtual void OnClick(int x, int y, Canvas& canvas) override;
    virtual void OnRelease(int x, int y, Canvas& canvas) override;

  private: 
    bool isPressed;
};
