#include "Eraser.h"
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <iostream>

Eraser::Eraser()
{
	maskHeight = 21;
	maskWidth = 21;
	centerX = 10;
	centerY = 10;
	// initialize array with zeros
	mask = new float* [maskHeight];
	for (int i = 0; i < maskHeight; i++) {
		mask[i]= new float[maskWidth];
		for (int j = 0; j < maskWidth; j++) {
			mask[i][j] = 0;
		}
	}

	for (int k = 0; k < maskHeight; k++) {
		for (int b = 0; b < maskWidth; b++) {
			if (((pow(k-centerX, 2)) + (pow(b-centerY, 2))) <= (pow(centerX, 2))) {
			  mask[k][b] = 1;
			}
		}
	}
}

Eraser::~Eraser() {
	for (int i = 0; i < maskHeight; i++) {
		delete [] mask[i];
	}
	delete [] mask;
}

void Eraser::Apply(int x, int y, int m_height, PixelBuffer* m_displayBuffer, ColorData color)
{
	x = x - maskWidth/2;
	y = y + maskHeight/2;

	for (int i = 0; i < maskHeight; i++)
	{
		for (int j = 0; j < maskWidth; j++)
		{
			ColorData curColor = m_displayBuffer -> getBackgroundColor();
			if (mask[i][j] == 1){m_displayBuffer->setPixel(x + j, m_height - y + i, curColor);}
		}
	}
}
