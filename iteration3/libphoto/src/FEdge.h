/*! \FEdge.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef FEDGE_H
#define FEDGE_H

#include "FilterConvolve.h"

class Kernel;
/// A filter that create a representation of the rate-of-change in the image
class FEdge : public FilterConvolve {
public:
    FEdge();
};

#endif
