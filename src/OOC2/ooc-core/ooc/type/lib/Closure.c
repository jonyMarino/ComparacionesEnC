/*
 ******************************
 * Closure implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Closure.c,v 1.6 2005/12/16 16:56:04 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>

/*
 * Class implementation
 */

#include Implementation

#include <ooc/type/Closure.h>

/*
 * Object methods
 */

method2(TYPE, initWith, ooc_closure fct, Object obj[])
{
  self->obj_cnt = 0;

  ooc_assert(fct);

  self->fct = fct;

  while (obj[self->obj_cnt] && self->obj_cnt < Closure_maxObj)
    self->obj[self->obj_cnt] = retain(obj[self->obj_cnt]), ++self->obj_cnt;
  
  return self;
}

method2(TYPE, initWithVA, ooc_closure fct, ...)
{
  Closure ret_self;
  va_list va;

  va_start(va, fct);
  ret_self = call2(self, initWithVAList, fct, va);
  va_end(va);

  return ret_self;
}

method2(TYPE, initWithVAList, ooc_closure fct, va_list va)
{
  Object obj;

  self->obj_cnt = 0;
  self->fct = fct;

  ooc_assert(fct);

  while ((obj = va_arg(va, Object)) && self->obj_cnt < Closure_maxObj)
    self->obj[self->obj_cnt] = retain(obj), ++self->obj_cnt;
  
  return self;
}

method0(void, deinit)
{
  self->fct = 0;

  while (self->obj_cnt--)
    release(self->obj[self->obj_cnt]);

  scall0(deinit);
}

constMethod1(Object, invoke, Object args[])
{
  return self->fct(self, args);
}

/*
 * Static methods
 */

staticMethod0(void, initialize)
{
  inhibit(init);

  override( initWith       );
  override( initWithVA     );
  override( initWithVAList );
  override( deinit         );
  override( invoke         );
}

#include End
