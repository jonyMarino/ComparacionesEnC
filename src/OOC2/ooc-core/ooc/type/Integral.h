#ifndef OOC_TYPE_INTEGRAL_H
#define OOC_TYPE_INTEGRAL_H

/*
 *******************************
 * Integral abstract interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Integral.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_NUMBER_H
#include <ooc/type/Number.h>
#endif

#include ooc_Interface

#define ABSTRACT_CLASS Integral
#define SUPER_CLASS Number

#define CLASSDEF_Integral			\
        CLASSDEF_Number	
 
#include ooc_End

#endif /* OOC_TYPE_INTEGRAL_H */
