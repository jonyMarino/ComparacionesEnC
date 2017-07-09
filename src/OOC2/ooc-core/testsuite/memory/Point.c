/*
 *******************************
 * Point implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Point.c,v 1.5 2005/12/14 18:35:06 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#define Point_PRIVATE_DEF	\
	private(int, x)		\
        private(int, y)

#include "Point.h"

/*
 * Static methods
 */

method0(TYPE, init)
{
  self->x = 0;
  self->y = 0;

  return self;
}

method0(void, deinit)
{
  (void)self;
}

method0(void, mthd)
{
  (void)self;
}

method1(void, mthdArg, Object obj)
{
  (void)self;
  (void)obj;
}

method1(Object, mthdRetArg, Object obj)
{
  (void)self;

  return obj;
}


staticMethod0(void, initialize)
{
  override( mthd       );
  override( mthdArg    );
  override( mthdRetArg );

  override( init   );
  override( deinit );
}

#include End
