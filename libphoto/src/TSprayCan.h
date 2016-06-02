
/*! \TSprayCan.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef TSPRAYCAN_H
#define TSPRAYCAN_H

#include "Tool.h"
/// A brush is designed to mimic the	look	of	paint	from a	spray	can
class TSprayCan : public Tool
{
public:
	TSprayCan();

	std::string getName();
};

#endif
