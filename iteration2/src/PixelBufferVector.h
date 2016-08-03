//
// PixelBufferVector.h
// This is a helper class.
// Created by Cheng Chen.


#ifndef PIXELBUFFERVECTOR_H
#define PIXELBUFFERVECTOR_H

#include <iostream>
#include <vector>
using namespace std;

class PixelBuffer;

class PixelBufferVector {
	public:
		PixelBufferVector();
		virtual ~PixelBufferVector();
		
		vector<PixelBuffer *> getObject();
		PixelBuffer * getDataWithIndex(int index);
		void addData(PixelBuffer * buffer);
		void deleteData();
		void clearData();
		int getSize();
	private:
		PixelBuffer * data;
		vector<PixelBuffer *> myVector;
};

#endif // PIXELBUFFERVECTOR_H

