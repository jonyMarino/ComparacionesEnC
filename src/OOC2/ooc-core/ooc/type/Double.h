#ifndef OOC_TYPE_DOUBLE_H
#define OOC_TYPE_DOUBLE_H

/*
 *******************************
 * Double interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Double.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS Double
#define SUPER_CLASS Floating

#define CLASSDEF_Double				\
        CLASSDEF_Floating			\
    ooc_public(double, val)			\
						\
  ooc_method1(TYPE, initWith, double val)

 
#include ooc_End

#endif /* OOC_TYPE_DOUBLE_H */
