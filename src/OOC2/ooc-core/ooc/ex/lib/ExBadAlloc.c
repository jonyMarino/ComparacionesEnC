/*
 ******************************
 * ExBadAlloc Implementation
 * -----
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: ExBadAlloc.c,v 1.7 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

#define USING_OOC

#include <ooc/Object.h>

#include Implementation

#include <ooc/ex/ExBadAlloc.h>

static Object
exBadAlloc_alloc(classObject cls)
{
  static struct ExBadAlloc singleton[1] = {{
    ooc_classDesc(ExBadAlloc), 1
  }};
  
  (void)cls;
  
  return (void*)singleton;
}

static void
exBadAlloc_dealloc(Object obj)
{
  (void)obj;
}

static void
exBadAlloc_detach(Object obj)
{
  (void)obj;
}

static struct ooc_memsrv memExBadAlloc_srv[1] = {{
  exBadAlloc_alloc,
  exBadAlloc_dealloc,
  exBadAlloc_detach
}};

staticMethod0(void, initialize)
{
  overrideMemServices(memExBadAlloc_srv);
}

#include End
