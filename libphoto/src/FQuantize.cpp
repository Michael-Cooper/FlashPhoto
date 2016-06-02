/*! \FQuantize.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FQuantize.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
/// A filter that reduce the number of possible colors  by binning each color value into the the
///number of bins specified.
/// Inherits from Filter
ColorData FQuantize::generatePixel(const PixelBuffer &buffer, int x, int y) const {
    ColorData c = buffer.getPixel(x, y);
    float red = c.getRed();
    float blue = c.getBlue();
    float green = c.getGreen();
    int steps = m_bins-1;
    red = round(red*steps)/steps;
    green = round(green*steps)/steps;
    blue = round(blue*steps)/steps;
    ColorData output(red, green, blue);

    return output;
}
