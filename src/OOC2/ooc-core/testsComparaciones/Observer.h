/*
 * Observer.h
 *
 *  Created on: 9 jul. 2017
 *      Author: marino
 */

#ifndef SRC_OOC2_OBSERVER_H_
#define SRC_OOC2_OBSERVER_H_

#include <ooc/Object.h>

#include ooc_Interface

#define ABSTRACT_CLASS Observer

#define OBJDEF_Observer \
        OBJDEF_Object   \
    // ... extra field(s) if any

#define CLASSDEF_Observer \
        \
		ooc_method1(void, update , int  value)

#include  ooc_End


#endif /* SRC_OOC2_OBSERVER_H_ */
