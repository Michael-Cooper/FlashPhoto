//
//
//

#ifndef FThreshold_H
#define FThreshold_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;
// class Mask;

class FThreshold : public Filter
{
public:
	FThreshold();

	std::string getName() ;


void applyToBuffer(PixelBuffer* buffer, float newStrength[]);


private:

	float strength;


};

#endif
