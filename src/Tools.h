#pragma once

#include <string>

#include "Utils.h"
#include "Maths.h"

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
  virtual void OnClick(const M::point_t p, Canvas &canvas) = 0;
  virtual void OnRelease(const M::point_t p, Canvas &canvas) = 0;

  //Getters
  Tool::Type getType()  { return type; }
  U::color_t getColor()    { return color; }
  
  bool isActive()       { return isBeingUsed; }
  M::point_t getOldPoint() { return oldP; }
  M::point_t getNewPoint() { return newP; }

  //Setters
  void setColor(U::color_t c)    { color = c; }

  void setActive(bool a)      { isBeingUsed = a; }
  void setOldPoint(M::point_t p) { oldP = p; }
  void setNewPoint(M::point_t p) { newP = p; }

private:
  Tool::Type type;  //Which tool we are using
  U::color_t color;    //Color of the tool we are using

  bool isBeingUsed;   //Is tool in use?
  M::point_t oldP, newP; //Current cursor point and last one
};