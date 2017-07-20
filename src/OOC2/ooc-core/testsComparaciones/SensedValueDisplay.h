/*
 * SensedValueDisplay.h
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */

#ifndef SRC_OOC2_SENSED_VALUE_DISPLAY_H_
#define SRC_OOC2_SENSED_VALUE_DISPLAY_H_

#include "Observer.h"

#include ooc_Interface

#define CLASS SensedValueDisplay
#define SUPER_CLASS Observer

#define OBJDEF_SensedValueDisplay \
        OBJDEF_Observer   \
    // ... extra field(s) if any

#define CLASSDEF_SensedValueDisplay \
        CLASSDEF_Observer

#include ooc_End


#endif
