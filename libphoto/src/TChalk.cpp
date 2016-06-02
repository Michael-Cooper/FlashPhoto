
/*! \TChalk.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/26/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

 //!  This tool simulates the usage of Chalk.
 //!
 //!  It has an MLinear mask with a radius of 5.0 (diameter of 11), an opacity of 1.0
 //!  (completely opaque).  colorBlendMath is overriden to randomly change the tool's
 //!  intensity at a pixel
#include "TChalk.h"
#include "MLinear.h"
#include "ColorData.h"
#include <cmath>
#include <cstdlib>

/// A brush that work as a chalk.
/// Inherited from Tool class
TChalk::TChalk()
{
	/// Initialize the mask using Mlinear
	m_mask = new MLinear(5.0, 1.0);
    m_maxSmear = 1;
}

std::string TChalk::getName()
{
	return "Chalk";
}

///  A random number between 0.0 and 1.0 is multiplied by a brightened_mask to
///  vary the intensity used in the blending math
ColorData TChalk::colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor)
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float brightened_mask = (mask/2+0.5);
	float intensity = round(brightened_mask*r);
	return toolColor*intensity + canvasColor*(1.0-intensity);
}
