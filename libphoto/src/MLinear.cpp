
/*! \MLinear.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/9/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "MLinear.h"
#include <cmath>

/// This class defines the linear shape that might be used for the tools
MLinear::MLinear(float radius, float opacity) : Mask(radius, opacity)
{
	generateMask();
}
/// Do calculation to get the intensity
float MLinear::getIntensity(int x, int y, float radius)
{
	float hyp = sqrt(x*x + y*y);

	if (hyp <= radius) {
		return 1 - hyp/radius;
	} else {
		return 0.0;

	}
}
