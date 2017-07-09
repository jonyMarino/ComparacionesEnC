#ifndef OOC_TYPE_FLOAT_H
#define OOC_TYPE_FLOAT_H

/*
 *******************************
 * Float interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Float.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_FLOATING_H
#include <ooc/type/Floating.h>
#endif

#include ooc_Interface

#define CLASS Float
#define SUPER_CLASS Floating

#define CLASSDEF_Float				\
        CLASSDEF_Floating			\
    ooc_public(float, val)			\
						\
  ooc_method1(TYPE, initWith, float val)
 
#include ooc_End

#endif /* OOC_TYPE_FLOAT_H */
