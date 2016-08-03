/*! \FMotionBlur.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FMotionBlur.h"
#include "KMotionBlur.h"
/// A filter that blur the image in a directional manner
/// Inherits from FilterConvolve
FMotionBlur::FMotionBlur(float amount, int direction) {
    m_convolveAlpha = true;
    m_kernel = new KMotionBlur(amount, direction);
}
