
/*! \MConstant.h
 * Student Support
 *
 *  Created by Seth Johnson on 2/9/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

 //!  MConstant is a Mask that is round, with a constant fill
 //!  value.
#ifndef MCONSTANT_H
#define MCONSTANT_H

#include "Mask.h"
/// Support oval constant shape
class MConstant : public Mask
{
public:
	MConstant(float radius, float opacity);
protected:
	float getIntensity(int x, int y, float radius);
};

#endif
