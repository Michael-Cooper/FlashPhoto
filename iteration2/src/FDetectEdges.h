#ifndef FDetectEdges_H
#define FDetectEdges_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;
class Mask;

class FDetectEdges : public Filter
{
public:
	FDetectEdges();

	std::string getName() ;

	void applyToBuffer(PixelBuffer* buffer, float newStrength[]);
};

#endif
