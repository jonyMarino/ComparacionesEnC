#ifndef OOC_TYPE_TYPEDALLOCARRAYPTR_H
#define OOC_TYPE_TYPEDALLOCARRAYPTR_H

/*
 *******************************
 * Generic typed alloc array pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TypedAllocArrayPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_TYPEDARRAYPTR_H
#include <ooc/type/TypedArrayPtr.h>
#endif

#include ooc_Interface

#define CLASS       TypedAllocArrayPtr
#define SUPER_CLASS TypedArrayPtr

#define CLASSDEF_TypedAllocArrayPtr					\
        CLASSDEF_TypedArrayPtr						\
    ooc_publicP(void, free, (void*))					\
									\
  ooc_method5(TYPE, initTypedAllocArrayPtr,				\
	      void *ptr, size_t size, ooc_type type, size_t cnt,	\
	                                    void (*free)(void *))
#include ooc_End

#endif /* OOC_TYPE_TYPEDALLOCARRAYPTR_H */
