
/*! \MOval.h
 * Student Support
 *
 *  Created by Seth Johnson on 2/9/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

 //!  MOval is a Mask in the shape of an ellipse with an orientation.
 //!  It takes an angle in degrees, and a ratio between height and width.
 //!  It is of constant fill.
#ifndef MOVAL_H
#define MOVAL_H

#include "Mask.h"
/// Support oval mask shape
class MOval : public Mask
{
public:
	/// Define the features of the oval shape
	MOval(float radius, float opacity, float angle, float ratio);
protected:
	/// Get intensity
	float getIntensity(int x, int y, float radius);
	float m_angle;
	float m_ratio;
};

#endif
