
/*! \TStamp.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef TSTAMP_H
#define TSTAMP_H

#include <stdio.h>
#include "Tool.h"

class PixelBuffer;
/// This tool can load the chosen image and work as a rubber stamp
class TStamp: public Tool {

public:
    TStamp();
    virtual ~TStamp();

    std::string getName();
    virtual int getWidth();
    virtual int getHeight();
    /// Load the chosen image and save it to the stampBuffer
    static void setStampBuffer(PixelBuffer * stampBuffer);
protected:
    static PixelBuffer *m_stampBuffer;
    ///Apply the pixel of the chosen image and apply it to the canvas
    virtual ColorData processPixel(int maskX, int maskY, ColorData toolColor, PixelBuffer* buffer, int bufferX, int bufferY);

};

#endif /* defined(__PhotoShop_Proj__TStamp__) */
