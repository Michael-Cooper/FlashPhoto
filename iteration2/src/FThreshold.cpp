
#include "FThreshold.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FThreshold::FThreshold() {
  strength = 0;
}

void FThreshold::applyToBuffer(PixelBuffer* buffer, float newStrength[]) {
  strength = newStrength[0];

  for (int x = 0; x < buffer->getWidth(); x++) {

    for (int y = 0; y < buffer->getHeight(); y++) {
      ColorData c = buffer->getPixel(x, y);

      (c.getRed() >= strength) ? c.setRed(1.0) : c.setRed(0.0);
      (c.getGreen() >= strength) ? c.setGreen(1.0) : c.setGreen(0.0);
      (c.getBlue() >= strength) ? c.setBlue(1.0) : c.setBlue(0.0);

      buffer->setPixel(x, y, c);
    }
  }
}

std::string FThreshold::getName(){
	return "Threshold";
}
