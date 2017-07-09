/*
 ******************************
 * Complex implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Complex.c,v 1.2 2005/12/06 15:12:57 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/ex/ExBadOp.h>
#include <ooc/utils/macros.h>

#include <float.h>

#include Implementation

#include <ooc/type/Complex.h>

method0(TYPE, init)
{
  scall0(init);

  self->val = ooc_complex(0.0, 0.0);

  return self;
}

method2(TYPE, initWith, double real, double imag)
{
  scall0(init);

  self->val = ooc_complex(real, imag);

  return self;
}

static inline bool
equal(double a, double b)
{
  return a == b ||
    (a<b ? b-a : a-b) < DBL_EPSILON * (OOC_ABS(a) + OOC_ABS(b));
}

constMethod1(bool, equal, constTYPE obj)
{
  ooc_assert(obj);

  return
    equal(ooc_creal(self->val), ooc_creal(obj->val)) &&
    equal(ooc_cimag(self->val), ooc_cimag(obj->val));
}

constMethod1(int, compare, constTYPE obj)
{
  throw(new(ExBadOp));

  return self != obj;
}

staticMethod0(void, initialize)
{
  override( init     );
  override( initWith );

  override( equal    );
  override( compare  );
}

#include End
