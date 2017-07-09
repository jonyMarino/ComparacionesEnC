#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include "DummyClass.h"

method0(int, mth2)
{
  (void)self;

  return 4;
}

staticMethod0(void, initialize)
{
  override( mth2 );
}

#include End
