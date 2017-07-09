#ifndef OOC_TYPE_FUNCTION_H
#define OOC_TYPE_FUNCTION_H

/*
 *******************************
 * Generic Function interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Function.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_BASICTYPE_H
#include <ooc/type/BasicType.h>
#endif

#include ooc_Interface

#define CLASS Function
#define SUPER_CLASS BasicType

#define CLASSDEF_Function			\
        CLASSDEF_BasicType			\
 ooc_public(ooc_function, fct)
 
#include ooc_End

#endif /* OOC_TYPE_FUNCTION_H */
