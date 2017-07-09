/*
 ******************************
 * Generic pointer implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Pointer.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>

#include Implementation

#include <ooc/type/Pointer.h>

method0(TYPE, init)
{
  scall0(init);

  self->ptr  = 0;
  self->size = 0;

  return self;
}

method2(TYPE, initPtr, void *ptr, size_t size)
{
  scall0(init);

  ooc_assert(!ptr || size);

  self->ptr  = ptr;
  self->size = size;

  return self;
}

method0(void, deinit)
{
  self->ptr = 0;

  scall0(deinit);
}

staticMethod0(void, initialize) 
{
  override( init    );
  override( initPtr );
  override( deinit  );
}

#include End
