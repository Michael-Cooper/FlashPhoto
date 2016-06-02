
/*! \FilterConvolve.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef FILTERCONVOLVE_H
#define FILTERCONVOLVE_H

#include "Filter.h"

class Kernel;
/// All convoluted-based filter should inherits from here
class FilterConvolve : public Filter {
protected:
     /// Generate the buffer for your filters
    virtual ColorData generatePixel(const PixelBuffer & buffer, int x, int y) const;
    /// Convoluted-based filters can use kernel when apply to canvas
    Kernel * m_kernel;
    bool m_convolveAlpha;

public:
    FilterConvolve();
    virtual ~FilterConvolve();
};

#endif
