/**
 * testFlashPhoto.cpp
 * 
 * Modified by chen4162
 */

#include "testFlashPhoto.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h"
#include "Tool.h"
#include "FSaturate.h"
#include "FBlur.h"
#include "FSharpen.h"
#include "FEdge.h"
#include "TStamp.h"
#include "Filter.h"
#include "ImageHandler.h"
#include "FilterFactory.h"
#include <sstream>
#include <cmath>

using std::cout;
using std::endl;

testFlashPhoto::testFlashPhoto(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    /** 
     * Set the name of the window
     */
    setCaption("testFlashPhoto");

    /** 
     * Initialize Interface
     */
    initializeBuffers(backgroundColor, width, height);

    /** 
     * Create array of tools and populate
     */
    m_tools = new Tool* [ToolFactory::getNumTools()];
    for (int i = 0; i < ToolFactory::getNumTools(); i++) {
        m_tools[i] = ToolFactory::createTool(i);
    }

    initGlui();
    initGraphics();

    m_maxUndos = 50;

	runTests();
}

void testFlashPhoto::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

testFlashPhoto::~testFlashPhoto()
{
    if (m_displayBuffer)
    {
        delete m_displayBuffer;
    }

	/** 
	 * Delete each of the tools before deleting the list of tool pointers.
	 */
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


void testFlashPhoto::mouseDragged(int x, int y)
{
    if (m_tools[m_curTool]->shouldSmear()) {
        int max_steps = m_tools[m_curTool]->getMaxSmear();

        
        /** 
		 * We implimented a smoothing feature by interpolating between
		 * mouse events. This is at the expense of processing, though,
		 * because we just "stamp" the tool many times between the two
		 * even locations. you can reduce max_steps until it runs
		 * smoothly on your machine.
		 * 
		 * Get the differences between the events
		 * in each direction
		 */
        int delta_x = x-m_mouseLastX;
        int delta_y = y-m_mouseLastY;

        /** 
		 * Calculate the min number of steps necesary to fill
		 * completely between the two event locations.
		 */
        float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
        int step_size = 1;

        /** 
		 * Optimize by maxing out at the max_steps,
		 * and fill evenly between
		 */
        if (pixelsBetween > max_steps)
        {
            step_size = pixelsBetween/max_steps;
        }

        /** 
		 * Iterate between the event locations
		 */
        for (int i = 0; i < pixelsBetween; i+=step_size)
        {
            int x = m_mouseLastX+(i*delta_x/pixelsBetween);
            int y = m_mouseLastY+(i*delta_y/pixelsBetween);

            m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);
        }
    }


	/** 
	 * let the previous point catch up with the current.
	 */
    m_mouseLastX = x;
    m_mouseLastY = y;

}

void testFlashPhoto::mouseMoved(int x, int y)
{

}

void testFlashPhoto::leftMouseDown(int x, int y)
{
    commitState();

    m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);

    m_mouseLastX = x;
    m_mouseLastY = y;
}

void testFlashPhoto::leftMouseUp(int x, int y)
{

}

void testFlashPhoto::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void testFlashPhoto::initGlui()
{
    /** 
	 * Select first tool (this activates the first radio button in glui)
	 */
    m_curTool = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);

        /** 
		 * Create interface buttons for different tools:
		 */
        for (int i = 0; i < ToolFactory::getNumTools(); i++) {
            new GLUI_RadioButton(radio, m_tools[i]->getName().c_str());
        }
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

    /** 
	 * UNDO,REDO,QUIT
	 */
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
            /** 
			 * new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
			 * new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");
			 */

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

        /** 
		 * Not in this iteration
		 * GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel, "\"Night Vision\" Filter"); // YOUR SPECIAL FILTER PANEL
		 * {
		 * 	new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_SPECIAL_FILTER, s_gluicallback);
		 * }
		 */
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

void testFlashPhoto::gluiControl(int controlID)
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
            commitState();
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            commitState();
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            commitState();
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            commitState();
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            commitState();
            applyFilterThreshold();
            break;
        case UI_APPLY_SATURATE:
            commitState();
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            commitState();
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            commitState();
            applyFilterQuantize();
            break;
        case UI_APPLY_SPECIAL_FILTER:
            commitState();
            applyFilterSpecial();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            commitState();
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            /** 
			 * Reload the current directory:
			 */
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

    /** 
	 * Forces canvas to update changes made in this function
	 */
    m_glui->post_update_main_gfx();
}


