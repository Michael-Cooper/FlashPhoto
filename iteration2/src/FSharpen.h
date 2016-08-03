#ifndef FSharpen_H
#define FSharpen_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;
class Mask;

class FSharpen : public Filter
{
public:
	FSharpen();

	std::string getName() ;


void applyToBuffer(PixelBuffer* buffer, float newStrength[]);
};

#endif
