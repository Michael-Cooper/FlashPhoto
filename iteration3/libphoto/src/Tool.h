
/*! \Tool.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

 //!  Tool is the representation of a particular PaintShop tool.
 //!  This baseclass is abstract and does not provide a default mask.
 //!  Tools inherited from this class should provide a name and a mask.
 //!  Inherited classes may optionally override the default colorBlendMath.

#ifndef TOOL_H
#define TOOL_H

#include <string>
#include "Mask.h"

class PixelBuffer;
class ColorData;
class Mask;

/// This is the superclass for Tools.
class Tool
{
public:
	Tool();
	virtual ~Tool();
  /// Apply rule for all tools, override if needed
	virtual void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);
	virtual std::string getName() = 0;
    virtual int getWidth() { return m_mask? m_mask->getWidth() : 0;}
    virtual int getHeight() { return m_mask? m_mask->getHeight() : 0;}
    int getMaxSmear() { return m_maxSmear;}
    bool shouldSmear() { return m_maxSmear != 0;}
protected:
  /// Calculate the color to apply
	virtual ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);
  /// Process the apply rule to each pixel
    virtual ColorData processPixel(int maskX, int maskY, ColorData toolColor, PixelBuffer* buffer, int bufferX, int bufferY);
    bool m_keep_buffer_constant;
    int m_maxSmear;
	Mask *m_mask;
};

#endif
