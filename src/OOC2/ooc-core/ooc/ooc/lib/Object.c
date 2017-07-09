/*
 *******************************
 * Object implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: Object.c,v 1.6 2005/12/14 18:35:05 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>
#include <ooc/ooc/lib/context.h>

/*
 * -------------------------
 *  Object implementation
 * -------------------------
 */

#include Implementation

#include <ooc/Object.h> /* friend classes */

/* reactivate Object scope */
#include CloseScope
#define  ABSTRACT_CLASS Object
#include OpenScope

/*
 * Class methods
 */

method0(TYPE, init)
{
  /* should do nothing */
  return self;
}

method0(void, deinit)
{
  /* should do nothing */
  (void)self;
}

method1(Object, cast, classObject cls)
{
  (void)self;
  (void)cls;

  return 0;
}

method1(Protocol, pcast, classProtocol pcls)
{
  /* must be empty */
  (void)self;
  (void)pcls;

  return 0;
}

staticMethod0(void, deinitialize)
{
  ooc_contextDeinitialize();
}

staticMethod0(void, initialize)
{
  override( init         );
  override( deinit       );
  override( cast         );
  override( pcast        );
  override( deinitialize );

  ooc_classInitialize(Class);
  ooc_contextInitialize();
}

#undef SUPER_CLASS /* special inheritance */

#include End
