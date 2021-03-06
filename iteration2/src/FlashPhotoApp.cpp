#include <stdio.h>
#include <cstdlib>
#include "FlashPhotoApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h"
#include "Tool.h"
#include "jpeglib.h"
#include "jconfig.h"
#include <setjmp.h>
#include <cmath>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <png.h>

#include <iostream>
#include "Filter.h"
#include "FDetectEdges.h"
#include "FBlur.h"
#include "FSharpen.h"
#include "FMotionBlur.h"
#include "FThreshold.h"
#include "FSaturation.h"
#include "FChannels.h"
#include "FQuantize.h"
#include "FVignette.h"
#include "TStamp.h"
#include "JpegHandler.h"
#include "PngHandler.h"
#include "PixelBufferVector.h"

using std::cout;
using std::endl;

FlashPhotoApp::FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("FlashPhoto");

    // Initialize Interface

    initializeBuffers(backgroundColor, width, height);


    // Create array of tools and populate
    m_tools = new Tool* [ToolFactory::getNumTools()];
    for (int i = 0; i < ToolFactory::getNumTools(); i++) {
      m_tools[i] = ToolFactory::createTool(i);
    }


    // Create Filters
    detectEdges = new FDetectEdges();
    blur = new FBlur();
    sharpen = new FSharpen();
    motionBlur = new FMotionBlur();
    threshold = new FThreshold();
    saturation = new FSaturation();
    channels = new FChannels();
    quantize = new FQuantize();
    vignette = new FVignette();

    // Create the object of the current pixelbuffer's vector.
	bufferVector = new PixelBufferVector();
	tempVector = new PixelBufferVector();

	// Initialize the undo times to be 0.
	undoTimes = 0;

	// Initialize the size to be the size of the pixelbuffer's vector.
	size = bufferVector->getSize();

    initGlui();
    initGraphics();

    // Store the initial pixelbuffer into the empty pixelbuffer's vector.
	bufferVector->addData(start);
}

void FlashPhotoApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

FlashPhotoApp::~FlashPhotoApp()
{
	if (m_displayBuffer) {
		delete m_displayBuffer;
	}
	
	if (m_new_displayBuffer) {
		delete m_new_displayBuffer;
	}

	if (copy) {
		delete copy;
	}

	if (temp) {
		delete temp;
	}

	if (start) {
		delete start;
	}

	if (m_buffer) {
		delete m_buffer;
	}

	// Delete each of the tools before deleting the list of tool pointers.
	if (m_tools) {
		Tool ** toolsEnd =  m_tools + ToolFactory::getNumTools();
		for (Tool ** tool_i = m_tools; tool_i < toolsEnd; tool_i++) {
			Tool* tool = *tool_i;
			if (tool) {
				delete tool;
			}
		}

		delete [] m_tools;
	}
}

void FlashPhotoApp::mouseDragged(int x, int y)
{
	int max_steps = 30;

	// We implimented a smoothing feature by interpolating between
	// mouse events. This is at the expense of processing, though,
	// because we just "stamp" the tool many times between the two
	// even locations. you can reduce max_steps until it runs
	// smoothly on your machine.

	// Get the differences between the events
	// in each direction
	int delta_x = x-m_mouseLastX;
	int delta_y = y-m_mouseLastY;

	// Calculate the min number of steps necesary to fill
	// completely between the two event locations.
	float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
	int step_count = pixelsBetween;
	int step_size = 1;

	// Optimize by maxing out at the max_steps,
	// and fill evenly between
	if (pixelsBetween > max_steps)
	{
		step_size = pixelsBetween/max_steps;
		step_count = max_steps;
	}

	// Iterate between the event locations
	for (int i = 0; i < pixelsBetween; i+=step_size)
	{
		int x = m_mouseLastX+(i*delta_x/pixelsBetween);
		int y = m_mouseLastY+(i*delta_y/pixelsBetween);

		m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);
	}

	// let the previous point catch up with the current.
	m_mouseLastX = x;
	m_mouseLastY = y;
}

void FlashPhotoApp::mouseMoved(int x, int y)
{

}

void FlashPhotoApp::leftMouseDown(int x, int y)
{
  if (m_curTool == 6){
	m_tools[m_curTool]->applyToBufferMouseDown(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);
	}
  else if (m_curTool == 5){
    m_tools[m_curTool]->applyToBufferStamp(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer, m_buffer);
  }
	else {
    cout<<"first"<<endl;
	  m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);
    cout<<"second"<<endl;
	}

	m_mouseLastX = x;
	m_mouseLastY = y;
}

