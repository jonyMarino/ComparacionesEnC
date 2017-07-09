#ifndef OOC_TYPE_COMPLEX_H
#define OOC_TYPE_COMPLEX_H

/*
 *******************************
 * Complex abstract interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Complex.h,v 1.4 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_FLOATING_H
#include <ooc/type/Floating.h>
#endif

#include <ooc/type/complex.h>

#include ooc_Interface

#define CLASS Complex
#define SUPER_CLASS Floating

#define CLASSDEF_Complex				\
        CLASSDEF_Floating				\
    ooc_public(ooc_complex, val)			\
							\
  ooc_method2(TYPE, initWith, double real, double imag)
 
#include ooc_End

#endif /* OOC_TYPE_COMPLEX_H */
