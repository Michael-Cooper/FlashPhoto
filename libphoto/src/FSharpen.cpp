/*! \FSharpen.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "FSharpen.h"
#include "KSharpen.h"
/// A filter that sharpen the image proportional to certain amount
/// Inherits from FilterConvolve
FSharpen::FSharpen(float amount) {
  /// m_convolveAlpha is true for sharpen
    m_convolveAlpha = true;
    /// Need use kernel for help
    m_kernel = new KSharpen(amount);
}
