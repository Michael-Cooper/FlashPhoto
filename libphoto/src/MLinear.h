
/*! \MLinear.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/9/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

 //!  MLinear is a Mask that is round, with a linear fall-off
 //!  from full intensity at the center to no intensity at the
 //!  extremity.
#ifndef MLINEAR_H
#define MLINEAR_H

#include "Mask.h"
/// Support linear mask shape
class MLinear : public Mask
{
public:
	/// Define the radius and opacity for your tool
	MLinear(float radius, float opacity);
protected:
	float getIntensity(int x, int y, float radius);
};

#endif
