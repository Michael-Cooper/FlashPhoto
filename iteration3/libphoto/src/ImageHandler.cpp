
/*! \ImageHandler.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/2/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#include "ImageHandler.h"

#include "PixelBuffer.h"
#include "ColorData.h"

#include "IPNGHandler.h"
#include "IJPGHandler.h"

#include <sstream>
#include <iostream>

using std::cout;
using std::endl;

/// This will identify the images' type and handle all the PNG and JPEG images 
PixelBuffer* ImageHandler::loadImage(const std::string & fileName) {

    IMAGE_TYPE imageType = getImageType(fileName);
    PixelBuffer* loadedImage = NULL;
    if (imageType == PNG_IMAGE) {
        loadedImage = IPNGHandler::loadImage(fileName);
    } else if (imageType == JPG_IMAGE) {
        loadedImage = IJPGHandler::loadImage(fileName);
    }  else {
        std::cout << "Incompatible image type" << std::endl;
    }
    return loadedImage;
}

bool ImageHandler::saveImage(const std::string & fileName, const PixelBuffer* bufferToSave) {
    IMAGE_TYPE imageType = getImageType(fileName);
    bool success = false;
    if (imageType == PNG_IMAGE) {
        success = IPNGHandler::saveImage(fileName, bufferToSave);
    } else if (imageType == JPG_IMAGE) {
        success = IJPGHandler::saveImage(fileName, bufferToSave);
    }  else {
        std::cout << "Incompatible image type" << std::endl;
    }
    return success;
}

ImageHandler::IMAGE_TYPE ImageHandler::getImageType(const std::string & fileName) {
    if (fileName.find(".png",fileName.size()-5) != std::string::npos) {
        return PNG_IMAGE;
    } else if (fileName.find(".jpg",fileName.size()-5) != std::string::npos || fileName.find(".jpeg",fileName.size()-6) != std::string::npos) {
        return JPG_IMAGE;
    } else {
        return UNKNOWN_IMAGE;
    }
}
