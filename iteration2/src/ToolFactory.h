//
//  ToolFactory.h
//  Student Support
//
//  Created by Seth Johnson on 2/6/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H

#include <vector>

class Tool;

class ToolFactory
{
public:
	enum TOOLS
	{
		TOOL_PEN = 0,
		TOOL_ERASER = 1,
		TOOL_SPRAYCAN = 2,
		TOOL_CALLIGRAPHYPEN = 3,
		TOOL_HIGHLIGHTER = 4,
		TOOL_TSTAMP = 5,
		TOOL_BLUR = 6,
		NUMTOOLS = 7
	};

	static int getNumTools();
	static Tool* createTool(int toolID);
};

#endif
