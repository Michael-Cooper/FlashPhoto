#include "Calligraphy.h"
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"

Calligraphy::Calligraphy() {
    
    maskHeight = 15;
    maskWidth = 5;
    centerX = 3;
    centerY = 8;
	// initialize array with ones
	mask = new float* [maskHeight];
	for (int i = 0; i < maskHeight; i++) {
		mask[i]= new float[maskWidth];
		for (int j = 0; j < maskWidth; j++) {
			mask[i][j] = 1;
		}
	}
}

Calligraphy::~Calligraphy() {
	for (int i = 0; i < maskHeight; i++) {
		delete [] mask[i];
	}
	delete [] mask;
}
