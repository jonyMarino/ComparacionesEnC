#ifndef OOC_TYPE_LONGDOUBLE_H
#define OOC_TYPE_LONGDOUBLE_H

/*
 *******************************
 * Long Double interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: LongDouble.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS LongDouble
#define SUPER_CLASS Floating

#define CLASSDEF_LongDouble			\
        CLASSDEF_Floating			\
    ooc_public(long double, val)		\
						\
  ooc_method1(TYPE, initWith, long double val)

#include ooc_End

#endif /* OOC_TYPE_LONGDOUBLE_H */
