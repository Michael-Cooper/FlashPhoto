//
//  Tool.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//
//  Tool is the representation of a particular PaintShop tool.
//  This baseclass is abstract and does not provide a default mask.
//  Tools inherited from this class should provide a name and a mask.
//  Inherited classes may optionally override the default colorBlendMath.


#ifndef TOOL_H
#define TOOL_H

#include <string>

class PixelBuffer;
class ColorData;
class Mask;

/// This is the superclass for Tools.
class Tool
{
public:
	Tool();
	virtual ~Tool();

	virtual void applyToBuffer(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);
	virtual void applyToBufferMouseDown(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer);
	virtual void applyToBufferStamp(int toolX, int toolY, ColorData toolColor, PixelBuffer* buffer, PixelBuffer* stamp);
	virtual std::string getName() = 0;
	virtual void swap();

protected:
	virtual ColorData colorBlendMath(float mask, ColorData toolColor, ColorData canvasColor, ColorData backgroundColor);
	Mask *m_mask;
};

#endif
