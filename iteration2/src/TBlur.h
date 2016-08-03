#ifndef TBLUR_H
#define TBLUR_H

#include "Tool.h"

class TBlur : public Tool
{
public:
	TBlur();


  void swap();
	std::string getName();
	void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);
	void applyToBufferMouseDown(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);

private:

	PixelBuffer* m_buffer;
  PixelBuffer* m_tempBuffer;
	float ** mask;
	int maskHeight;
	int maskWidth;
	float trans;

};

#endif
