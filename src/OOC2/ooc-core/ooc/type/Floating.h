#ifndef OOC_TYPE_FLOATING_H
#define OOC_TYPE_FLOATING_H

/*
 *******************************
 * Floating abstract interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Floating.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define ABSTRACT_CLASS Floating
#define SUPER_CLASS Number

#define CLASSDEF_Floating			\
        CLASSDEF_Number	
 
#include ooc_End

#endif /* OOC_TYPE_FLOATING_H */
