
/*! \FChannels.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FChannels.h"
#include "ColorData.h"
#include "PixelBuffer.h"
// A filter that increase/decrease the intensity of each color channel
/// inherits from Filter
ColorData FChannels::generatePixel(const PixelBuffer & buffer, int x, int y) const
{
    const ColorData & p = buffer.getPixel(x, y);
    ColorData output(p.getRed()*m_red, p.getGreen()*m_green, p.getBlue()*m_blue,p.getAlpha());
    return output;
}
