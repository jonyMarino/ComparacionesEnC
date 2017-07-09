/*
 * Observer.h
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */

#ifndef SRC_OOC2_OBSERVER_H_
#define SRC_OOC2_OBSERVER_H_

#include <ooc/Object.h>

#include OpenInterface

#define ABSTRACT_CLASS Observer
#define SUPER Object

#define OBJDEF_Observer \
        OBJDEF_Object   \
    // ... extra field(s) if any

#define CLASSDEF_Observer \
        CLASSDEF_Object   \
		method(void, update , SELF, int  value);

#include CloseInterface


#endif /* SRC_OOC2_OBSERVER_H_ */
