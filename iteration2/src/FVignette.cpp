
#include "FVignette.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FVignette::FVignette() {
  strength = 0;
}

void FVignette::applyToBuffer(PixelBuffer* buffer, float newStrength[]) {
  strength = newStrength[0];

  int height = buffer->getHeight();
  int width = buffer->getWidth();
  int centerX = width / 2;
  int centerY = height / 2;
  float maxRadius = sqrt(pow((height/2),2) + pow((width/2),2));

  for (int x = 0; x < width; x++) {

    for (int y = 0; y < height; y++) {
      ColorData c = buffer->getPixel(x, y);

      float r = c.getRed();
      float g = c.getGreen();
      float b = c.getBlue();

      float res = pow((x-centerX),2) / pow((width/2),2) + pow((y-centerY),2) / pow((height/2),2);
      if (res > 1) {
        float fac = (res - 1) * .9;
        c.setRed(r - fac);
        c.setGreen(g - fac);
        c.setBlue(b - fac);
      }

      buffer->setPixel(x, y, c);
    }
  }
}

std::string FVignette::getName(){
	return "Vignette";
}
