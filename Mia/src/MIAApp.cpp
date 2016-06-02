#include "MIAApp.h"
#include "ToolFactory.h"
#include "Tool.h"
#include "TStamp.h"
#include "Filter.h"
#include "ImageHandler.h"
#include "FilterFactory.h"
#include "ColorData.h"

#include <cmath>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

int debug = 0;

MIAApp::MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    /// Set the name of the window
    setCaption("Medical Image Analysis (MIA)");

    ///Initialize Interface
    initializeBuffers(backgroundColor, width, height);

    m_tools = new Tool* [2];
    m_tools[0] = ToolFactory::createTool(0);
    m_tools[1] = ToolFactory::createTool(6);

    PixelBuffer * sbuffer = ImageHandler::loadImage("../marker.png");
    TStamp::setStampBuffer(sbuffer);

    m_toolColor = ColorData(1,0,0); // red

    initGlui();
    initGraphics();

    m_maxUndos = 50;

    if (argc > 1) {
        runCmdLine(argc, argv);
    }
}
/// Function that runs when at least one argument is passed into function; this is command line mode
void MIAApp::runCmdLine(int argc, char* argv[]) {
    std::string inFilename = "";
    std::string inFileExtension = "";
    std::string outFilename = "";
    std::string outFileExtension = "";

    int patternDigits = 0;
    int stackCounter = 0;

    std::string nextArg = argv[1];

    if (nextArg.compare("-h") == 0) {
        displayHelpMessage();
        exit(0);
    } else { // first argument is a filename
        if (argc < 3) {
            cout << "Usage: Mia <infile> args <outfile>" << endl;
            displayHelpMessage();
            exit(1);
        }

        if (debug) {
            cout << "nextArg: " << nextArg << endl;
        }

        unsigned long pound = (unsigned long)nextArg.find("#");
        std::size_t extensionStart = nextArg.find_last_of(".");
        if (extensionStart == std::string::npos) {
            cout << "Invalid filename" << endl;
            displayHelpMessage();
            exit(1);
        }

        if (pound != std::string::npos) { // if the filename contains a '#'
            inFilename = nextArg.substr(0, pound);
            while (nextArg.at(pound) == '#') { // count number of digits represented by '#'
                if (debug) {
                    cout << "nextArg.at(pound)" << nextArg.at(pound) << "   " << pound << endl;
                }
                pound++;
                patternDigits++;
            }
        }
        else {
            inFilename = nextArg.substr(0, extensionStart);
        }

        // get in-file extension
        if (nextArg.substr(extensionStart, std::string::npos).compare(".jpg") && nextArg.substr(extensionStart, std::string::npos).compare(".png")) {
            cout << "Invalid file extension" << endl;
            displayHelpMessage();
            exit(1);
        }
        inFileExtension = nextArg.substr(extensionStart);

        if (debug) {
            cout << "inFileExtension: " << inFileExtension << endl;
        }

        for (; stackCounter < pow(10, patternDigits); stackCounter++) {

            if (debug) {
                cout << "for-loop iteration" << endl;
            }

            // generate file ref number
            std::string fileIndex = "";

            if (patternDigits > 0) {
                for (int k = patternDigits; k > 0; k--) {
                    char fileIndexCharArr[patternDigits + 1];
                    sprintf(fileIndexCharArr, "%d", (stackCounter % (int)pow(10, k)) / (int)pow(10, k-1));
                    fileIndex = fileIndex + string(fileIndexCharArr);
                }
            }

            // check if filename is valid image file
            m_fileName = inFilename + fileIndex + inFileExtension;
            if (isValidImageFile(m_fileName) == 0) {
                if (patternDigits == 0) { // if we're not pattern matching, show error message if input file wasn't valid
                    cout << "Failed to load file: " << m_fileName << " is not a valid image file" << endl;
                    displayHelpMessage();
                    exit(1);
                }
                continue;
            }

            // perform image load
            loadImageToCanvas();

            if (debug) {
                cout << "Image sucessfully loaded to canvas" << endl;
            }


            // iterate through all arguments & perform filters
            for (int i = 2; i < argc; i++) {
                nextArg = string(argv[i]);

                if (debug) {
                    cout << "using argument " << nextArg << endl;
                }
                if (nextArg.compare("-h") == 0) {
                    displayHelpMessage();
                    continue;
                } else if (nextArg.compare("-sharpen") == 0) {

                    if (argc <= i + 1) {
                        cout << "Argument -sharpen requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double value = atof(argv[i]);
                        m_filterParameters.sharpen_amount = value;
                        applyFilterSharpen();
                    }

                } else if (nextArg.compare("-edgedetect") == 0) {
                    applyFilterEdgeDetect();
                } else if (nextArg.compare("-thresh") == 0) {
                    if (argc <= i + 1) {
                        cout << "Argument -thresh requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double value = atof(argv[i]);
                        m_filterParameters.threshold_amount = value;
                        applyFilterThreshold();
                    }

                } else if (nextArg.compare("-quantize") == 0) {
                    if (argc <= i + 1) {
                        cout << "Argument -quantize requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double value = atof(argv[i]);
                        m_filterParameters.quantize_bins = value;
                        applyFilterQuantize();
                    }

                } else if (nextArg.compare("-blur") == 0) {
                    if (argc <= i + 1) {
                        cout << "Argument -blur requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double value = atof(argv[i]);
                        m_filterParameters.blur_amount = value;
                        applyFilterBlur();
                    }

                } else if (nextArg.compare("-saturate") == 0) {
                    if (argc <= i + 1) {
                        cout << "Argument -saturate requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double value = atof(argv[i]);
                        m_filterParameters.saturation_amount = value;
                        applyFilterSaturate();
                    }

                } else if (nextArg.compare("-multrgb") == 0) {
                    if (argc <= i + 3) {
                        cout << "Argument -saturate requires 1 parameter" << endl;
                        displayHelpMessage();
                        exit(1);
                    } else if (inFilename.compare(" ")){
                        i++;
                        double rvalue = atof(argv[i]);
                        i++;
                        double gvalue = atof(argv[i]);
                        i++;
                        double bvalue = atof(argv[i]);
                        m_filterParameters.multiply_colorRed = rvalue;
                        m_filterParameters.multiply_colorGreen = gvalue;
                        m_filterParameters.multiply_colorBlue = bvalue;
                        applyFilterMultiplyRGB();
                    }

                } else if (nextArg.compare("-compare") == 0) {
                    if (patternDigits != 0) {
                        cout << "Compare feature doesn't support multiple file input" << endl;
                        displayHelpMessage();
                        exit(1);
                    }
                    if (inFilename.compare(" ")) {
                        if (argc <= i + 1) {
                            cout << "Argument -compare requires a filename as a parameter" << endl;
                            displayHelpMessage();
                            exit(1);
                        } else {
                            i++;
                            std::string name = string(argv[i]);

                            if (!isValidImageFile(name)) {
                                cout << name << " is not a valid png/jpg image file" << endl;
                                displayHelpMessage();
                                exit(1);
                            }

                            PixelBuffer* buffer2Compare = ImageHandler::loadImage(name);

                            if (m_displayBuffer->getHeight() != buffer2Compare->getHeight()) {
                                cout << 0 << endl;
                                exit(2);
                            }
                            if (m_displayBuffer->getWidth() != buffer2Compare->getWidth()) {
                                cout << 0 << endl;
                                exit(2);
                            }

                            for (int y = 0; y < m_displayBuffer->getHeight(); y++) {
                                for (int x = 0; x < m_displayBuffer->getWidth(); x++) {
                                    if (m_displayBuffer->getPixel(x,y).getRed() != buffer2Compare->getPixel(x,y).getRed()) {
                                        cout << 0 << endl;
                                        exit(2);
                                    }
                                    if (m_displayBuffer->getPixel(x,y).getGreen() != buffer2Compare->getPixel(x,y).getGreen()) {
                                        cout << 0 << endl;
                                        exit(2);
                                    }
                                    if (m_displayBuffer->getPixel(x,y).getBlue() != buffer2Compare->getPixel(x,y).getBlue()) {
                                        cout << 0 << endl;
                                        exit(2);
                                    }
                                }
                            }
                            cout << 1 << endl;
                            exit(0);
                        } // end else
                    } // end if

                } else { // out-file name

                    // generate out-filename
                    pound = nextArg.find("#");
                    extensionStart = nextArg.find_last_of('.');

                    if (pound != std::string::npos && patternDigits != 0) { // if the filename contains at least one '#'
                        outFilename = nextArg.substr(0, pound) + fileIndex;
                    } else if (patternDigits == 0) {
                        if (extensionStart != std::string::npos) {
                            outFilename = nextArg.substr(0, extensionStart);
                        }
                    } else {
                        cout << "Invalid output filename: must contain at least one '#'" << endl;
                        displayHelpMessage();
                        exit(1);
                    }

                    // get out-file extension
                    if (extensionStart == std::string::npos) {
                        cout << "Invalid outfile name" << endl;
                        displayHelpMessage();
                        exit(1);
                    }
                    if (nextArg.substr(extensionStart).compare(".jpg") && nextArg.substr(extensionStart).compare(".png")) {
                        cout << "Invalid outfile extension" << endl;
                        displayHelpMessage();
                        exit(1);
                    }
                    outFileExtension = nextArg.substr(extensionStart);

                    // save file
                    m_fileName = outFilename + outFileExtension;
                    saveCanvasToFile();
                    break;
                }
            } // end for-loop

        } // end for-loop
        if (outFilename.compare("") == 0) {
            cout << "No output file specified" << endl;
            displayHelpMessage();
            exit(1);
        }
        exit(0);
	} // end else
}

