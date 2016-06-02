
/*! \FEdge.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FEdge.h"
#include "KEdge.h"
/// A filter that create a representation of the rate-of-change in the image
/// inherits from FilterConvolve
FEdge::FEdge() {
    m_kernel = new KEdge();
}
