#include "Pen.h"
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include <iostream>

using std::cout;
using std::endl;

Pen::Pen()
{
	maskHeight = 3;
	maskWidth = 3;
	centerX = 2;
	centerY = 2;
	// initialize array with ones
	mask = new float* [maskHeight];
	for (int i = 0; i < maskHeight; i++) {
		mask[i]= new float[maskWidth];
		for (int j = 0; j < maskWidth; j++) {
			mask[i][j] = 1;
		}
	}

	// set corners to zero
	mask[0][0] = 0;
	mask[0][maskWidth - 1] = 0;
	mask[maskHeight - 1][0] = 0;
	mask[maskHeight - 1][maskWidth - 1] = 0;
}

Pen::~Pen() {
	for (int i = 0; i < maskHeight; i++) {
		delete [] mask[i];
	}
	delete [] mask;
}