void MIAApp::displayHelpMessage() {
    cout << "Usage: Mia <infile> args <outfile>" << endl << endl;
    cout << "infile and outfile must have extension .png or .jpg" << endl << endl;
    cout << "Accepted arguments (with required paramters in brackets (<>)):" << endl << endl;
    cout << "Image filters:" << endl;
    cout << "  -sharpen <integer>" << endl;
    cout << "  -edgedetect" << endl;
    cout << "  -thresh <float>" << endl;
    cout << "  -quantize <int>" << endl;
    cout << "  -blur <float>" << endl;
    cout << "  -saturate <float>" << endl;
    cout << "  -multrgb <float> <float> <float>" << endl;
    cout << "  -sharpen <integer>" << endl << endl;
    cout << "-compare <valid image filename>" << endl;
    cout << "  [Prints '1' if image files match, pixel by pixel. Otherwise prints '0'.]" << endl << endl;
}

void MIAApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

MIAApp::~MIAApp()
{
    if (m_displayBuffer)
    {
        delete m_displayBuffer;
    }

    // Delete each of the tools before deleting the list of tool pointers.
    if (m_tools) {
        Tool ** toolsEnd =  m_tools + 2;
        for (Tool ** tool_i = m_tools; tool_i < toolsEnd; tool_i++) {
            Tool* tool = *tool_i;
            if (tool) {
                delete tool;
            }
        }

        delete [] m_tools;
    }
}


