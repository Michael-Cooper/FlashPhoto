
/*! \Kernel.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/1/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef KERNEL_H
#define KERNEL_H

#include "FloatMatrix.h"
/// Convolution-based filters can convolute a small kernel with the pixels in the image.
class Kernel : public FloatMatrix {
protected:
    void normalize();
    /// Initialize the kernel
    virtual void initKernel(int rad);
    /// Generate the kernel
    virtual void generateKernel() ;
    /// Get the intensity
    float getIntensity(int x, int y, float m_radius) ;
    int m_radius;
public:
    Kernel();
    /// Get the radius 
    int getRadius() {
        return m_radius;
    }
    ~Kernel();
    float sum();
    void print();

};
#endif
