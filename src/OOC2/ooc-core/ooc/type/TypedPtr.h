#ifndef OOC_TYPE_TYPEDPTR_H
#define OOC_TYPE_TYPEDPTR_H

/*
 *******************************
 * Typed pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TypedPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_POINTER_H
#include <ooc/type/Pointer.h>
#endif

#include <ooc/type/type.h>

#include ooc_Interface

#define CLASS       TypedPtr
#define SUPER_CLASS Pointer

#define CLASSDEF_TypedPtr						 \
        CLASSDEF_Pointer						 \
    ooc_public(ooc_type, type)						 \
									 \
  ooc_method3(TYPE, initTypedPtr, void* ptr, size_t size, ooc_type type)
 
#include ooc_End

#endif /* OOC_TYPE_TYPEDPTR_H */
