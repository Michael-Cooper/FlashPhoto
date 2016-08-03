/*! \TSprayCan.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "TSprayCan.h"
#include "MLinear.h"
/// A brush is designed to mimic the	look	of	paint	from a	spray	can
/// Inherited from Tool class
TSprayCan::TSprayCan()
{
	/// Initialize the mask from MLinear
	m_mask = new MLinear(30, 0.2);

}


std::string TSprayCan::getName()
{
	return "Spray Can";
}
