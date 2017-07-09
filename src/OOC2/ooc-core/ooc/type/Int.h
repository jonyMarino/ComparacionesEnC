#ifndef OOC_TYPE_INT_H
#define OOC_TYPE_INT_H

/*
 *******************************
 * Int interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Int.h,v 1.2 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_INTEGRAL_H
#include <ooc/type/Integral.h>
#endif

#include ooc_Interface

#define CLASS Int
#define SUPER_CLASS Integral

#define CLASSDEF_Int				\
        CLASSDEF_Integral			\
    ooc_public(int, val)			\
						\
  ooc_method1(TYPE, initWith, int val)
 
#include ooc_End

#endif /* OOC_TYPE_INT_H */
