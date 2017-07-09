#ifndef OOC_TYPE_TYPEDALLOCPTR_H
#define OOC_TYPE_TYPEDALLOCPTR_H

/*
 *******************************
 * Generic typed alloc pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TypedAllocPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_TYPEDPTR_H
#include <ooc/type/TypedPtr.h>
#endif

#include ooc_Interface

#define CLASS       TypedAllocPtr
#define SUPER_CLASS TypedPtr

#define CLASSDEF_TypedAllocPtr						    \
        CLASSDEF_TypedPtr						    \
    ooc_publicP(void, free, (void*))					    \
									    \
  ooc_method4(TYPE, initTypedAllocPtr, void *ptr, size_t size,		    \
	                               ooc_type type, void (*free)(void *))

#include ooc_End

#endif /* OOC_TYPE_TYPEDALLOCPTR_H */
