
/*! \KMotionBlur.h
 * PhotoShop Proj
 *
 *  Created by Seth Johnson on 4/4/15.
 *  Copyright (c) 2015 Seth Johnson. All rights reserved.
 *
 * For educational purposes only.  Please do not post online.
 */
#ifndef KMOTIONBLUR_H
#define KMOTIONBLUR_H

#include "Kernel.h"
/// Kernel for the motion blur filter
class KMotionBlur : public Kernel {
protected:

    float m_amount;
    int m_direction;
    /// Get the intensity
    float getIntensity(int x, int y, float radius);

public:
  /// Direction is needed for motion blur
    KMotionBlur(float amount, int direction);

};

#endif
