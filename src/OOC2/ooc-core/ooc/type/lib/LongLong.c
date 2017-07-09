/*
 ******************************
 * Long Long implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: LongLong.c,v 1.3 2005/12/06 15:12:57 ldeniau Exp $
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

#include <ooc/type/LongLong.h>

method0(TYPE, init)
{
  scall0(init);

#if OOC_LLONG
  self->val = 0;
#else
  self->val._[0] = self->val._[1] = 0;
#endif

  return self;
}

method1(TYPE, initWith, ooc_llong val)
{
  scall0(init);

  self->val = val;

  return self;
}

constMethod0(size_t, hash)
{
#if OOC_LLONG
  return self->val;
#else
  if (self->val._[0])
    if (self->val._[1])
      return self->val._[0] * self->val._[1];
    else
      return self->val._[0];
  else
    return self->val._[1];
#endif
}

constMethod1(bool, equal, constTYPE obj)
{
  ooc_assert(obj);

#if OOC_LLONG
    return self->val == obj->val;
#else
    return
      self->val._[0] == obj->val._[0] &&
      self->val._[1] == obj->val._[1];
#endif
}

constMethod1(int, compare, constTYPE obj)
{
  ooc_assert(obj);

#if OOC_LLONG
  return self->val < obj->val ? -1 : (self->val > obj->val ? 1 : 0);
#else
       if (self->val._[1] < obj->val._[1])
    return -1;
  else if (self->val._[1] > obj->val._[1])
    return  1;
  else if (self->val._[0] < obj->val._[0])
    return -1;
  else if (self->val._[0] > obj->val._[0])
    return  1;
  else
    return  0;
#endif
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
