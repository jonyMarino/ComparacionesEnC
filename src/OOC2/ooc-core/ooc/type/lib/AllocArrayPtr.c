/*
 ******************************
 * Generic alloc array pointer implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: AllocArrayPtr.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include <ooc/type/AllocArrayPtr.h>

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

method3(TYPE, initArrayPtr, void *ptr, size_t size, size_t cnt)
{
  self->free = 0;

  scall3(initArrayPtr, ptr, size, cnt);

  self->free = ooc_free;

  return self;
}

method4(TYPE, initAllocArrayPtr, void *ptr, 
	size_t size, size_t cnt, void (*free)(void*))
{
  self->free = 0;

  scall3(initArrayPtr, ptr, size, cnt);

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
  override( initArrayPtr      );
  override( initAllocArrayPtr );
  override( deinit            );
}

#include End
