//
//
//

#ifndef FQuantize_H
#define FQuantize_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;

class FQuantize : public Filter
{
public:
	FQuantize();

	std::string getName() ;


	void applyToBuffer(PixelBuffer* buffer, float newStrength[]);


private:

	float strength;


};

#endif
