#define USING_OOC

#include <ooc/Object.h>

#include <stdio.h>

#include Implementation

#include "DummyProtocol.h"

/*
 * Object methods
 */

static int mth1(Object self)
{
  (void)self;

  return 1;
}

static int mth2(Object self)
{
  (void)self;

  return 2;
}

method0(TYPE, init)
{
  scall0(init);

  self->mth1 = mth1;
  self->mth2 = mth2;

  return self;
}

/*
 * Static methods
 */

staticMethod0(void, initialize)
{
  override( init );
}

#include End
