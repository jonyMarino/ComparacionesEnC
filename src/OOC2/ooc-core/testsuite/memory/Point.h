#ifndef OOC_TESTSUITE_MEM_POINT_H
#define OOC_TESTSUITE_MEM_POINT_H

/*
 ******************************
 * Point interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Point.h,v 1.1 2005/10/28 16:27:13 oachim Exp $
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#include <ooc/Object.h>

#include ooc_Interface

#define FINAL_CLASS Point

#define CLASSDEF_Point				\
        Point_PRIVATE_DEF			\
						\
    ooc_method0(void  , mthd)			\
    ooc_method1(void  , mthdArg   , Object obj)	\
    ooc_method1(Object, mthdRetArg, Object obj)

#ifndef Point_PRIVATE_DEF
#define Point_PRIVATE_DEF
#endif

#include ooc_End

#endif /* OOC_TESTSUITE_MEM_POINT_H */
