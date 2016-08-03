
/*! \FBlur.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FBlur.h"
#include "KGaussian.h"
/// A filter that blur the image proportional to certain amount
/// Inherits from FilterConvolve
FBlur::FBlur(float amount) {
    m_convolveAlpha = true;
    m_kernel = new KGaussian(amount);
}
