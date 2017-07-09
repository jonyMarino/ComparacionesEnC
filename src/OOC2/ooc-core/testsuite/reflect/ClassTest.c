#define USING_OOC

#include <ooc/Object.h>

#include <ooc/type/complex.h>
#include <ooc/reflect/ReflectFields.h>
#include <ooc/reflect/ReflectMethods.h>

#include Implementation

#include "ClassTest.h"

method0(CLASS, init)
{
  size_t i;

  scall0(init);

  for (i = 0; i < 10; i++)
    self->array[i] = i;

  return self;
}

method1(Object, mthd1, Object arg)
{
  self->data_mth1 = arg;

  return arg;
}

method1(int, mthd2, int i)
{
  (void)self;

  return i * 2;
}

method1(double, mthd3, double d)
{
  (void)self;

  return d * 2;
}

method1(ooc_complex, mthd4, ooc_complex c)
{
  ooc_complex r;

  (void)self;

  ooc_creal(r) = ooc_creal(c);
  ooc_cimag(r) = -ooc_cimag(c);

  return r;
}

staticMethod1(int, mthd5, int i)
{
  return i * 2;
}

staticMethod0(void, initialize)
{
  override(init );

  override(mthd1);
  override(mthd2);
  override(mthd3);
  override(mthd4);
  override(mthd5);
}

#include End
