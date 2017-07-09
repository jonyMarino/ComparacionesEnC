#ifndef OOC_TYPE_TYPEDARRAYPTR_H
#define OOC_TYPE_TYPEDARRAYPTR_H

/*
 *******************************
 * Generic Typed Array pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TypedArrayPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS       TypedArrayPtr
#define SUPER_CLASS TypedPtr

#define CLASSDEF_TypedArrayPtr						\
        CLASSDEF_TypedPtr						\
    ooc_public(size_t, cnt)						\
									\
  ooc_method4(TYPE, initTypedArrayPtr,					\
	      void *ptr, size_t size, ooc_type type, size_t cnt)

#include ooc_End

#endif /* OOC_TYPE_TYPEDARRAYPTR_H */
