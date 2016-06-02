
/*! \TEraser.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "TEraser.h"
#include "MConstant.h"
#include "ColorData.h"
/// A brush that erases	the	digital	canvas and returns it to	its	original background	color
/// Inherited from Tool class
TEraser::TEraser()
{
/// Initialize the mask from MConstant
	m_mask = new MConstant(10.0,1.0);
}

std::string TEraser::getName()
{
	return "Eraser";
}

///  Eraser does not blend colors with the toolColor.  Here we are overriding the
///      superclass's colorBlendMath to set the canvasColor to the backgroundColor.
ColorData TEraser::colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor)
{
	return backgroundColor*mask + canvasColor*(1-mask);
}
