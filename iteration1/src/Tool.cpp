#include "Tool.h"
#include "PixelBuffer.h"
#include "BrushWorkApp.h"
#include "ColorData.h"

#include <iostream>

using std::cout;
using std::endl;

Tool::Tool() {
}

Tool::~Tool() {
}

void Tool::Apply(int x, int y, int m_height, PixelBuffer* m_displayBuffer, ColorData color)
{
	x = x - centerX;
	y = y + centerY;
	float trans;
	for (int i = 0; i < maskHeight; i++)
	{
		for (int j = 0; j < maskWidth; j++)
		{
      	                trans = mask[i][j];
			ColorData curColor = m_displayBuffer->getPixel(x + j, m_height - y + i);
			if (mask[i][j] < 1 && mask[i][j] > 0){
				trans = curColor.getLuminance() * mask[i][j];
				//std::cout << "High " << trans << std::endl;  //fot test only
                                //std::cout << "High2 " << mask[i][j] << std::endl;  //fot test only
			}
			m_displayBuffer->setPixel(x + j, m_height - y + i, color * trans + curColor * (1 - trans));
		}
	}
}
