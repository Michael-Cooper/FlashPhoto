#include "TBlur.h"
#include "ColorData.h"
#include "Mask.h"
#include "PixelBuffer.h"

TBlur::TBlur()
{

  maskHeight = 20;
  maskWidth = 20;
  mask = new float* [maskHeight];
  for (int i = 0; i < maskHeight; i++) {
    mask[i]= new float[maskWidth];
    for (int j = 0; j < maskWidth; j++) {
      mask[i][j] = 0.0025;
    }
  }
}

std::string TBlur::getName()
{
	return "Blur";
}


void TBlur::applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer)
{
  int tempX;
  int tempY;
  for (int i = 0; i < maskWidth; i++)
  {
    for (int j = 0; j < maskHeight; j++)
    {
      tempX = toolX - maskWidth/2 + i;
      tempY = toolY - maskHeight/2 + i;

      ColorData c = m_buffer->getPixel(tempX, tempY);


      for (int mw = 0; mw < maskWidth; mw++)
      {
        for (int mh = 0; mh < maskHeight; mh++)
        {
          trans = mask[mw][mh];
          //c = c + mask[mw][mh]*buffer->getPixel((w - maskWidth/2 + mw), (h - maskHeight/2 + mh));
          //c = c + trans * buffer->getPixel((w - maskWidth/2 + mw), (h - maskHeight/2 + mh));
          ColorData maskC = m_buffer->getPixel((tempX - maskWidth/2 + mw), (tempY - maskHeight/2 + mh));
          maskC = maskC * trans;
          c = c + maskC;
        }
      }
      c = c - m_buffer->getPixel(tempX, tempY);
      m_tempBuffer->setPixel(tempX, tempY, c);
    }
  }
}

void TBlur::applyToBufferMouseDown(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer)
{
  m_buffer = buffer;
  m_tempBuffer = new PixelBuffer(buffer->getWidth(), buffer->getHeight(), buffer->getBackgroundColor());
  m_tempBuffer->copyPixelBuffer(m_buffer, m_tempBuffer);

  int tempX;
  int tempY;

  for (int i = 0; i < maskWidth; i++)
  {
    for (int j = 0; j < maskHeight; j++)
    {
      tempX = toolX - maskWidth/2 + i;
      tempY = toolY - maskHeight/2 + i;

      ColorData c = m_buffer->getPixel(tempX, tempY);


      for (int mw = 0; mw < maskWidth; mw++)
      {
        for (int mh = 0; mh < maskHeight; mh++)
        {
          trans = mask[mw][mh];
          //c = c + mask[mw][mh]*buffer->getPixel((w - maskWidth/2 + mw), (h - maskHeight/2 + mh));
          //c = c + trans * buffer->getPixel((w - maskWidth/2 + mw), (h - maskHeight/2 + mh));
          ColorData maskC = m_buffer->getPixel((tempX - maskWidth/2 + mw), (tempY - maskHeight/2 + mh));
          maskC = maskC * trans;
          c = c + maskC;
        }
      }
      c = c - m_buffer->getPixel(tempX, tempY);
      m_tempBuffer->setPixel(tempX, tempY, c);
    }
  }
}

void TBlur::swap()
{

  m_buffer->copyPixelBuffer(m_tempBuffer, m_buffer);
  delete m_tempBuffer;
}
