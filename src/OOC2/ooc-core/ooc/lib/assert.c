/*
 ******************************
 * Assertion implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: assert.c,v 1.3 2005/12/09 17:43:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/assert.h>
#include <ooc/ex/ExBadAssert.h>

int
ooc_assert_(const char *cond, const char *file, int line)
{
  ExBadAssert ex = new1(ExBadAssert, initWithStr, cond);

  throwLoc(ex, file, line);

  return 0;
}