/** 
 * GLUI CALLBACKS
 * 
 * Edit these functions to provide instructions
 * for how testFlashPhoto should respond to the
 * button presses.
 */

void testFlashPhoto::loadImageToCanvas()
{
    if (m_displayBuffer) { delete m_displayBuffer; }
    m_displayBuffer = ImageHandler::loadImage(m_fileName);
    setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());
}

void testFlashPhoto::loadImageToStamp()
{
    TStamp::setStampBuffer(ImageHandler::loadImage(m_fileName));

    /** 
	 * setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());
	 */
}

void testFlashPhoto::saveCanvasToFile()
{
    if (ImageHandler::saveImage(m_fileName, m_displayBuffer)) {
        std::cout << "successfully saved image" << std::endl;
    } else {
        std::cout << "unsuccessfully saved image..." << std::endl;
    }
}

void testFlashPhoto::applyFilterThreshold()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_THRESHOLD, 1, m_filterParameters.threshold_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterChannel()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_CHANNELS, 3, m_filterParameters.channel_colorRed, m_filterParameters.channel_colorGreen, m_filterParameters.channel_colorBlue);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterSaturate()
{

    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SATURATION, 1, m_filterParameters.saturation_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterBlur()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_BLUR, 1, m_filterParameters.blur_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;


}

void testFlashPhoto::applyFilterSharpen()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SHARPEN, 1, m_filterParameters.sharpen_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;


}

void testFlashPhoto::applyFilterMotionBlur()
{
    Filter * f = FilterFactory::getFilter( FilterFactory::FILTER_MOTION_BLUR, 2, m_filterParameters.motionBlur_amount, m_filterParameters.motionBlur_direction);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterEdgeDetect() {
    Filter * f = FilterFactory::getFilter( FilterFactory::FILTER_EDGE_DETECT, 0);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterQuantize() {
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_QUANTIZE, 1, m_filterParameters.quantize_bins);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::applyFilterSpecial() {
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SPECIAL, 0);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;

}

void testFlashPhoto::undoOperation()
{
    undoState();
}

void testFlashPhoto::redoOperation()
{
    redoState();
}
/** 
 * END OF CALLBACKS
 */

/** 
 * Provided code for managing the
 * GLUI interface.
 */

void testFlashPhoto::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void testFlashPhoto::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void testFlashPhoto::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void testFlashPhoto::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void testFlashPhoto::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void testFlashPhoto::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void testFlashPhoto::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}

bool testFlashPhoto::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


bool testFlashPhoto::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool testFlashPhoto::isValidImageFile(const std::string & name) {

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

void testFlashPhoto::setImageFile(const std::string & fileName)
{
    /** 
	 * If a directory was selected
	 * instead of a file, use the
	 * latest file typed or selected.
	 */
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }


    /** 
	 * TOGGLE SAVE FEATURE
	 * If no file is selected or typed,
	 * don't allow file to be saved. If
	 * there is a file name, then allow
	 * file to be saved to that name.
	 */

    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }

    /** 
	 * TOGGLE LOAD FEATURE
	 * 
	 * If the file specified cannot be opened,
	 * then disable stamp and canvas loading.
	 */
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

void testFlashPhoto::commitState()
{
    PixelBuffer * newState = new PixelBuffer(m_displayBuffer->getWidth(),m_displayBuffer->getHeight(),m_displayBuffer->getBackground());

    PixelBuffer::copyPixelBuffer(m_displayBuffer, newState);

    m_historyStates.push_back(m_displayBuffer);

    m_displayBuffer = newState;

    while (!m_redoStates.empty()) {
        delete m_redoStates.top();
        m_redoStates.pop();
    }

    redoEnabled(!m_redoStates.empty());
    undoEnabled(!m_historyStates.empty());



}

void testFlashPhoto::redoState()
{
    m_historyStates.push_back(m_displayBuffer);
    m_displayBuffer = m_redoStates.top();
    m_redoStates.pop();

    setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());

    redoEnabled(!m_redoStates.empty());
    undoEnabled(!m_historyStates.empty());
}

