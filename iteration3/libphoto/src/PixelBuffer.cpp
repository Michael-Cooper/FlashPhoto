
/*! \PixelBuffer.cpp
 * PhotoShop Proj
 *
 *  Created by CSCI3081W Guru
 *  Copyright (c) CSCI3081W Guru. All rights reserved.
 *
 */
#include <iostream>
#include <cstring>
#include "PixelBuffer.h"
#include "ColorData.h"

using std::cerr;
using std::endl;
using std::fill;
/// By calling certain functions of this tools, you can get the width, height, ColorData information,etc of the
/// current canvas
PixelBuffer::PixelBuffer(int w, int h, ColorData backgroundColor) : m_width(w), m_height(h)
{
	m_backgroundColor = new ColorData(backgroundColor);

	m_pixels = new ColorData[w*h];
	fillPixelBufferWithColor(backgroundColor);
}
PixelBuffer::~PixelBuffer() {
	delete[] m_pixels;
	delete m_backgroundColor;
}
ColorData PixelBuffer::getPixel(int x, int y) const
{
	ColorData pixelData;

	if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height))
	{
		cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
	}
	else
	{
		int index = x + m_width*(y);
		pixelData = m_pixels[index];
	}
	return pixelData;
}

void PixelBuffer::setPixel(int x, int y, const ColorData& newPixel)
{
	if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height))
	{
		cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
	}
	else
	{
		int index = x + m_width*(y);
		m_pixels[index] = newPixel;
	}
}

ColorData const * const PixelBuffer::getData() const
{
	return m_pixels;
}

int PixelBuffer::getHeight() const
{
	return m_height;
}

int PixelBuffer::getWidth() const
{
	return m_width;
}
ColorData PixelBuffer::getBackground() const
{
    return *m_backgroundColor;
}
void PixelBuffer::fillPixelBufferWithColor(ColorData initialPixels)
{
	fill(m_pixels, m_pixels+m_width*m_height, initialPixels);  // sets m_buffer's pixels to initialPixels
}

void PixelBuffer::copyPixelBuffer(const PixelBuffer * sourceBuffer, PixelBuffer * destinationBuffer)
{
	if (destinationBuffer->getWidth() != sourceBuffer->getWidth()
		|| destinationBuffer->getHeight() != sourceBuffer->getHeight())
	{
		cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;

	}
	else
	{
		memcpy ( (void*)destinationBuffer->m_pixels, (void*) sourceBuffer->m_pixels, sizeof(ColorData)*destinationBuffer->m_height*destinationBuffer->m_width );

	}

}


PixelBuffer* PixelBuffer::duplicatePixelBuffer(const PixelBuffer* sourceBuffer)
{
    PixelBuffer* d = new PixelBuffer(sourceBuffer->getWidth(), sourceBuffer->getHeight(), sourceBuffer->getBackground());
    PixelBuffer::copyPixelBuffer(sourceBuffer, d);
    return d;
}
