#include "StampSpecial.h"
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"

StampSpecial::StampSpecial() {

	maskHeight = 81;
	maskWidth = 81;
	centerX = 41;
	centerY = 41;

	int k, b;

	// initialize array with ones
	mask = new float* [maskHeight];
	for (int i = 0; i < maskHeight; i++) {
		mask[i]= new float[maskWidth];
		for (int j = 0; j < maskWidth; j++) {
			mask[i][j] = 1;
		}
	}

	// set some places to be transparent as a feature of the stamp.
	for (k = 5; k < maskHeight/2; k = k+10)
	{
		for (b = 0; b < (maskWidth/2-k); b++)
		{
			mask[k][centerX-1+b] = 0;
			mask[k][centerX-1-b] = 0;
			mask[k+1][centerX-1+b] = 0;
			mask[k+1][centerX-1-b] = 0;
			mask[k+2][centerX-1+b] = 0;
			mask[k+2][centerX-1-b] = 0;
			mask[k+3][centerX-1+b] = 0;
			mask[k+3][centerX-1-b] = 0;
			mask[k+4][centerX-1+b] = 0;
			mask[k+4][centerX-1-b] = 0;

			mask[centerX-1+b][k] = 0;
			mask[centerX-1-b][k] = 0;
			mask[centerX-1+b][k+1] = 0;
			mask[centerX-1-b][k+1] = 0;
			mask[centerX-1+b][k+2] = 0;
			mask[centerX-1-b][k+2] = 0;
			mask[centerX-1+b][k+3] = 0;
			mask[centerX-1-b][k+3] = 0;
			mask[centerX-1+b][k+4] = 0;
			mask[centerX-1-b][k+4] = 0;
		}
	}

	for (k = maskHeight-5; k > maskHeight/2; k = k-10)
	{
		for (b = 0; b < (k - maskWidth/2); b++)
		{
			mask[k][centerX-1+b] = 0;
			mask[k][centerX-1-b] = 0;
			mask[k-1][centerX-1+b] = 0;
			mask[k-1][centerX-1-b] = 0;
			mask[k-2][centerX-1+b] = 0;
			mask[k-2][centerX-1-b] = 0;
			mask[k-3][centerX-1+b] = 0;
			mask[k-3][centerX-1-b] = 0;
			mask[k-4][centerX-1+b] = 0;
			mask[k-4][centerX-1-b] = 0;
			mask[centerX-1+b][k] = 0;
			mask[centerX-1-b][k] = 0;
			mask[centerX-1+b][k-1] = 0;
			mask[centerX-1-b][k-1] = 0;
			mask[centerX-1+b][k-2] = 0;
			mask[centerX-1-b][k-2] = 0;
			mask[centerX-1+b][k-3] = 0;
			mask[centerX-1-b][k-3] = 0;
			mask[centerX-1+b][k-4] = 0;
			mask[centerX-1-b][k-4] = 0;
		}
	}
}

StampSpecial::~StampSpecial() {
	for (int i = 0; i < maskHeight; i++) {
		delete [] mask[i];
	}
	delete [] mask;
}
