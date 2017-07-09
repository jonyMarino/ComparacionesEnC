/*
 ******************************
 * Generic array pointer implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ArrayPtr.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include <ooc/type/ArrayPtr.h>

method0(TYPE, init)
{
  scall0(init);

  self->cnt = 0;

  return self;
}

method2(TYPE, initPtr, void *ptr, size_t size)
{
  scall2(initPtr, ptr, size);

  self->cnt = 0;

  return self;
}

method3(TYPE, initArrayPtr, void *ptr, size_t size, size_t cnt)
{
  scall2(initPtr, ptr, size);

  self->cnt = cnt;

  return self;
}

staticMethod0(void, initialize)
{
  override( init         );
  override( initPtr      );
  override( initArrayPtr );
}

#include End
