/*
 *******************************
 * TestError implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestError.c,v 1.6 2005/12/06 15:58:36 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/ex/ExNotSupported.h>

#include Implementation

#include <ooc/test/TestError.h>

/*
 * Object methods
 */

method3(TYPE, initWith, Object ex, const char *file, int line)
{
  self->ex = 0;

  scall0(init);

  self->ex   = retain(ex);
  self->file = file;
  self->line = line;

  return self;
}

method0(void, deinit)
{
  release(self->ex);

  scall0(deinit);
}

/*
 * Class methods
 */

staticMethod0(void, initialize)
{
  inhibit(init);

  override( initWith );
  override( deinit   );
}

#include End
