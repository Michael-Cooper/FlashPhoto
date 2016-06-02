
/*! \ToolFactory.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 2/6/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "ToolFactory.h"
#include "Tool.h"
#include "TPen.h"
#include "TEraser.h"
#include "TCalligraphyPen.h"
#include "THighlighter.h"
#include "TSprayCan.h"
#include "TChalk.h"
#include "TBlur.h"
#include "TStamp.h"
int ToolFactory::getNumTools()
{
	return NUMTOOLS;
}

/// Based on the number, we can identify each tool 
Tool* ToolFactory::createTool(int toolID)
{
	Tool* tool = NULL;

	switch (toolID) {
		case TOOL_PEN:
			tool = new TPen();
			break;
		case TOOL_ERASER:
			tool = new TEraser();
			break;
		case TOOL_SPRAYCAN:
			tool = new TSprayCan();
			break;
		case TOOL_CALLIGRAPHYPEN:
			tool = new TCalligraphyPen();
			break;
		case TOOL_HIGHLIGHTER:
			tool = new THighlighter();
			break;
		case TOOL_CHALK:
			tool = new TChalk();
			break;
        case TOOL_STAMP:
            tool = new TStamp();
            break;
        case TOOL_BLUR:
            tool = new TBlur();
            break;
		default:
			tool = NULL;
			break;
	}

	return tool;
}
