//
// PixelBufferVector.cpp
// This is a helper class.
// Created by Cheng Chen.


#include "PixelBufferVector.h";
#include "PixelBuffer.h";

// Constructor of the PixelBufferVector class.
PixelBufferVector::PixelBufferVector() {}

// Destructor of the PixelBufferVector class.
PixelBufferVector::~PixelBufferVector() {
	myVector.clear();
}

// Get the PixelBufferVector object.
vector<PixelBuffer *> PixelBufferVector::getObject() {
	return myVector;
}

// Get the element in the vector by using index.
PixelBuffer * PixelBufferVector::getDataWithIndex(int index) {
	return myVector.at(index);
}

// Add a new element into the vector.
void PixelBufferVector::addData(PixelBuffer * buffer) {
	myVector.push_back (buffer);
}

// Delete the most recent element in the vector.
void PixelBufferVector::deleteData() {
	myVector.pop_back();
}

// Clear all of the elements in the vector.
void PixelBufferVector::clearData() {
	myVector.clear();
}

// Get the size of the vector.
int PixelBufferVector::getSize() {
	return myVector.size();
}
