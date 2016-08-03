
/*! \Mask.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/9/15..
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 */

 //!  Mask is a wrapper for the array of floats representing the shape of
 //!  a tool. It is pure virtual, because a mask does not inherently have
 //!  a shape. Shapes are defined implicitly with getIntensity().
 //!
 //!  For educational purposes only.  Please do not post online.
#ifndef MASK_H
#define MASK_H

#include "FloatMatrix.h"
/// All tools need to declare their mask to identify their shapes
class Mask : public FloatMatrix
{
public:
	/// Basic mask, override if needed
	Mask(float radius, float opacity);
    Mask(int width, int height, float opacity);

	Mask();
	~Mask();
protected:
	float m_radius;
	float m_opacity;
	/// Generate the mask for the tool
	void generateMask();
	/// Get intensity for each tool
	virtual float getIntensity(int x, int y, float radius);
};

#endif
