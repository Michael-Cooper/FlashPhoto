/*! \FSpecial.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/7/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#ifndef __PhotoShop__FSpecial__
#define __PhotoShop__FSpecial__

#include <stdio.h>
#include "Filter.h"
/// A special filter defined by us
class FSpecial: public Filter {
public:
    PixelBuffer * generateFilteredBuffer(const PixelBuffer & input_buffer
                                         );
    virtual ColorData generatePixel(const PixelBuffer & buffer, const PixelBuffer & blurredBuffer, int x, int y) const;
};

#endif /* defined(__PhotoShop__FSpecial__) */
