
/*! \IJPGHandler.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/2/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef __PhotoShop__IJPGHandler__
#define __PhotoShop__IJPGHandler__

#include <stdio.h>
#include <string>

#include <jpeglib.h>
#include <setjmp.h>

#include "ImageHandler.h"

class PixelBuffer;
/// Loading and saving the chosen JPEG images
class IJPGHandler : public ImageHandler {
public:
  /// Loading the input JPEG images
    static PixelBuffer* loadImage(const std::string fileName);
    /// Save the canvas using given name
    static bool saveImage(const std::string fileName, const PixelBuffer* bufferToSave);
private:
    struct my_error_mgr {
        jpeg_error_mgr pub;	/* "public" fields */
        jmp_buf setjmp_buffer;	/* for return to caller */
    };
};

#endif
