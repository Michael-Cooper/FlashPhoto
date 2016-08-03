/*! \FTheshold.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "FThreshold.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "Helpers.h"
/// A filter that can rounded each of the color channels based on the input amount
/// Inherits from Filter
ColorData FThreshold::generatePixel(const PixelBuffer &buffer, int x, int y) const
{
    ColorData c = buffer.getPixel(x, y);

    ColorData output;
    output.setRed(c.getRed() < m_amount? 0 : 1);
    output.setGreen(c.getGreen() < m_amount ? 0 : 1);
    output.setBlue(c.getBlue() < m_amount ? 0 : 1);

    return output;
}