void FlashPhotoApp::leftMouseUp(int x, int y)
{
    std::cout << "mouseReleased " << x << " " << y << std::endl;
    m_tools[m_curTool]->swap();

	// Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::initializeBuffers(ColorData backgroundColor, int width, int height)
{
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
    copy = new PixelBuffer(width, height, backgroundColor);
	temp = new PixelBuffer(width, height, backgroundColor);
	start = new PixelBuffer(width, height, backgroundColor);
    m_buffer = new PixelBuffer(width, height, backgroundColor);
}

void FlashPhotoApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Eraser");
        new GLUI_RadioButton(radio, "Spray Can");
        new GLUI_RadioButton(radio, "Caligraphy Pen");
        new GLUI_RadioButton(radio, "Highlighter");
        new GLUI_RadioButton(radio, "Stamp");
        new GLUI_RadioButton(radio, "Blur");
    }

    GLUI_Panel *colorPanel = new GLUI_Panel(m_glui, "Tool Color");
    {
        m_curColorRed = 0;
        m_gluiControlHooks.spinnerRed  = new GLUI_Spinner(colorPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
        m_gluiControlHooks.spinnerRed->set_float_limits(0, 1.0);

        m_curColorGreen = 0;
        m_gluiControlHooks.spinnerGreen  = new GLUI_Spinner(colorPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
        m_gluiControlHooks.spinnerGreen->set_float_limits(0, 1.0);

        m_curColorBlue = 0;
        m_gluiControlHooks.spinnerBlue  = new GLUI_Spinner(colorPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
        m_gluiControlHooks.spinnerBlue->set_float_limits(0, 1.0);

        new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
        new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
        new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
        new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
        new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
        new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
        new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
        new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
    }

    // UNDO,REDO,QUIT
    {
        m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
        undoEnabled(false);
        m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
        redoEnabled(false);

        new GLUI_Separator(m_glui);
        new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
    }

    new GLUI_Column(m_glui, true);
    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
        {
            GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:", &m_filterParameters.blur_amount);
            filterBlurAmount->set_int_limits(0, 20);

            filterBlurAmount->set_int_val(5);

            new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
        }

        GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
        {
            GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel, "Amount:", &m_filterParameters.motionBlur_amount);
            filterMotionBlurAmount->set_int_limits(0, 100);

            filterMotionBlurAmount->set_int_val(5);

            m_filterParameters.motionBlur_direction = 0;
            GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel, &m_filterParameters.motionBlur_direction);
            new GLUI_RadioButton(dirBlur, "North/South");
            new GLUI_RadioButton(dirBlur, "East/West");
            new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
            new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

            new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
        }
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(0, 100);

            filterSharpAmount->set_int_val(5);

            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);

            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
        }

		new GLUI_Column(filterPanel, true);

        GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
        {
            GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel, "Amount:", &m_filterParameters.saturation_amount);
            filterSaturationAmount->set_float_limits(-10, 10);
            filterSaturationAmount->set_float_val(1);

            new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
        }

        GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(channelPanel, "Red:", &m_filterParameters.channel_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(channelPanel, "Green:", &m_filterParameters.channel_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(channelPanel, "Blue:", &m_filterParameters.channel_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *vignettePanel = new GLUI_Panel(filterPanel, "Vignette"); // YOUR SPECIAL FILTER PANEL
        {
            new GLUI_Button(vignettePanel, "Apply", UI_APPLY_VIGNETTE_FILTER, s_gluicallback);
        }
    }

    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);

        m_gluiControlHooks.fileBrowser->set_h(400);

        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);
        m_gluiControlHooks.loadStampButton = new GLUI_Button(imagePanel, "Load Stamp", UI_LOAD_STAMP_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);

        loadCanvasEnabled(false);
        loadStampEnabled(false);
        saveCanvasEnabled(false);
    }
    return;
}

void FlashPhotoApp::gluiControl(int controlID)
{
    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_APPLY_BLUR:
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_DITHER:
            applyFilterThreshold();
            break;
        case UI_APPLY_SATURATE:
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_APPLY_VIGNETTE_FILTER:
            applyFilterVignette();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
            break;
        default:
            break;
    }

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how FlashPhotoApp should respond to the
// button presses.

