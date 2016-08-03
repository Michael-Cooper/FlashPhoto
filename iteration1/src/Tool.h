#ifndef TOOL_H
#define TOOL_H

class ColorData;
class PixelBuffer;
class BrushWorkApp;

class Tool {
  public:
	Tool();
	~Tool();

	virtual void Apply(int x, int y, int m_height, PixelBuffer* m_displayBuffer, ColorData color);

  protected:
	int maskHeight;
	int maskWidth;
	int centerX;
	int centerY;
	float ** mask;
};

#endif
