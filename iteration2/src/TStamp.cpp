#include "TStamp.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <stdio.h>
#include <iostream>

TStamp::TStamp()
{
}

std::string TStamp::getName()
{
	return "Stamp";
}

void TStamp::applyToBufferStamp(int x, int y, ColorData toolColor, PixelBuffer* canvas, PixelBuffer* stamp)
{
  ColorData pixelinfo;
  //Get the center
  int CenterX = stamp->getWidth()/2 ;
  int CenterY = stamp->getHeight()/2 ;
  //loop through every pixel of the image
  for (int j=0; j < stamp->getHeight(); j++){
      for (int i=0; i < stamp->getWidth(); i++){
      // Determine if it is still inside the canvas
      if ((x + i - CenterX < canvas->getWidth()) && (y + j - CenterY < canvas->getHeight())){
        pixelinfo = stamp->getPixel(i,j);
        canvas->setPixel(x + i - CenterX, y + j - CenterY ,pixelinfo);
      }
    }
  }
}
