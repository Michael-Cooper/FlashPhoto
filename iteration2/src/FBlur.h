//
//
//

#ifndef FBlur_H
#define FBlur_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;
class Mask;

class FBlur : public Filter
{
public:
	FBlur();

	std::string getName() ;


void applyToBuffer(PixelBuffer* buffer, float newStrength[]);
void createKernel();


private:

	float strength;


};

#endif