void testFlashPhoto::undoState()
{
    if (!m_historyStates.empty() ) {
        if (m_historyStates.size() >= m_maxUndos) {
            delete m_historyStates.front();
            m_historyStates.pop_front();
        }
        m_redoStates.push(m_displayBuffer);
        m_displayBuffer = m_historyStates.back();
        m_historyStates.pop_back();
        setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());

    }

    redoEnabled(!m_redoStates.empty());
    undoEnabled(!m_historyStates.empty());

    display();
}

/** 
 * The function below is to call the testTool 
 * function by using a for loop.
 * Except that i = 5 (when the tool is chalk), 
 * all tools will call the testTool funcion.
 */
void testFlashPhoto::runTests()
{
	for (int i=0; i<8; i++)
	{
		if (i != 5)
		{
			testTool(i);
		}
	}
	exit(0);
}


/** 
 * The function below is to create the names of
 * the output images automatically.
 */
std::string testFlashPhoto::name(int index)
{
	std::string name = "out2";
	std::stringstream n;
	n << index;
	name += n.str() + ".png";
	return name;
}

/** 
 * The function below is to input some images for each
 * tool and then use the tools to deal with the images.
 * Then output the corresponding images to be compared
 * with the standard images that stored in the images
 * directory.
 */
void testFlashPhoto::testTool(int index)
{
	/** 
	 * Load the background image as canvas.
	 */
	loadCanvasEnabled(true);
	if (index == 7)
	{
		m_fileName = "images/in0.png";
		loadImageToCanvas();
	}
	
	/** 
	 * Load the stamp when we use the stamp tool.
	 */
	if (index == 6)
	{
		loadStampEnabled(true);
		m_fileName = "images/colorCircles.png";
		loadImageToStamp();
		m_curColorRed = 1.0;
		m_curColorGreen = 1.0;
		m_curColorBlue = 1.0;
	}

	/** 
	 * Determine the tool and determine a start position to draw.
	 */
	m_curTool = index;
	leftMouseDown(200,200);

	/** 
	 * Drag a line by using different tools.
	 */
	if (index == 1)
	{
		m_curTool = 0;
		leftMouseDown(200,200);
		mouseDragged(220,220);
		mouseDragged(240,240);
		mouseDragged(260,260);
		mouseDragged(280,280);
		mouseDragged(300,300);
		mouseDragged(320,320);
		mouseDragged(340,340);
		mouseDragged(360,360);
		leftMouseUp(360,360);
		
		m_curTool = index;
		leftMouseDown(200,200);
		mouseDragged(220,220);
		mouseDragged(240,240);
		mouseDragged(260,260);
		mouseDragged(280,280);
		leftMouseUp(280,280);
	}
	
	else if (index == 2 || index == 7)
	{
		mouseDragged(220,220);
		mouseDragged(225,225);
		mouseDragged(230,230);
		mouseDragged(235,235);
		mouseDragged(240,240);
		mouseDragged(245,245);
		mouseDragged(250,250);
		mouseDragged(255,255);
		mouseDragged(260,260);
		mouseDragged(265,265);
		mouseDragged(270,270);
		mouseDragged(275,275);
		mouseDragged(280,280);
		mouseDragged(285,285);
		mouseDragged(290,290);
		mouseDragged(295,295);
		mouseDragged(300,300);
		leftMouseUp(300,300);
	}
	
	else if (index == 6)
	{
		mouseDragged(220,220);
		leftMouseUp(220,220);
	}
	
	else
	{
		mouseDragged(220,220);
		mouseDragged(240,240);
		mouseDragged(260,260);
		mouseDragged(280,280);
		mouseDragged(300,300);
		mouseDragged(320,320);
		mouseDragged(340,340);
		mouseDragged(360,360);
		leftMouseUp(360,360);
	}

	/** 
	 * Save the completed images as the output images.
	 */
	saveCanvasEnabled(true);
	m_fileName = std::string("images/")+name(index);
	saveCanvasToFile();

	initializeBuffers(ColorData(1,1,0.95),400,400);

	loadCanvasEnabled(false);
	loadStampEnabled(false);
	saveCanvasEnabled(false);
}
