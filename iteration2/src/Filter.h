//
//
//  Tool is the representation of a particular PaintShop tool.
//  This baseclass is abstract and does not provide a default mask.
//  Tools inherited from this class should provide a name and a mask.
//  Inherited classes may optionally override the default colorBlendMath.


#ifndef FILTER_H
#define FILTER_H

#include <string>

class PixelBuffer;
class ColorData;
class Mask;

/// This is the superclass for Filters.
class Filter
{
public:
	Filter();
	virtual ~Filter();

	virtual void applyToBuffer(PixelBuffer* buffer, float newStrength[]);
	virtual void setDirection(int d);



	virtual std::string getName() = 0;


protected:
int maskHeight;
int maskWidth;
//int centerX;
//int centerY;
float ** mask;
float trans;

};

#endif