void FlashPhotoApp::loadImageToCanvas()
{
  cout << "Load Canvas has been clicked for file " << m_fileName << endl;
  if (isValidImageFileName(m_fileName)){
      if(isValidImageFile(m_fileName)){
        // if it is the jpeg file
        if (hasSuffix(m_fileName,"jpg")||hasSuffix(m_fileName,"jpeg")){
          JpegHandler graph = JpegHandler();
          m_displayBuffer = graph.read_JPEG_file(&m_fileName[0u], m_displayBuffer);
          setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
        }
        // if it is the png file
        else if (hasSuffix(m_fileName,"png")){
          PngHandler graph = PngHandler();
          m_displayBuffer = graph.read_PNG_file(&m_fileName[0u], m_displayBuffer);
          setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
        }
        // more files in future
        else{
          cout << "More image types will be supported in future:) " << endl;
        }
      }
      else{printf("Invalid image file." );}
    }
    else{printf("Invalid image file name." );}

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::loadImageToStamp()
{
	cout << "Load Stamp has been clicked for file " << m_fileName << endl;
  if (isValidImageFileName(m_fileName)){
    if(isValidImageFile(m_fileName)){
      if (hasSuffix(m_fileName,"jpg")||hasSuffix(m_fileName,"jpeg")){
        JpegHandler graph = JpegHandler();
        m_buffer = graph.read_JPEG_file(&m_fileName[0u], m_buffer);
      }
      else if (hasSuffix(m_fileName,"png")){
        PngHandler graph = PngHandler();
        m_buffer = graph.read_PNG_file(&m_fileName[0u], m_buffer);
      }
      else{
        cout << "More image types will be supported in future:) " << endl;
      }
    }
    else{printf("Invalid image file." );}
  }
  else{printf("Invalid image file name." );}
}

void FlashPhotoApp::saveCanvasToFile()
{
	cout << "Save Canvas been clicked for file " << m_fileName << endl;

	if (hasSuffix(m_fileName,"jpg")){
	JpegHandler graph = JpegHandler();
	graph.write_JPEG_file(&m_fileName[0u], m_displayBuffer);
	}
	else if (hasSuffix(m_fileName,"png")) {
	PngHandler graph = PngHandler();
	graph.write_PNG_file(&m_fileName[0u], m_displayBuffer);

	}
	else{
	cout << "More image types will be supported in future:) " << endl;
	}
}

void FlashPhotoApp::applyFilterThreshold()
{
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    float params[] = {m_filterParameters.threshold_amount};
    threshold->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterChannel()
{
    cout << "Apply has been clicked for Channels with red = " << m_filterParameters.channel_colorRed
    << ", green = " << m_filterParameters.channel_colorGreen
    << ", blue = " << m_filterParameters.channel_colorBlue << endl;
    float params[] = {m_filterParameters.channel_colorRed, m_filterParameters.channel_colorGreen,
                      m_filterParameters.channel_colorBlue};
    channels->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturation_amount << endl;
    float params[] = {m_filterParameters.saturation_amount};
    saturation->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterBlur()
{
    cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
    float params[] = {m_filterParameters.blur_amount};
    blur->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    float params[] = {0};
    sharpen->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterMotionBlur()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.motionBlur_amount
    << " and direction " << m_filterParameters.motionBlur_direction << endl;
    motionBlur->setDirection(m_filterParameters.motionBlur_direction);
    float params[] = {m_filterParameters.motionBlur_amount};
    motionBlur->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    float params[] = {0};
    detectEdges->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    float params[] = {(float)m_filterParameters.quantize_bins};
    quantize->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::applyFilterVignette() {
    cout << "Apply has been clicked for Vignette" << endl;
    float params[] = {0};
    vignette->applyToBuffer(m_displayBuffer, params);

    // Add the new pixelbuffer into the vector of pixelbuffer's elements.
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoEnabled(true);
	redoEnabled(false);
	tempVector->clearData();
}

void FlashPhotoApp::undoOperation()
{
	temp = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, temp);
	tempVector->addData(temp);
	bufferVector->deleteData();
	PixelBuffer::copyPixelBuffer(bufferVector->getDataWithIndex(bufferVector->getSize() - 1), m_displayBuffer);

	undoTimes++;
	if (undoTimes > 0)
		redoEnabled(true);
	size = bufferVector->getSize();
	if (size <= 1)
		undoEnabled(false);
	// cout << bufferVector->getSize() << "---" << "Undoing..." << endl;
}

void FlashPhotoApp::redoOperation()
{
	PixelBuffer::copyPixelBuffer(tempVector->getDataWithIndex(tempVector->getSize() - 1), m_displayBuffer);
	tempVector->deleteData();
	copy = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
	PixelBuffer::copyPixelBuffer(m_displayBuffer, copy);
	bufferVector->addData(copy);

	undoTimes--;
	if (undoTimes <= 0)
		redoEnabled(false);
	size = bufferVector->getSize();
	if (size > 1)
		undoEnabled(true);
	// cout << bufferVector->getSize() << "---" << "Redoing..." << endl;

	if (tempVector->getSize() <= 0)
		redoEnabled(false);
}

// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void FlashPhotoApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void FlashPhotoApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void FlashPhotoApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void FlashPhotoApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void FlashPhotoApp::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void FlashPhotoApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void FlashPhotoApp::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}

bool FlashPhotoApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


bool FlashPhotoApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool FlashPhotoApp::isValidImageFile(const std::string & name) {

    FILE *f;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }
    return isValid;
}

void FlashPhotoApp::setImageFile(const std::string & fileName)
{
    // If a directory was selected
    // instead of a file, use the
    // latest file typed or selected.
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }


    // TOGGLE SAVE FEATURE
    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.

    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }

    // TOGGLE LOAD FEATURE

    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (isValidImageFile(imageFile)) {
        loadStampEnabled(true);
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadStampEnabled(false);
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void FlashPhotoApp::initGraphics() {
	// Initialize OpenGL for 2D graphics as used in the BrushWork app
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glViewport(0, 0, m_width, m_height);
}
