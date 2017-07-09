#ifndef OOC_TYPE_ALLOCPTR_H
#define OOC_TYPE_ALLOCPTR_H

/*
 *******************************
 * AllocPtr interface
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: AllocPtr.h,v 1.3 2005/12/20 15:17:20 ldeniau Exp $
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

#define CLASS       AllocPtr
#define SUPER_CLASS Pointer

#define CLASSDEF_AllocPtr					\
        CLASSDEF_Pointer					\
    ooc_publicP(void, free, (void*))				\
								\
  ooc_method3(TYPE, initAllocPtr,				\
	      void* ptr, size_t size, void (*free)(void*))
 
#include ooc_End

#endif /* OOC_TYPE_ALLOCPTR_H */
