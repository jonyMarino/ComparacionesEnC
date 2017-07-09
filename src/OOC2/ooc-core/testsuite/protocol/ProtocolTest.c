#define USING_OOC

#include <ooc/Object.h>
#include <ooc/reflect/ReflectMethods.h>
#include <ooc/reflect/ReflectFields.h>

#include "DummyClass.h"

#include Implementation

#define ProtocolTest_PRIVATE_DEF \
        private(DummyClass, obj)

#include "ProtocolTest.h"

/*
 * Object methods
 */

method0(Object, testCallMethod)
{
  Object obj = (Object)self->obj;
  int res = pcall0(obj, DummyProtocol, mth1);

  ooc_testAssert(res == 1);

  return 0;
}

method0(Object, testOverrideMethod)
{
  Object obj = (Object)self->obj;
  int res = pcall0(obj, DummyProtocol, mth2);

  ooc_testAssert(res == 4);

  return 0;
}

/*
 * Fixture
 */

method0(void, setup)
{
  self->obj = own(new(DummyClass));
}

method0(void, cleanup)
{
  release(self->obj);
}

/*
 * Static methods
 */

staticMethod0(void, initialize)
{
  override(setup  );
  override(cleanup);

  override(testCallMethod    );
  override(testOverrideMethod);
}

#include End
