#pragma once

#include <string>

#include "Utils.h"

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
  virtual void OnClick(const U::point_t p, Canvas &canvas) = 0;
  virtual void OnRelease(const U::point_t p, Canvas &canvas) = 0;

  //Getters
  Tool::Type getType()  { return type; }
  U::color_t getColor()    { return color; }
  
  bool isActive()       { return isBeingUsed; }
  U::point_t getOldPoint() { return oldP; }
  U::point_t getNewPoint() { return newP; }

  //Setters
  void setColor(U::color_t c)    { color = c; }

  void setActive(bool a)      { isBeingUsed = a; }
  void setOldPoint(U::point_t p) { oldP = p; }
  void setNewPoint(U::point_t p) { newP = p; }

private:
  Tool::Type type;  //Which tool we are using
  U::color_t color;    //Color of the tool we are using

  bool isBeingUsed;   //Is tool in use?
  U::point_t oldP, newP; //Current cursor point and last one
};