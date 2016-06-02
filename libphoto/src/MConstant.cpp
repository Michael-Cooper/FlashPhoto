
/*! \MConstant.cpp
 * Student Support
 *
 *  Created by Seth Johnson on 2/9/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "MConstant.h"
#include <cmath>
/// This class defines the constant shape that might be used for the tools
MConstant::MConstant(float radius, float opacity) : Mask(radius, opacity)
{
	generateMask();
}
/// Do calculation to get the intensity
float MConstant::getIntensity(int x, int y, float radius)
{
	float hyp = sqrt(x*x + y*y);
	if (hyp > radius) {
		return 0.0;
	} else {
		return 1.0;
	}
}
