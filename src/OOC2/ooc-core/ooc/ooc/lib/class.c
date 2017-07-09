/*
 *******************************
 * Class initialization
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: class.c,v 1.14 2006/11/27 16:59:38 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/Object.h>
#include <ooc/assert.h>
#include <ooc/utils/thread.h>
#include <stdlib.h>

/*
 * Static functions
 */

static void
classDeinitialize_(Class cls)
{
  Class next;

  ooc_assert(cls && cls->_isa);

  OOC_DBG(("ooc_classDeinitialize(%s)", ooc_className(cls)));

  if (ooc_classIsStatic(cls)) {
    ooc_assert(cls->_cnt == 1);
    
    /* class is marked as deinitialized */
    OOC_CONST_CAST(unsigned, cls->_cnt) = 0;
  }
  
  /* 1st: sub class (if any) */
  if (ooc_classSubClass(cls))
    classDeinitialize_(ooc_classSubClass(cls));
  
  next = ooc_classNextClass(cls);

  /* 2nd: class */
  call0(cls, deinit);

  /* 3rd: next class */
  if (next)
    classDeinitialize_(next);
}

/*
 * -------------------------
 *  Special functions
 * -------------------------
 */

void
ooc_classInitialize_(Class cls)
{
  ooc_assert(cls && cls->_isa);

  OOC_DBG(("ooc_classInitialize(%s)", ooc_className(cls)));

  ooc_assert(ooc_classIsStatic(cls) && !cls->_cnt);

  /* class is marked as initialized */
  OOC_CONST_CAST(unsigned, cls->_cnt) = 1;

  /* 1st: super class (if any) */
  if (cls->_spr)
    ooc_classDescInitialize(cls->_spr);
  
  /* 2nd: meta class */
  ooc_classDescInitialize(cls->_isa);

  /* 3rd: class */
  call0(cls, init);
}

void
ooc_classDeinitialize(void)
{
  static bool done = false;
  ooc_threadMutex(mutex);

  ooc_threadMutexLock(&mutex);
  if (done)
    ooc_abort("ooc_classDeinitialize() already called");
  
  done = true;
  classDeinitialize_((void*)ooc_classDesc(Object));
  ooc_threadMutexUnlock(&mutex);
}

/*
 * -------------------------
 *  Special methods
 * -------------------------
 */

void
ooc_methodPureVirtual(Object obj)
{
  if (ooc_memIsObject(obj))
    ooc_abort("pure virtual method call with an instance of class %s "
	      "as its first parameter (self?)", ooc_className(obj->_isa));

  ooc_abort("pure virtual (static?) method call");
}

void
ooc_methodInhibited(Object obj)
{
  if (ooc_memIsObject(obj))
    ooc_abort("inhibited method call with an instance of class %s "
	      "as its first parameter (self?)", ooc_className(obj->_isa));
  
  ooc_abort("inhibited (static?) method call");
}

void
ooc_methodDoNothing(void) {}
