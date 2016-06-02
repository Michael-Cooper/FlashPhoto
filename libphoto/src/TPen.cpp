
/*! \TPen.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "TPen.h"
#include "MConstant.h"
/// A brush that work as a pen.
/// Inherited from Tool class
TPen::TPen()
{
	 /// Initialize the mask from MConstant
	m_mask = new MConstant(1.0, 1.0);
}

std::string TPen::getName()
{
	return "Pen";
}
