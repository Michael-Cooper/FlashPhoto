//
//  Tool.cpp
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;


Filter::Filter()
{

}

Filter::~Filter(){
}

void Filter::setDirection(int d)
{

}


void Filter::applyToBuffer(PixelBuffer* buffer, float newStrength[])
{



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
