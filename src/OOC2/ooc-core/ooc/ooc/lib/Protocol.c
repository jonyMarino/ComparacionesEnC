/*
 ******************************
 * Protocol Implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Protocol.c,v 1.6 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>

/*
 * -------------------------
 *  Protocol implementation
 * -------------------------
 */

#include Implementation

#include <ooc/Object.h> /* friend classes */

/* reactivate Protocol scope */
#include ooc_CloseScope
#define ABSTRACT_PROTOCOL Protocol
#define SUPER_CLASS Object
#include ooc_OpenScope

/*
 * Class methods
 */

#ifndef OOC_DBG

staticMethod0(void, initialize) {}

#else

method0(TYPE, init)
{
  OOC_DBG((OOC_STR(CLASS)".init(%s)", ooc_className(self->_isa)));

  return self;
}

method0(void, deinit)
{
  OOC_DBG((OOC_STR(CLASS)".deinit(%s)", ooc_className(self->_isa)));
  (void)self;
}

staticMethod0(void, initialize)
{
  override( init   );
  override( deinit );
}

#endif

#include End
