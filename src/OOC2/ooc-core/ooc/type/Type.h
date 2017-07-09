#ifndef OOC_TYPE_TYPE_H
#define OOC_TYPE_TYPE_H

/*
 *******************************
 * Type interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Type.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#include <ooc/Object.h>
#include <ooc/type/type.h>

#include ooc_Interface

#define CLASS Type

#define CLASSDEF_Type				\
    ooc_visible(ooc_type, type)			\
						\
    ooc_method1(TYPE, initWith, ooc_type type)

#include ooc_End

#endif /* OOC_TYPE_TYPE_H */
