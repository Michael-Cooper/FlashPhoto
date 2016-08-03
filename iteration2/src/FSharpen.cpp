#include "FSharpen.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>

using std::cout;
using std::endl;

FSharpen::FSharpen()
{
  maskHeight = 5;
  maskWidth = 5;

  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
    for (int j = 0; j < maskWidth; j++) {
      mask[i][j] = -1;
    }
  }

  mask[2][2] = 8;

  mask[1][1] = 2;
  mask[1][2] = 2;
  mask[1][3] = 2;
  mask[2][1] = 2;
  mask[2][3] = 2;
  mask[3][1] = 2;
  mask[3][2] = 2;
  mask[3][3] = 2;


}



void FSharpen::applyToBuffer(PixelBuffer* buffer, float newStrength[])
{
  int numTimes = newStrength[0] / 20;
  numTimes += 1;



  for (int a = 0; a < numTimes; a++)
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
            maskC = maskC * trans * (1.0/8.0);
            c = c + maskC;


          }
        }
        tempB->setPixel(w, h, c);
      }
    }

    buffer->copyPixelBuffer(tempB, buffer);
    delete tempB;
  }

}



std::string FSharpen::getName()
{
	return "Sharpen";
}
