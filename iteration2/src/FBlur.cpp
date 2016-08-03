
#include "FBlur.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FBlur::FBlur()
{
  strength = 0;

  maskHeight = strength;
  maskWidth = strength;

  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
    for (int j = 0; j < maskWidth; j++) {
      mask[i][j] = 0.04;
    }
  }
}


void FBlur::createKernel()
{
  if (int(strength) % 2 == 0)
    strength += 1;
  maskHeight = (int) strength;
  maskWidth = (int) strength;


  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
    for (int j = 0; j < maskWidth; j++) {
      mask[i][j] = 1 / (floor(strength) * floor(strength));
    }
  }
}



void FBlur::applyToBuffer(PixelBuffer* buffer, float newStrength[])
{
  strength = newStrength[0];
  createKernel();

  PixelBuffer* tempB;
  tempB = new PixelBuffer(buffer->getWidth(), buffer->getHeight(), buffer->getBackgroundColor());

  for (int h = 0; h < buffer->getHeight(); h++)
  {
    for (int w = 0; w < buffer->getWidth(); w++)
    {
      ColorData c = buffer->getPixel(w, h);


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

      c = c - buffer->getPixel(w, h);
      tempB->setPixel(w, h, c);
    }
  }

  buffer->copyPixelBuffer(tempB, buffer);
  delete tempB;
}


std::string FBlur::getName()
{
	return "Blur";
}
