//
//  MIAApp.h
//  Originally created by the CSci-3081W TAs.
//


#ifndef MIAAPP_H
#define MIAAPP_H

#include "BaseGfxApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <deque>
#include <stack>

class ColorData;
class PixelBuffer;
class Tool;
///This is the main class for the Mia app.  Everything runs from here.
class MIAApp : public BaseGfxApp {
public:

    MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~MIAApp();

    /// Glut overrided function
    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);

    void runCmdLine(int argc, char* argv[]);
    void displayHelpMessage();

private:

    /// GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_NEXT_IMAGE_BUTTON,
        UI_PREVIOUS_IMAGE_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_GRAYSCALE,
        UI_APPLY_MULTIPLY_RGB,
        UI_APPLY_QUANTIZE,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    std::string getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    /// enable previous image button when next consecutive image exists
    void previousImageEnabled(bool enabled);
    /// enable next image button when next consecutive image exists
    void nextImageEnabled(bool enabled);

    void loadImageToCanvas();
    void saveCanvasToFile();
    void loadNextImage();
    void loadPreviousImage();

    void applyFilterSharpen();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterMultiplyRGB();
    void applyFilterGrayScale();
    void applyFilterQuantize();
    void applyFilterBlur();
    void applyFilterSaturate();

    void undoOperation();
    void redoOperation();


    void initGlui();
    void initializeBuffers(ColorData initialColor, int width, int height);


    struct {
        float multiply_colorRed;
        float multiply_colorGreen;
        float multiply_colorBlue;
        float threshold_amount;
        float sharpen_amount;
        int quantize_bins;
        float blur_amount;
        float saturation_amount;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button* nextImageButton;
        GLUI_Button* previousImageButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;

        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;




    } m_gluiControlHooks;


    /// This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;

      std::deque<PixelBuffer*> m_historyStates;
      std::stack<PixelBuffer*> m_redoStates;

      ColorData m_toolColor;

      int m_maxUndos;

      /// save current canvas and commit it
      void commitState();
      /// switch to the previous stored canvas state
      void undoState();
      /// switch to the last canvas state after undo
      void redoState();

    /// These are used to store the selections from the GLUI user interface
    int m_curTool;

      Tool **m_tools;

      /// Previous mouse coordinates for interpolating mouse moves
      int m_mouseLastX, m_mouseLastY;

    float m_curColorRed, m_curColorGreen, m_curColorBlue;

    std::string m_fileName;
    std::string m_nextFileName;
    std::string m_prevFileName;


};


#endif
