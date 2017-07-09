/*
 ******************************
 * Bool implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Bool.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>

#include <stdio.h>
#include <string.h>

#include Implementation

#include <ooc/type/Bool.h>

method0(TYPE, init)
{
  scall0(init);
  
  self->val = 0;

  return self;
}

method1(TYPE, initWith, bool val)
{
  scall0(init);

  self->val = val;

  return self;
}

constMethod0(size_t, hash)
{
  return self->val;
}

constMethod1(bool, equal, constTYPE obj)
{
  ooc_assert(obj);

  return self->val == obj->val;
}

constMethod1(int, compare, constTYPE obj)
{
  ooc_assert(obj);

  return self->val < obj->val ? -1 : (self->val > obj->val ? 1 : 0);
}

staticMethod0(void, initialize)
{
  override( init     );
  override( initWith );

  override( hash     );
  override( equal    );
  override( compare  );
}

#include End
