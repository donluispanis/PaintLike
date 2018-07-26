#pragma once

#include <string>
class Canvas;

class Tool
{

public:

  //===============================================================================
  // PUBLIC TYPES
  //===============================================================================
  enum class Type
  {
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

  struct point_t {
    int x;
    int y;
  };


  //===============================================================================
  // TOOL PUBLIC FUNCTIONS
  //===============================================================================
  Tool(Tool::Type t) : type(t)
  {
    color.color = 0xFFFFFFFF;
  }

  virtual ~Tool()
  {
  }

  virtual void OnClick(const point_t p, Canvas &canvas) = 0;
  virtual void OnRelease(const point_t p, Canvas &canvas) = 0;

  Tool::Type getType() { return type; }
  color_t getColor() { return color; }

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

  virtual void OnClick(const point_t p, Canvas &canvas) override;
  virtual void OnRelease(const point_t p, Canvas &canvas) override;

private:
  bool isPressed;
  point_t oldP, newP;
};
