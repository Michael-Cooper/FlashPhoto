#ifndef TSTAMP_H
#define TSTAMP_H

#include "Tool.h"

class TStamp : public Tool
{
public:
	TStamp();

	std::string getName();
	void applyToBufferStamp(int x, int y, ColorData toolColor, PixelBuffer* canvas, PixelBuffer* stamp);

};

#endif
