
/*! \TBlur.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef TBLUR_H
#define TBLUR_H

#include <stdio.h>
#include "Tool.h"

class Filter;
/// A brush that can blur certain part of the canvas
class TBlur : public Tool {
protected:
    Filter* m_filter;
    int m_size;
    /// Process the pixel around the click point
    ColorData processPixel(int maskX, int maskY, ColorData toolColor, PixelBuffer* buffer, int bufferX, int bufferY);

public:
    TBlur();
    ~TBlur();
    /// Get the name of this tool
    std::string getName();
};

#endif
