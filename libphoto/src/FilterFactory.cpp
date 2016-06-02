
/*! \FilterFactory.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "FilterFactory.h"
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include "FBlur.h"
#include "FSharpen.h"
#include "FSaturate.h"
#include "FEdge.h"
#include "FQuantize.h"
#include "FChannels.h"
#include "FThreshold.h"
#include "FMotionBlur.h"
#include "FSpecial.h"

#include "PixelBuffer.h"

/// A class that stored all the filters, get the number of the filter and change the apply rule for different filters
int FilterFactory::getNumFilters()
{
    return NUMFILTERS;
}

/// Different filters have different ID numbers
Filter*  FilterFactory::getFilter( int filterID, int param_count, ...)
{
    va_list vl;
    va_start(vl,param_count);

    Filter * f = NULL;
    switch (filterID) {
        case FILTER_BLUR:
            f = new FBlur(va_arg(vl,double));
            break;
        case FILTER_MOTION_BLUR:
            f = new FMotionBlur(va_arg(vl,double),va_arg(vl,int));
            break;
        case FILTER_SHARPEN:
            f = new FSharpen(va_arg(vl,double));
            break;
        case FILTER_EDGE_DETECT:
            f = new FEdge;
            break;
        case FILTER_SATURATION:
            f = new FSaturate(va_arg(vl,double));
            break;
        case FILTER_QUANTIZE:
            f = new FQuantize(va_arg(vl,int));
            break;
        case FILTER_THRESHOLD:
            f = new FThreshold(va_arg(vl,double));
            break;
        case FILTER_CHANNELS:
            f = new FChannels(va_arg(vl,double),va_arg(vl,double),va_arg(vl,double));
            break;
        case FILTER_SPECIAL:
            f = new FSpecial();
            break;
        default:
            break;
    }
    va_end(vl);

    return f;
}

void FilterFactory::applyFilter(Filter* f, PixelBuffer *& buffer)
{
    PixelBuffer* oldBuffer = buffer;
    if (f) {
        buffer = f->generateFilteredBuffer(*buffer);
        if (oldBuffer) {
            delete oldBuffer;
        }
    }
}
