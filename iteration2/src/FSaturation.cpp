
#include "FSaturation.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FSaturation::FSaturation() {
  strength = 0;
}

void FSaturation::applyToBuffer(PixelBuffer* buffer, float newStrength[]) {
  strength = newStrength[0];

  for (int x = 0; x < buffer->getWidth(); x++) {

    for (int y = 0; y < buffer->getHeight(); y++) {
      ColorData c = buffer->getPixel(x, y);

      float r = c.getRed();
      float g = c.getGreen();
      float b = c.getBlue();
      float l = c.getLuminance();

      c.setRed(r - (strength - 1) * (l - r));
      c.setGreen(g - (strength - 1) * (l - g));
      c.setBlue(b - (strength - 1) * (l - b));

      buffer->setPixel(x, y, c);
    }
  }
}

std::string FSaturation::getName(){
	return "Saturation";
}
