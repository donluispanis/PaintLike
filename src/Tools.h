#pragma once

#include <string>
class Canvas;

class Tool
{

public:
  //===============================================================================
  // PUBLIC TYPES
  //===============================================================================
  enum class Type //Type of tool
  {
    PENCIL,
    PEN,
    PEN_ROUND,
    RECTANGLE,
    CIRCLE
  };

  struct color_t
  { //Color data
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
  };

  struct point_t
  { //Point data
    int x;
    int y;
  };

  //===============================================================================
  // TOOL PUBLIC FUNCTIONS
  //===============================================================================
  Tool(Tool::Type t) : type(t), isBeingUsed(false)
  {
    color = {0xFF, 0xFF, 0xFF, 0xFF};
  }

  virtual ~Tool()
  {
  }

  //Basic functions
  virtual void OnClick(const point_t p, Canvas &canvas) = 0;
  virtual void OnRelease(const point_t p, Canvas &canvas) = 0;

  //Getters
  Tool::Type getType()  { return type; }
  color_t getColor()    { return color; }
  
  bool isActive()       { return isBeingUsed; }
  point_t getOldPoint() { return oldP; }
  point_t getNewPoint() { return newP; }

  //Setters
  void setColor(color_t c)    { color = c; }

  void setActive(bool a)      { isBeingUsed = a; }
  void setOldPoint(point_t p) { oldP = p; }
  void setNewPoint(point_t p) { newP = p; }

private:
  Tool::Type type;  //Which tool we are using
  color_t color;    //Color of the tool we are using

  bool isBeingUsed;   //Is tool in use?
  point_t oldP, newP; //Current cursor point and last one
};