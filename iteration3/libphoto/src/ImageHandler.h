
/*! \ImageHandler.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/2/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef __PhotoShop__ImageHandler__
#define __PhotoShop__ImageHandler__

#include <string>

class PixelBuffer;
/// Loading and saving PNG and JPEG images 
class ImageHandler {
public:
    enum IMAGE_TYPE {
        PNG_IMAGE,
        JPG_IMAGE,
        UNKNOWN_IMAGE
    };

    static PixelBuffer* loadImage(const std::string & fileName);
    static bool saveImage(const std::string & fileName, const PixelBuffer* bufferToSave);
private:
    //bool isValidImageFile(const std::string & fileName);
    static IMAGE_TYPE getImageType(const std::string & fileName);
};

#endif
