#ifndef OOC_TYPE_POINTER_H
#define OOC_TYPE_POINTER_H

/*
 *******************************
 * Pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Pointer.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS       Pointer
#define SUPER_CLASS BasicType

#define CLASSDEF_Pointer				\
        CLASSDEF_BasicType				\
    ooc_public(void* , ptr )				\
    ooc_public(size_t, size)				\
							\
  ooc_method2(TYPE, initPtr, void* ptr, size_t size)

#include ooc_End

#endif /* OOC_TYPE_POINTER_H */
