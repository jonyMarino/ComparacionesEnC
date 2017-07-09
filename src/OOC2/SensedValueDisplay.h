/*
 * SensedValueDisplay.h
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */

#ifndef SRC_OOC2_SENSED_VALUE_DISPLAY_H_
#define SRC_OOC2_SENSED_VALUE_DISPLAY_H_

#include "Observer.h"

#include OpenInterface

#define CLASS SensedValueDisplay
#define SUPER Observer

#define OBJDEF_SensedValueDisplay \
        OBJDEF_Observer   \
    // ... extra field(s) if any

#define CLASSDEF_SensedValueDisplay \
        CLASSDEF_Observer

#include CloseInterface


#endif
