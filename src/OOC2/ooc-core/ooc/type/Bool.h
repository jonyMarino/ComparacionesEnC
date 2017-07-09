#ifndef OOC_TYPE_BOOL_H
#define OOC_TYPE_BOOL_H

/*
 *******************************
 * Bool interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Bool.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS Bool
#define SUPER_CLASS Integral

#define CLASSDEF_Bool				\
        CLASSDEF_Integral			\
    ooc_public(bool, val)			\
						\
  ooc_method1(TYPE, initWith, bool val)

#include ooc_End

#endif /* OOC_TYPE_BOOL_H */
