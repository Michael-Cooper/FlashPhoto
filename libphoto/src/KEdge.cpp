
/*! \KEdge.cpp
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/3/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#include "KEdge.h"
#include <cmath>
#include <iostream>
#include "Helpers.h"

/// A basic kernel for edge direction
KEdge::KEdge() {
    initKernel(1);
    generateKernel();
}
/// Calculate the intensity based on the radius
float KEdge::getIntensity(int x, int y, float radius)
{
    if (fabs(radius-x-1) < 1 && fabs(radius-y-1) < 1) {
        return 8;
    } else {
        return -1;
    }

}
