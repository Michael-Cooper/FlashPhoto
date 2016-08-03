

#ifndef FMotionBlur_H
#define FMotionBlur_H

#include "Filter.h"
#include <string>

class PixelBuffer;
class ColorData;
class Mask;

class FMotionBlur : public Filter
{
public:
	FMotionBlur();

	std::string getName() ;


void applyToBuffer(PixelBuffer* buffer, float newStrength[]);
void createKernel();
void setDirection(int d);


private:

	float strength;
  int direction;


};

#endif
