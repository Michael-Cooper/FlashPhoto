
#include "FMotionBlur.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FMotionBlur::FMotionBlur()
{


}


void FMotionBlur::setDirection(int d)
{
  direction = d;
}





void FMotionBlur::createKernel()
{
  if (int(strength) % 2 == 0)
    strength += 1;
  maskHeight = (int) strength;
  maskWidth = (int) strength;



  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
  }


  if (direction == 0)
  {
    for (int i = 0; i < maskHeight; i++)
    {
      mask[i][maskHeight/2] = 1 / floor(strength);
    }
  }


  else if (direction == 1)
  {
    for (int i = 0; i < maskWidth; i++)
    {
      mask[maskWidth/2][i] = 1 / floor(strength);
    }
  }



  else if (direction == 2)
  {
    for (int i = 0; i < maskWidth; i++)
    {
      mask[maskWidth - 1 - i][i] = 1 / floor(strength);
    }
  }


  else if (direction == 3)
  {
    for (int i = 0; i < maskWidth; i++)
    {
      mask[i][i] = 1 / floor(strength);
    }
  }


}


void FMotionBlur::applyToBuffer(PixelBuffer* buffer, float newStrength[])
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


      if (direction == 0)
      {
        for (int i = 0; i < maskHeight; i++)
        {

          trans = mask[i][maskHeight/2];
          ColorData maskC = buffer->getPixel(w, (h - maskHeight/2 + i));
          maskC = maskC * trans;
          c = c + maskC;
        }
      }

      else if (direction == 1)
      {
        for (int i = 0; i < maskHeight; i++)
        {

          trans = mask[maskHeight/2][i];
          ColorData maskC = buffer->getPixel((w - maskWidth/2 + i), h);
          maskC = maskC * trans;
          c = c + maskC;
        }
      }


      else if (direction == 2)
      {
        for (int i = 0; i < maskHeight; i++)
        {
          trans = mask[maskWidth - 1 - i][i];
          ColorData maskC = buffer->getPixel((w + maskWidth/2 - i), h + maskHeight/2 - i);
          maskC = maskC * trans;
          c = c + maskC;
        }
      }


      else if (direction == 3)
      {
        for (int i = 0; i < maskHeight; i++)
        {
          trans = mask[i][i];
          ColorData maskC = buffer->getPixel((w - maskWidth/2 + i), h + maskHeight/2 - i);
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




std::string FMotionBlur::getName()
{
	return "MotionBlur";
}
