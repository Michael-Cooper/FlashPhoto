
#include "FChannels.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FChannels::FChannels() {
  r_strength = 0;
  g_strength = 0;
  b_strength = 0;
}

void FChannels::applyToBuffer(PixelBuffer* buffer, float newStrength[]) {
  // if (newStrength.size() != 2) {
  //   fprintf(stderr, "FChannels::applyToBuffer requires 3 arguments");
  //   return;
  // }
  r_strength = newStrength[0];
  g_strength = newStrength[1];
  b_strength = newStrength[2];

  for (int x = 0; x < buffer->getWidth(); x++) {

    for (int y = 0; y < buffer->getHeight(); y++) {
      ColorData c = buffer->getPixel(x, y);

      c.setRed(c.getRed() * r_strength);
      c.setGreen(c.getGreen() * g_strength);
      c.setBlue(c.getBlue() * b_strength);

      buffer->setPixel(x, y, c);
    }
  }
}

std::string FChannels::getName(){
	return "Channels";
}
