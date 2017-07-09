#ifndef OOC_TYPE_LONGLONG_H
#define OOC_TYPE_LONGLONG_H

/*
 *******************************
 * Long Long interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: LongLong.h,v 1.4 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_INTEGRAL_H
#include <ooc/type/Integral.h>
#endif

#include <ooc/type/llong.h>

#include ooc_Interface

#define CLASS LongLong
#define SUPER_CLASS Integral

#define CLASSDEF_LongLong			\
        CLASSDEF_Integral			\
    ooc_public(ooc_llong, val)			\
						\
  ooc_method1(TYPE, initWith, ooc_llong val)

#include ooc_End

#endif /* OOC_TYPE_LONGLONG_H */