void MIAApp::mouseDragged(int x, int y)
{
    if (m_tools[m_curTool]->shouldSmear()) {
        int max_steps = m_tools[m_curTool]->getMaxSmear();

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
        int step_size = 1;

        // Optimize by maxing out at the max_steps,
        // and fill evenly between
        if (pixelsBetween > max_steps)
        {
            step_size = pixelsBetween/max_steps;
        }

        // Iterate between the event locations
        for (int i = 0; i < pixelsBetween; i+=step_size)
        {
            int x = m_mouseLastX+(i*delta_x/pixelsBetween);
            int y = m_mouseLastY+(i*delta_y/pixelsBetween);

            m_tools[m_curTool]->applyToBuffer(x, m_height-y, m_toolColor, m_displayBuffer);
        }
    }


    // let the previous point catch up with the eent.
    m_mouseLastX = x;
    m_mouseLastY = y;
}

void MIAApp::mouseMoved(int x, int y)
{

}

void MIAApp::leftMouseDown(int x, int y)
{
    commitState();

    m_tools[m_curTool]->applyToBuffer(x, m_height-y, m_toolColor, m_displayBuffer);

    m_mouseLastX = x;
    m_mouseLastY = y;
}

void MIAApp::leftMouseUp(int x, int y)
{

}

void MIAApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void MIAApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;



    new GLUI_Column(m_glui, false);
    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Arrow");

    }


    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(1, 10);
            filterSharpAmount->set_int_val(1);
            filterSharpAmount->set_speed(0.1);

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

        GLUI_Panel *multiplyPanel = new GLUI_Panel(filterPanel, "Multiply RGB");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(multiplyPanel, "R:", &m_filterParameters.multiply_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(multiplyPanel, "G:", &m_filterParameters.multiply_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(multiplyPanel, "B:", &m_filterParameters.multiply_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(multiplyPanel, "Apply", UI_APPLY_MULTIPLY_RGB, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *grayPanel = new GLUI_Panel(filterPanel, "Grayscale");
        {

            new GLUI_Button(grayPanel, "Apply", UI_APPLY_GRAYSCALE, s_gluicallback);
        }



        /// UNDO,REDO,QUIT
        {
            m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
            undoEnabled(false);
            m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
            redoEnabled(false);

            new GLUI_Separator(m_glui);
            new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
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

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);


        m_gluiControlHooks.previousImageButton = new GLUI_Button(imagePanel, "Previous Image", UI_PREVIOUS_IMAGE_BUTTON, s_gluicallback);
        m_gluiControlHooks.nextImageButton = new GLUI_Button(imagePanel, "Next Image", UI_NEXT_IMAGE_BUTTON, s_gluicallback);


        loadCanvasEnabled(false);
        saveCanvasEnabled(false);
        nextImageEnabled(false);
        previousImageEnabled(false);
    }
    return;
}

void MIAApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_APPLY_SHARP:
            commitState();
            applyFilterSharpen();
            break;
        case UI_APPLY_EDGE:
            commitState();
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            commitState();
            applyFilterThreshold();
            break;
        case UI_APPLY_GRAYSCALE:
            commitState();
            applyFilterGrayScale();
            break;
        case UI_APPLY_MULTIPLY_RGB:
            commitState();
            applyFilterMultiplyRGB();
            break;
        case UI_APPLY_QUANTIZE:
            commitState();
            applyFilterQuantize();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            commitState();
            loadImageToCanvas();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_NEXT_IMAGE_BUTTON:
            commitState();
            loadNextImage();
            break;
        case UI_PREVIOUS_IMAGE_BUTTON:
            commitState();
            loadPreviousImage();
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
// for how MIAApp should respond to the
// button presses.

void MIAApp::loadImageToCanvas()
{
    if (m_displayBuffer) { delete m_displayBuffer; }
    m_displayBuffer = ImageHandler::loadImage(m_fileName);
    setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());


    // Determining whether there are next or previous images
    m_nextFileName = getImageNamePlusSeqOffset(m_fileName, 1);
    m_prevFileName = getImageNamePlusSeqOffset(m_fileName, -1);

    nextImageEnabled(isValidImageFile(m_nextFileName));
    previousImageEnabled(isValidImageFile(m_prevFileName));
}

void MIAApp::saveCanvasToFile()
{
    if (ImageHandler::saveImage(m_fileName, m_displayBuffer)) {
        std::cout << "successfully saved image" << std::endl;
    } else {
        std::cout << "unsuccessfully saved image..." << std::endl;
    }
}

void MIAApp::applyFilterThreshold()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_THRESHOLD, 1, m_filterParameters.threshold_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterMultiplyRGB()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_CHANNELS, 3, m_filterParameters.multiply_colorRed, m_filterParameters.multiply_colorGreen, m_filterParameters.multiply_colorBlue);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterGrayScale()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SATURATION, 1, m_filterParameters, 0);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}


void MIAApp::applyFilterSharpen()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SHARPEN, 1, m_filterParameters.sharpen_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterEdgeDetect() {
    Filter * f = FilterFactory::getFilter( FilterFactory::FILTER_EDGE_DETECT, 0);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterQuantize() {
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_QUANTIZE, 1, m_filterParameters.quantize_bins);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterBlur() {
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_BLUR, 1, m_filterParameters.blur_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::applyFilterSaturate()
{
    Filter * f = FilterFactory::getFilter(FilterFactory::FILTER_SATURATION, 1, m_filterParameters.saturation_amount);
    FilterFactory::applyFilter(f, m_displayBuffer);
    delete f;
}

void MIAApp::undoOperation()
{
    undoState();
}

void MIAApp::redoOperation()
{
    redoState();
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void MIAApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void MIAApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void MIAApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void MIAApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void MIAApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void MIAApp::previousImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.previousImageButton, enabled);
}

void MIAApp::nextImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.nextImageButton, enabled);
}

void MIAApp::loadNextImage()
{
    setImageFile(m_nextFileName);
    loadImageToCanvas();
}

void MIAApp::loadPreviousImage()
{
    setImageFile(m_prevFileName);
    loadImageToCanvas();
}


bool MIAApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}

bool MIAApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool MIAApp::isValidImageFile(const std::string & name) {

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

std::string MIAApp::getImageNamePlusSeqOffset(const std::string & currentFileName, int offset)
{

    int digitCount = 3;

    std::string extension, name, number;
    size_t dotPos = currentFileName.find_last_of(".");
    if (dotPos ==  std::string::npos || dotPos == 0) {
        return "";
    }

    extension = currentFileName.substr(dotPos+1);
    name = currentFileName.substr(0,dotPos);
    if (name.length() < digitCount) {
        return "";
    }

    number = name.substr(name.length()-digitCount);
    name = name.substr(0,name.length()-digitCount);
    int num;
    std::istringstream ( number ) >> num;
    int output_num = num +offset;
    if (output_num < 0) {
        return "";
    }
    std::stringstream ss;
    ss << output_num;
    std::string output_number;
    ss >> output_number;

    // Append zero chars
    size_t str_length = output_number.length();
    for (int i = 0; i < digitCount - str_length; i++)
        output_number = "0" + output_number;




    return (name + output_number + "." + extension);
}

void MIAApp::setImageFile(const std::string & fileName)
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
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void MIAApp::commitState()
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

void MIAApp::redoState()
{
    m_historyStates.push_back(m_displayBuffer);
    m_displayBuffer = m_redoStates.top();
    m_redoStates.pop();

    setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());

    redoEnabled(!m_redoStates.empty());
    undoEnabled(!m_historyStates.empty());
}

void MIAApp::undoState()
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
