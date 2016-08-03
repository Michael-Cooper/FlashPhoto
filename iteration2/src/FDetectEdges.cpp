#include "FDetectEdges.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>

using std::cout;
using std::endl;

FDetectEdges::FDetectEdges()
{
  maskHeight = 3;
  maskWidth = 3;

  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
    for (int j = 0; j < maskWidth; j++) {
      mask[i][j] = -1.0;
    }
  }

  mask[1][1] = 8.0;

}

std::string FDetectEdges::getName()
{
	return "DetectEdges";
}



void FDetectEdges::applyToBuffer(PixelBuffer* buffer, float newStrength[])
{

  PixelBuffer* tempB;
  tempB = new PixelBuffer(buffer->getWidth(), buffer->getHeight(), buffer->getBackgroundColor());

  for (int h = 0; h < buffer->getHeight(); h++)
  {
    for (int w = 0; w < buffer->getWidth(); w++)
    {
      ColorData c(0,0,0);


      for (int mw = 0; mw < maskWidth; mw++)
      {
        for (int mh = 0; mh < maskHeight; mh++)
        {
          trans = mask[mw][mh];
          ColorData maskC = buffer->getPixel((w - maskWidth/2 + mw), (h - maskHeight/2 + mh));
          maskC = maskC * trans;
          c = c + maskC;
        }
      }

      tempB->setPixel(w, h, c);
    }
  }

  buffer->copyPixelBuffer(tempB, buffer);
  delete tempB;
}
