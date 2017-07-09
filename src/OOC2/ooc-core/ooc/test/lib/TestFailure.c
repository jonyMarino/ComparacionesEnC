/*
 *******************************
 * TestFailure implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: TestFailure.c,v 1.6 2005/12/06 15:58:37 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/type/chr_array.h>
#include <ooc/ex/ExNotSupported.h>
#include <string.h>

#include Implementation

#include <ooc/test/TestFailure.h>

/*
 * Object methods
 */

method3(TYPE, initWith, const char *cond, const char *file, int line)
{
  self->cond = 0;

  scall0(init);

  self->cond = chr_array_rawdup(cond, strlen(cond)+1);
  self->file = file;
  self->line = line;

  return self;
}

method0(void, deinit)
{
  chr_array_del(self->cond), self->cond = 0;

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
