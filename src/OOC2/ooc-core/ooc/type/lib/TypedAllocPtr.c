/*
 ******************************
 * Generic typed alloc pointer implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TypedAllocPtr.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include <ooc/type/TypedAllocPtr.h>

method0(TYPE, init)
{
  self->free = 0;

  scall0(init);
  
  self->free = ooc_free;

  return self;
}

method2(TYPE, initPtr, void *ptr, size_t size)
{
  self->free = 0;

  scall2(initPtr, ptr, size);

  self->free = ooc_free;

  return self;
}

method3(TYPE, initTypedPtr, void *ptr, size_t size, ooc_type type)
{
  self->free = 0;

  scall3(initTypedPtr, ptr, size, type);

  self->free = ooc_free;

  return self;
}

method4(TYPE, initTypedAllocPtr, void *ptr, size_t size, 
	                         ooc_type type, void (*free)(void*))
{
  self->free = 0;

  scall3(initTypedPtr, ptr, size, type);

  self->free = free;

  return self;
}

method0(void, deinit)
{
  if (self->free)
    self->free(self->ptr), self->free = 0;

  scall0(deinit);
}

staticMethod0(void, initialize)
{
  override( init              );
  override( initPtr           );
  override( initTypedPtr      );
  override( initTypedAllocPtr );
  override( deinit            );
}

#include End
