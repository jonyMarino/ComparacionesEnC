/*
 ******************************
 * Exception Implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Exception.c,v 1.4 2005/12/09 17:43:09 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

/*
 * -------------------------
 *  Exceptions implementation
 * -------------------------
 */

#include Implementation

#include <ooc/ex/Exception.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadAssert.h>

method1(TYPE, initWithStr, const char *str)
{
  scall0(init);

  self->str = str;

  return self;
} 

staticMethod0(void, initialize)
{
  override(initWithStr);
}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadAccess.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadArgument.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadCast.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadClass.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadDomain.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadException.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadSignal.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadFormat.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadInput.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadIO.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadOp.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadPosition.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadRange.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadSize.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadState.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExBadType.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExOverflow.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExUnderflow.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExNotFound.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExNotImplemented.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExNotSupported.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExTestAssert.h>

staticMethod0(void, initialize) {}

#include End

/*
 * -------------------------
 */

#include Implementation

#include <ooc/ex/ExUnexpected.h>

staticMethod0(void, initialize) {}

#include End
