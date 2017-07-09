/*
 ******************************
 * System exception implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExSystem.c,v 1.1 2005/09/28 08:02:39 oachim Exp $
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
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSystem.h>

staticMethod0(void, initialize) {}

#include End


bool
ooc_throwSys_(int syserr, classExSystem cls, const char *file, int line)
{
  ExSystem e;

  ooc_assert(isSubclassOf(cls, ExSystem));

  e = (ExSystem)newAs(cls);

  e->syserr = syserr;

  throwLoc(e, file, line);

  return false;
}

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExSysIO.h>

staticMethod0(void, initialize) {}

#include End
