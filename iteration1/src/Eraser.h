#ifndef ERASER_H
#define ERASER_H
#include "Tool.h"


class Eraser : public Tool {
  public:
    Eraser();
    ~Eraser();
      
    void Apply(int x, int y, int m_height, PixelBuffer* m_displayBuffer, ColorData color);
};

#endif