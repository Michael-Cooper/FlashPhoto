
/*! \TCalligraphyPen.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "TCalligraphyPen.h"
#include "MOval.h"
/// A brush that work as a calligraphy pen.
/// Inherited from Tool class
TCalligraphyPen::TCalligraphyPen()
{
	/// Initialize the mask from MOval
	m_mask = new MOval(7.0, 1.0, 70.0, 0.333);
}

std::string TCalligraphyPen::getName()
{
	return "Caligraphy Pen";
}
