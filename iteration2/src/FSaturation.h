//
//
//

#ifndef FSaturation_H
#define FSaturation_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;

class FSaturation : public Filter
{
public:
	FSaturation();

	std::string getName() ;


	void applyToBuffer(PixelBuffer* buffer, float newStrength[]);


private:

	float strength;


};

#endif
