
/*! \ToolFactory.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */

#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include <vector>

class Tool;
/// This class stores all the tools
class ToolFactory
{
	/// Every tool has their own number
public:
	enum TOOLS
	{
		TOOL_PEN = 0,
		TOOL_ERASER = 1,
		TOOL_SPRAYCAN = 2,
		TOOL_CALLIGRAPHYPEN = 3,
		TOOL_HIGHLIGHTER = 4,
		TOOL_CHALK = 5,
        TOOL_STAMP = 6,
        TOOL_BLUR,
		NUMTOOLS
	};
	/// Get the number for the certain tool
	static int getNumTools();
	/// Create a new tool
	static Tool* createTool(int toolID);
};

#endif
