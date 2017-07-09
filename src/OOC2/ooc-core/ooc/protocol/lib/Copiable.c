/*
 *******************************
 * Copiable implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Copiable.c,v 1.10 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/utils/memchr.h>
#include <ooc/utils/memint.h>

#include Implementation

#include <ooc/protocol/Copiable.h>

static void bad_type(void);

static void
copy(Object self, constObject src)
{
  size_t off, sz;

  ooc_assert(src);
  
  if (self == src)
    return;
  
  if (!isSame(self->_isa, src->_isa))
    bad_type();

  off = offsetof(struct Object, _cnt) + sizeof self->_cnt;
  sz = ooc_classInstanceSize(self->_isa) - off;

  if (sz % sizeof(int))
    ooc_memchr_copy((char*)self+off, (char*)src+off, sz);
  else
    ooc_memint_copy((int*)((char*)self+off),
		    (int*)((char*)src +off), sz / sizeof(int));
}

static void
swap(Object self, Object src)
{
  size_t off, sz;

  ooc_assert(src);

  if (self == src)
    return;
  
  if (!isSame(self->_isa, src->_isa))
    bad_type();
 
  off = offsetof(struct Object, _cnt) + sizeof self->_cnt;
  sz = ooc_classInstanceSize(self->_isa) - off;

  if (sz % sizeof(int))
    ooc_memchr_swap((char*)self+off, (char*)src+off, sz);
  else
    ooc_memint_swap((int*)((char*)self+off),
		    (int*)((char*)src +off), sz / sizeof(int));
}

method0(TYPE, init)
{
  scall0(init);

  self->copy = copy;
  self->swap = swap;

  return self;
}

staticMethod0(void, initialize)
{
  override(init);
}

#include End

#include <ooc/ex/ExBadType.h>

static void
bad_type(void)
{
  throw(new(ExBadType));
}
