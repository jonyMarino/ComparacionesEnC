#ifndef OOC_TYPE_ARRAYPTR_H
#define OOC_TYPE_ARRAYPTR_H

/*
 *******************************
 * Generic Array pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ArrayPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_POINTER_H
#include <ooc/type/Pointer.h>
#endif

#include ooc_Interface

#define CLASS       ArrayPtr
#define SUPER_CLASS Pointer

#define CLASSDEF_ArrayPtr						\
        CLASSDEF_Pointer						\
    ooc_public(size_t, cnt )						\
									\
  ooc_method3(TYPE, initArrayPtr, void *ptr, size_t size, size_t cnt)

#include ooc_End

#endif /* OOC_TYPE_ARRAYPTR_H */
