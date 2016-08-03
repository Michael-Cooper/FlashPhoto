
#include "FQuantize.h"
#include <iostream>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <math.h>

using std::cout;
using std::endl;

FQuantize::FQuantize() {
  strength = 0;
}

void FQuantize::applyToBuffer(PixelBuffer* buffer, float newStrength[]) {
  strength = newStrength[0];

  for (int x = 0; x < buffer->getWidth(); x++) {

    for (int y = 0; y < buffer->getHeight(); y++) {
      ColorData c = buffer->getPixel(x, y);

      float r = c.getRed();
      float g = c.getGreen();
      float b = c.getBlue();

      // set r value
      float binVal = 0;
      float binThresh = 1.0 / strength;

      for (int i = 0; i < strength; i++) {
        if (r <= binThresh) {
          c.setRed(binVal);
          break;
        }
        binVal += 1.0 / (strength - 1);
        binThresh += 1.0 / strength;
      }

      // set g value
      binVal = 0;
      binThresh = 1.0 / strength;

      for (int i = 0; i < strength; i++) {
        if (g <= binThresh) {
          c.setGreen(binVal);
          break;
        }
        binVal += 1.0 / (strength - 1);
        binThresh += 1.0 / strength;
      }

      // set b value
      binVal = 0;
      binThresh = 1.0 / strength;

      for (int i = 0; i < strength; i++) {
        if (b <= binThresh) {
          c.setBlue(binVal);
          break;
        }
        binVal += 1.0 / (strength - 1);
        binThresh += 1.0 / strength;
      }

      buffer->setPixel(x, y, c);
    }
  }
}

std::string FQuantize::getName(){
	return "Quantize";
}
