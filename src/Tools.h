#pragma once

#include <string>

class Tool
{

  public:
    Tool(std::string n) : name(n)
    {
    }

    virtual ~Tool()
    {
    }

    virtual void OnClick(int x, int y) = 0;

  private:
    std::string name;
    unsigned char color[4];
};

class Pencil : public Tool
{
  public:
    Pencil(std::string n) : Tool(n)
    {
    }

    virtual ~Pencil()
    {
    }

    virtual void OnClick(int x, int y) override;
};
