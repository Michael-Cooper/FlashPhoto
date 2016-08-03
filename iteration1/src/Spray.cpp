#include "Spray.h"
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <iostream>

Spray::Spray()
{
	maskHeight = 41;
	maskWidth = 41;
	centerX = 21;
	centerY = 21;
	influence = .2;

	// initialize array with zeros
	mask = new float* [maskHeight];
	for (int i = 0; i < maskHeight; i++) {
		mask[i]= new float[maskWidth];
		for (int j = 0; j < maskWidth; j++) {
			mask[i][j] = 0;
		}
	}

	//calculating mask influence.  Each mask[k][b] value will end up representing the percentage (from 0 to 1) of the currently
  //selected color to apply to the canvas.
	for (int k = 0; k < maskHeight; k++)
	{
		for (int b = 0; b < maskWidth; b++)
		{
			mask[k][b] = (sqrt(pow((k - centerX), 2) + pow((b - centerY), 2))) / 100;
			influence = .2;
			if (influence - mask[k][b] < 0) {mask[k][b] = 0;}
			else mask[k][b] = influence - mask[k][b];
		}
	}
}

Spray::~Spray() {
	for (int i = 0; i < maskHeight; i++) {
		delete [] mask[i];
	}
	delete [] mask;
}
