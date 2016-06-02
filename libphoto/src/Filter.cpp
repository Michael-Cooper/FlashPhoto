
/*! \Filter.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/1/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
/// All non convoluted-based filters should inherit from Filter class as no kernel is needed
ColorData Filter::generatePixel(const PixelBuffer &buffer, int x, int y) const {
    ColorData p = buffer.getPixel(x, y);
    return p;
}

/// generate the filteredBuffer for the filters
PixelBuffer * Filter::generateFilteredBuffer(const PixelBuffer & input_buffer) {
    PixelBuffer * output_buffer = new PixelBuffer(input_buffer.getWidth(), input_buffer.getHeight(), input_buffer.getBackground());
    for (int i = 0; i < input_buffer.getWidth(); i++) {
        for (int j = 0; j < input_buffer.getHeight(); j++) {
            ColorData p = generatePixel(input_buffer, i, j);
            output_buffer->setPixel(i, j, p.clampedColor());
        }
    }
    return output_buffer;
}
