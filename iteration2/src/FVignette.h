//
//
//

#ifndef FVignette_H
#define FVignette_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;

class FVignette : public Filter
{
public:
	FVignette();

	std::string getName() ;


	void applyToBuffer(PixelBuffer* buffer, float newStrength[]);


private:

	float strength;


};

#endif
