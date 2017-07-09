#ifndef OOC_TYPE_ALLOCARRAYPTR_H
#define OOC_TYPE_ALLOCARRAYPTR_H

/*
 *******************************
 * Generic Array pointer interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: AllocArrayPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#ifndef OOC_TYPE_ARRAYPTR_H
#include <ooc/type/ArrayPtr.h>
#endif

#include ooc_Interface

#define CLASS       AllocArrayPtr
#define SUPER_CLASS ArrayPtr

#define CLASSDEF_AllocArrayPtr						\
        CLASSDEF_ArrayPtr						\
    ooc_publicP(void, free, (void*))					\
									\
  ooc_method4(TYPE, initAllocArrayPtr,					\
	      void *ptr, size_t size, size_t cnt, void (*free)(void *))

#include ooc_End

#endif /* OOC_TYPE_ALLOCARRAYPTR_H */
