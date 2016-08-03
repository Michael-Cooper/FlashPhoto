
/*! \IPNGHandler.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/2/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef __PhotoShop__IPNGHandler__
#define __PhotoShop__IPNGHandler__

#include <string>
/// Loading and saving the chosen PNG images
#include "ImageHandler.h"

class PixelBuffer;
/// Loading and saving PNG images
class IPNGHandler : public ImageHandler {
public:
  /// Loading the input PNG images
    static PixelBuffer* loadImage(const std::string fileName);
    /// Save the canvas using given name
    static bool saveImage(const std::string fileName, const PixelBuffer* bufferToSave);
};

#endif
