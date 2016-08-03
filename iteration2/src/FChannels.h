//
//
//

#ifndef FChannels_H
#define FChannels_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;

class FChannels : public Filter
{
public:
	FChannels();

	std::string getName() ;

	void applyToBuffer(PixelBuffer* buffer, float newStrength[]);


private:

	float r_strength;
	float g_strength;
	float b_strength;


};

#endif
