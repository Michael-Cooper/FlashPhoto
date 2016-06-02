
/*! \KGaussian.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/2/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "KGaussian.h"
#include <cmath>
#include <iostream>
#include "Helpers.h"
/// Kernel for the blur filter
/// Inherited from Kernel class
KGaussian::KGaussian() : m_sigma(0) {
    initKernel((int)ceil(m_sigma*3));
    generateKernel();
    normalize();

}
KGaussian::KGaussian(float sigma) : m_sigma(sigma) {
    initKernel((int)ceil(sigma));
    generateKernel();
    normalize();
}

/// Get intensity based on the radius
float KGaussian::getIntensity(int x, int y, float radius)
{
    if (radius < 1) {
        return 1;
    }
    float dist = sqrt(x*x + y*y);
    return Helpers::gaussian(dist, m_sigma);

}
